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
//#include <rt_lighting.h>
#include <rt_time.h>
#include <math.h>

#include <pthread.h>
#include <stdio.h>

void	set_viewport(t_rt_viewport *viewport, t_rt_camera *camera, float aspect_ratio)
{
	float	radians;
	float	diagonal;

	radians = (float)camera->fov * (float)M_PI / 180;
	viewport->height = 2.0f;
	viewport->width = viewport->height * aspect_ratio;
	diagonal = sqrtf(viewport->width * viewport->width + viewport->height * viewport->height);
	viewport->focal_length = diagonal / 2 / tanf(radians / 2);
	printf("\n\nwidth: %f\nheight: %f\ndiagonal: %f\nfov: %d\nfocal length: %f\n\n", viewport->width, viewport->height, diagonal,  camera->fov, viewport->focal_length);
}

t_rt_vector	canvas_to_viewport(int x, int y, t_rt_scene *scene)
{
	t_rt_vector	v;

	v.x = (float)x * scene->viewport.width / (float)scene->size.width;  //static divisions in a loop..
	v.y = (float)y * scene->viewport.height / (float)scene->size.height;
	v.z = scene->viewport.focal_length;
	// v = multip_vector(v, 1 / dot_product(v, v));
	return (v);
}

t_rt_color	trace_ray(t_rt_vector o, t_rt_vector d, t_rt_scene *scene, t_rt_resolution pixel)
{
	t_intersect_result	intersect_result;

	ft_bzero(&intersect_result, sizeof(intersect_result));
	intersect_result = get_closest_intersection(scene, o, d, 1, INFINITY);
	if (!intersect_result.closest_obj)
		return (all_the_colors(pixel, scene));
	return (intersect_result.closest_obj->def.color);
//	return (precalculate_light(intersect_result.closest_shape, o, d, intersect_result.closest_t, scene));
}

t_err	render_scene(t_rt_mlx *mlx, t_rt_scene *scene)
{
	t_rt_resolution	pixel;
	t_rt_color		color;
	t_time_stamp	start_of_frame;
	t_msecs			time_spend;

	start_of_frame = set_time();
	pixel.y = -scene->size.height / 2;
	while (pixel.y < scene->size.height / 2)
	{
		pixel.x = -scene->size.width / 2;
		while (pixel.x < scene->size.width / 2)
		{
			t_rt_vector D = canvas_to_viewport(pixel.x, pixel.y, scene);
			color = trace_ray((t_rt_vector){0,0,0}, D, scene, pixel);
//			color = trace_ray(scene->cameras[0].coordinates, D, scene); // needs matrix translation?
			mlx_put_pixel(mlx->img, pixel.x +  scene->size.width / 2, scene->size.height - (pixel.y + scene->size.height / 2), color_to_int(color));
			pixel.x++;
		}
		pixel.y++;
	}
	char	blue[32];
	char	fps[64];
	time_spend = ms_passed(start_of_frame);
	mlx_delete_image(mlx->mlx, mlx->fps);
	mlx_delete_image(mlx->mlx, mlx->text);
	sprintf(blue, "fov: %d\n", scene->cameras[0].fov);
	sprintf(fps, "frame took %lu ms - (%.1f fps)\n", time_spend, 1000.0f / (float)time_spend);
	mlx->text = mlx_put_string(mlx->mlx, blue, 20, 20);
	mlx->fps = mlx_put_string(mlx->mlx, fps, scene->size.width - 325, scene->size.height - 50);
	custom_sleep(16 - time_spend);
	return (NO_ERR);
}

//t_mult_pixel	get_multi_pix(t_scene scene, int id)
//{
//	t_mult_pixel	multi_pix;
//
//	if (id  == 0)
//	{
//		multi_pix.min_x = -1 * scene.resolution_x / 2;
//		multi_pix.max_x = 0;
//		multi_pix.min_y = 0;
//		multi_pix.max_y = scene.resolution_y / 2;
//	}
//	else if (id == 1)
//	{
//		multi_pix.min_x = 0;
//		multi_pix.max_x = scene.resolution_x /2;
//		multi_pix.min_y = 0;
//		multi_pix.max_y = scene.resolution_y / 2;
//	}
//	else if (id == 2)
//	{
//		multi_pix.min_x = -1 * scene.resolution_x / 2;
//		multi_pix.max_x = 0;
//		multi_pix.min_y = -1 * scene.resolution_y / 2;
//		multi_pix.max_y = 0;
//	}
//	else
//	{
//		multi_pix.min_x = 0;
//		multi_pix.max_x = scene.resolution_x / 2;
//		multi_pix.min_y = -1 * scene.resolution_y / 2;
//		multi_pix.max_y = 0;
//	}
//	return (multi_pix);
//}

//void	*render_thread(void *arg)
//{
//	t_minirt		*rt;
//	t_mult_pixel	m_pix;
//	int 			x;
//	int 			y;
//	t_vector		d;
//	t_color			color;
//
////	printf("this is pthread :%d\n", ((t_pthr_arg *)arg)->id);
//	rt = ((t_pthr_arg *)arg)->rt;
//	m_pix = get_multi_pix(rt->scene, ((t_pthr_arg *)arg)->id);
//	x = m_pix.min_x;
//	while (x < m_pix.max_x)
//	{
//		y = m_pix.min_y;
//		while (y < m_pix.max_y)
//		{
//			d = canvas_to_viewport(x, y, rt->scene);
//			color = trace_ray(rt->scene.origin, d, rt->scene);
//			rt_putpixel(x, y, color_to_int(color), rt);
//			y++;
//		}
//		x++;
//	}
//	return (NULL);
//}
//
//t_err	render_scene(t_minirt *rt)
//{
//	pthread_t	pthread[4];
//	t_pthr_arg	arg[4];
//	int			i;
//
//	i = 0;
//	while (i < 4)
//	{
//		arg[i].id = i;
//		arg[i].rt = rt;
//		i++;
//	}
//	i = 0;
////	pthread_create(&pthread[i], NULL, &render_thread, &arg[i]);
//	while (i < 4)
//	{
//		if (pthread_create(&pthread[i], NULL, &render_thread, &arg[i]))
//			printf("pthread id[%d] failed\n", i);
//		i++;
//	}
//	i = 0;
//	while (i < 4)
//	{
//		pthread_join(pthread[i], NULL);
//		i++;
//	}
//	return (NO_ERR);
//}
