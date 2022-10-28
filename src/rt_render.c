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
#include <rt_time.h>
#include <math.h>

#include <stdio.h>

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

t_rt_vector	canvas_to_viewport(int x, int y, t_rt_scene *scene)
{
	t_rt_vector	v;

	v.x = (double)x * scene->viewport.width / (double)scene->canvas.x;  //static divisions in a loop..
	v.y = (double)y * scene->viewport.height / (double)scene->canvas.y;
	v.z = scene->viewport.focal_length;
	// v = multiply_vector(v, 1 / dot_product(v, v));
	return (v);
}

t_rt_color	trace_ray(t_rt_ray ray, t_rt_scene *scene, int recursion_depth)
{
	t_intersect_result	intersect_result;

	ft_bzero(&intersect_result, sizeof(intersect_result));
	intersect_result = get_closest_intersection(scene, ray.origin, ray.direction, ray.t_min, ray.t_max);
	if (!intersect_result.closest_obj)
		return (y_gradient(ray.origin, ray.direction, scene));
	return (precalculate_light(intersect_result, ray,  scene, recursion_depth));
}

t_err	render_scene(t_rt_mlx *mlx, t_rt_scene *scene)
{
	t_rt_resolution	pixel;
	t_rt_color		color;
	t_time_stamp	start_of_frame;
	t_msecs			time_spend;

	start_of_frame = set_time();
	pixel.y = -scene->canvas.y / 2;
	while (pixel.y < scene->canvas.y / 2)
	{
		pixel.x = -scene->canvas.x / 2;
		while (pixel.x < scene->canvas.x / 2)
		{
			t_rt_vector d = canvas_to_viewport(pixel.x, pixel.y, scene);
			color = trace_ray((t_rt_ray){(t_rt_vector){0,0,0}, d, INFINITY, 1, 3, (t_rt_vector){0, 0, 0}, (t_rt_vector){0, 0, 0}, (t_rt_vector){0, 0, 0}, (t_rt_vector){0, 0, 0}}, scene, 3);
//			color = trace_ray(scene->cameras[0].coordinates, D, scene); // needs matrix translation?
			mlx_put_pixel(mlx->img, pixel.x + scene->canvas.x / 2, scene->canvas.y - (pixel.y + scene->canvas.y / 2), color_to_int(color));
			pixel.x++;
		}
		pixel.y++;
	}
	char	fov[32];
	char	fps[32];
	char	rgb[64];
	time_spend = ms_passed(start_of_frame);
	sprintf(fov, "fov: %d", scene->cameras[0].fov);
	sprintf(rgb, "%.3d %.3d %.3d", (int)(255.999 * scene->red), (int)(255.999 * scene->green), (int)(255.999 * scene->blue));
	sprintf(fps, "frame took %lu ms", time_spend);
	mlx_delete_image(mlx->mlx, mlx->fps);
	mlx_delete_image(mlx->mlx, mlx->text);
	mlx_delete_image(mlx->mlx, mlx->rgb);
	mlx->text = mlx_put_string(mlx->mlx, fov, 20, 20);
	mlx->rgb = mlx_put_string(mlx->mlx, rgb, scene->canvas.x - 150, 20);
	mlx->fps = mlx_put_string(mlx->mlx, fps, scene->canvas.x - 200, scene->canvas.y - 50);
	custom_sleep(16 - time_spend);
	return (NO_ERR);
}
