/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:30:02 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/05/02 13:06:22 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_datatypes.h>
#include <rt_intersect.h>
#include <rt_render.h>
#include <rt_color.h>
#include <rt_lighting.h>
#include <rt_vector_utils.h>
#include <rt_time.h>
#include <math.h>

#include <rt_scene_printer.h>
#include <stdio.h>

size_t g_frame_counter = 0;

double	degrees_to_radians(int degrees)
{
	return ((double)degrees * (double)M_PI / 180);
}

void	set_viewport(t_rt_viewport *viewport, t_rt_camera *camera, double aspect_ratio)
{
	double	radians;
	double	diagonal;

	radians = (double)camera->fov * (double)M_PI / 180;
	viewport->height = 2.0;
	viewport->width = viewport->height * aspect_ratio;
	diagonal = sqrt(viewport->width * viewport->width + viewport->height * viewport->height);
	viewport->focal_length = diagonal / 2 / tan(radians / 2);
	printf("\n\nwidth: %f\nheight: %f\ndiagonal: %f\nfov: %d\nfocal length: %f\n\n", viewport->width, viewport->height, diagonal,  camera->fov, viewport->focal_length);
}

t_rt_vector rotate_vector_x(t_rt_vector original_vector, double radians)
{
	t_rt_vector	rotated_vector;

	rotated_vector.x = original_vector.x;
	rotated_vector.y = original_vector.y * cos(radians) - original_vector.z * sin(radians);
	rotated_vector.z = original_vector.y * sin(radians) + original_vector.z * cos(radians);
	return (rotated_vector);
}

t_rt_vector rotate_vector_y(t_rt_vector original_vector, double radians)
{
	t_rt_vector	rotated_vector;

	rotated_vector.x = original_vector.x * cos(radians) + original_vector.z * sin(radians);
	rotated_vector.y = original_vector.y;
	rotated_vector.z = -original_vector.x * sin(radians) + original_vector.z * cos(radians);
	return (rotated_vector);
}

t_rt_vector rotate_vector_z(t_rt_vector original_vector, double radians)
{
	t_rt_vector	rotated_vector;

	rotated_vector.x = original_vector.x * cos(radians) - original_vector.y * sin(radians);
	rotated_vector.y = original_vector.x * sin(radians) + original_vector.y * cos(radians);
	rotated_vector.z = original_vector.z;
	return (rotated_vector);
}

t_rt_vector	rotate_vector(t_rt_vector original_vector, t_rt_vector rotation)
{
	t_rt_vector	rotated_vector;

	rotated_vector = rotate_vector_x(original_vector, degrees_to_radians(rotation.y * 360));
	rotated_vector = rotate_vector_y(rotated_vector, degrees_to_radians(rotation.x * 360));
	rotated_vector = rotate_vector_z(rotated_vector, degrees_to_radians(rotation.z * 360));
	(void)rotation;
	return (rotated_vector);
}

t_rt_vector	canvas_to_viewport(int x, int y, t_rt_scene *scene)
{
	t_rt_vector	v;

	v.x = (double)x * scene->viewport.width / (double)scene->canvas.x;  //static divisions in a loop..
	v.y = (double)y * scene->viewport.height / (double)scene->canvas.y;
	v.z = scene->viewport.focal_length;
//	print_orientation(scene->cameras[0].orientation);
	v = rotate_vector(v, scene->cameras[0].orientation);
	return (v);
}

t_rt_color	trace_ray(t_rt_ray ray, t_rt_scene *scene, int recursion_depth)
{
	t_intersect_result	intersect_result;

	ft_bzero(&intersect_result, sizeof(intersect_result));
	intersect_result = get_closest_intersection(scene, ray.origin, ray.destination, ray.t_min, ray.t_max);
	if (!intersect_result.closest_obj)
		return (y_gradient(ray.origin, ray.destination, scene));
	return (assemble_color(intersect_result, ray, scene, recursion_depth));
}

t_rt_ray	init_rt_ray(t_rt_point origin, t_rt_point destination, double t_min, double t_max)
{
	t_rt_ray	ray;

	ft_bzero(&ray, sizeof(ray));
	ray.origin = origin;
	ray.destination = destination;
	ray.t_min = t_min;
	ray.t_max = t_max;
	return (ray);
}

void	render_text(t_rt_mlx *mlx, t_rt_scene *scene, t_ms time_spend)
{
	char	fov[32];
	char	fps[32];
	char	rgb[32];
	char	ref[32];

	sprintf(fov, "fov: %d", scene->cameras[0].fov);
	sprintf(rgb, "%.3d %.3d %.3d", (int)(255.999 * scene->bg_color.x), (int)(255.999 * scene->bg_color.y), (int)(255.999 * scene->bg_color.z));
	sprintf(fps, "frame took %lu ms", time_spend);
	sprintf(ref, "recursion depth: %d", scene->recursion_depth);
	mlx_delete_image(mlx->mlx, mlx->fps);
	mlx_delete_image(mlx->mlx, mlx->text);
	mlx_delete_image(mlx->mlx, mlx->rgb);
	mlx_delete_image(mlx->mlx, mlx->ref);
	mlx->text = mlx_put_string(mlx->mlx, fov, 20, 20);
	mlx->rgb = mlx_put_string(mlx->mlx, rgb, scene->canvas.x - 150, 20);
	mlx->fps = mlx_put_string(mlx->mlx, fps, scene->canvas.x - 200, scene->canvas.y - 50);
	mlx->ref = mlx_put_string(mlx->mlx, ref, 20, scene->canvas.y - 50);
}

t_err	render_scene(t_rt_mlx *mlx, t_rt_scene *scene)
{
	t_rt_resolution	pixel;
	t_rt_color		color;
	t_time_stamp	start_of_frame;
	t_ms			time_spend;

	start_of_frame = set_time();
	pixel.y = -scene->canvas.y / 2;
	while (pixel.y < scene->canvas.y / 2)
	{
		pixel.x = -scene->canvas.x / 2;
		while (pixel.x < scene->canvas.x / 2)
		{
			t_rt_point	destination = canvas_to_viewport(pixel.x, pixel.y, scene);
			color = trace_ray(init_rt_ray(scene->cameras[0].coordinates, destination, 1, INFINITY), scene, scene->recursion_depth);
			mlx_put_pixel(mlx->img, pixel.x + scene->canvas.x / 2, scene->canvas.y - (pixel.y + scene->canvas.y / 2), color_to_int(color));
			pixel.x++;
		}
		pixel.y++;
	}
	time_spend = ms_passed(start_of_frame);
	render_text(mlx, scene, time_spend);
	g_frame_counter++;
	printf("*************** FRAME COUNTER %zu\n", g_frame_counter);
	return (NO_ERR);
}
