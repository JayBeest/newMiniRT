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
#include <rt_init.h>
#include <rt_render.h>
#include <rt_render_utils.h>
#include <rt_msaa.h>
#include <rt_color.h>
#include <rt_trace.h>
#include <rt_rotate.h>
#include <rt_time.h>
#include <math.h>
#include <stdio.h>

size_t g_frame_counter = 0;

void	render_text(t_rt_mlx *mlx, t_rt_scene *scene, t_ms time_spend)
{
	char	fov[32];
	char	fps[32];
	char	rgb[32];
	char	ref[32];
	char	msaa[32];

	sprintf(fov, "fov: %d (zoom: %.1fx)", scene->cameras[0].fov, 1 + CAMERA_ZOOM_FACTOR * scene->cameras[0].zoom_level - 1);
	sprintf(rgb, "%.3d %.3d %.3d", (int)(255.999 * scene->bg_color.x), (int)(255.999 * scene->bg_color.y), (int)(255.999 * scene->bg_color.z));
	sprintf(fps, "frame took %lu ms", time_spend);
	sprintf(ref, "recursion depth: %d", scene->recursion_depth);
	sprintf(msaa, "multisampling:  %dx", scene->msaa);
	if (mlx->fps)
		mlx_delete_image(mlx->mlx, mlx->fps);
	if (mlx->text)
		mlx_delete_image(mlx->mlx, mlx->text);
	if (mlx->rgb)
		mlx_delete_image(mlx->mlx, mlx->rgb);
	if (mlx->ref)
		mlx_delete_image(mlx->mlx, mlx->ref);
	if (mlx->msaa)
		mlx_delete_image(mlx->mlx, mlx->msaa);
	if (!scene->hud)
		return ;
	mlx->text = mlx_put_string(mlx->mlx, fov, 20, 20);
	mlx->rgb = mlx_put_string(mlx->mlx, rgb, scene->canvas.x - 150, 20);
	mlx->fps = mlx_put_string(mlx->mlx, fps, scene->canvas.x - 200, scene->canvas.y - 70);
	mlx->ref = mlx_put_string(mlx->mlx, ref, 20, scene->canvas.y - 50);
	mlx->msaa = mlx_put_string(mlx->mlx, msaa, 20, scene->canvas.y - 80);
}

void	set_viewport_ratio(t_rt_viewport *viewport, t_rt_resolution canvas)
{
	viewport->x_ratio = viewport->width / (double)canvas.x;
	viewport->y_ratio = viewport->height / (double)canvas.y;
	printf("viewport/canvas ratios - x: %f y: %f\n", viewport->x_ratio, viewport->y_ratio);
}

void	set_viewport(t_rt_scene *scene, double aspect_ratio)
{
	t_rt_viewport	*viewport;
	int				i;
	double			diagonal;
	double			radians;

	viewport = &scene->viewport;
	radians = (double)scene->cameras[0].fov * (double)M_PI / 180;
	viewport->height = 2;
	viewport->width = viewport->height * aspect_ratio;
	diagonal = sqrt(viewport->width * viewport->width + viewport->height * viewport->height);
	viewport->focal_length = diagonal / 2 / tan(radians / 2);
//	printf("\n\nwidth: %f\nheight: %f\ndiagonal: %f\nfov: %d\nfocal length: %f\n\n", viewport->width, viewport->height, diagonal,  camera->fov, viewport->focal_length);
	i = scene->cameras[0].zoom_level;
	if (i == 0)
		return ;
	while (i > 0)
	{
		viewport->height /= CAMERA_ZOOM_FACTOR;
		viewport->width = viewport->height * aspect_ratio;
		i--;
	}
	set_viewport_ratio(viewport, scene->canvas);
}

t_rt_vector	canvas_to_viewport(double x, double y, t_rt_scene *scene)
{
	t_rt_vector	v;

	v.x = ((double)x - (double)scene->canvas.x / 2) * scene->viewport.x_ratio;
	v.y = (1 - ((double)y - (double)scene->canvas.y / 2)) * scene->viewport.y_ratio;
	v.z = scene->viewport.focal_length;
//	print_orientation(scene->cameras[0].orientation);
	v = rotate_vector(v, scene->cameras[0].orientation);
	return (v);
}

t_err	render_scene(t_rt_mlx *mlx, t_rt_scene *scene)
{
	t_rt_resolution			pixel;
	t_rt_color				color;
	t_time_stamp			start_of_frame;
	t_ms					time_spend;

	start_of_frame = set_time();
	pixel.y = 0;
	while (pixel.y < scene->canvas.y)
	{
		pixel.x = 0;
		while (pixel.x < scene->canvas.x)
		{
			if (scene->msaa > 0 && !scene->bare_toggle)
				color = rand_multi_sample(scene, pixel);
			else
				color = trace_ray(init_rt_ray(scene->cameras[0].coordinates, \
				canvas_to_viewport(pixel.x, pixel.y, scene), 1, INFINITY), scene, scene->recursion_depth);
			mlx_put_pixel(mlx->img, pixel.x, pixel.y, color_to_int(color));
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
