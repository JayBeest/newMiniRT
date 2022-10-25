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
#include <rt_render_utils.h>
#include <rt_draw_utils.h>
#include <rt_color.h>
#include <rt_intersect.h>
//#include <rt_lighting.h>
#include <rt_time.h>
#include <math.h>

#include <pthread.h>
#include <stdio.h>


t_intersect_result	get_closest_intersection(t_rt_scene *scene, t_rt_vector o, t_rt_vector d, double t_min, double t_max)
{
	t_intersect_result	intersect_result;
	t_quad_result		quad_result;

	intersect_result.closest_obj = NULL;
	intersect_result.closest_t = INFINITY;
	int i = 0;
	while (i < scene->object_amount)
	{
//		if (node == self)
//		{
//			intersect_result.closest_t = INFINITY;
//			intersect_result.closest_shape = self;
//			node = node->next;
//			continue ;
//		}
		quad_result = intersect_shape(o, d, &scene->objects[i]);
		// if (quad_result.t1 < 1000 && quad_result.t1 > 1 && quad_result.t1 == quad_result.t2)
		// {
		// 	// printf(RED "edge found!!\n" RESET);
		// 	intersect_result.closest_t = quad_result.t1;
		// 	intersect_result.closest_shape = node;
		// }
		// else
		// {
			if (quad_result.t1 > t_min && quad_result.t1 < t_max && quad_result.t1 < intersect_result.closest_t)
			{
//				if (node == self)
//					intersect_result.closest_t = INFINITY;
//				else
					intersect_result.closest_t = quad_result.t1;
				intersect_result.closest_obj = &scene->objects[i];
			}
			if (quad_result.t2 > t_min && quad_result.t2 < t_max && quad_result.t2 < intersect_result.closest_t)
			{
//				if (node == self)
//					intersect_result.closest_t = INFINITY;
//				else
					intersect_result.closest_t = quad_result.t2;
				intersect_result.closest_obj = &scene->objects[i];			}
		// }
		i++;
	}
	return (intersect_result);
}

t_rt_color	trace_ray(t_rt_vector o, t_rt_vector d, t_rt_scene *scene)
{
	t_intersect_result	intersect_result;

	ft_bzero(&intersect_result, sizeof(intersect_result));
	intersect_result = get_closest_intersection(scene, o, d, 1, INFINITY);
	if (!intersect_result.closest_obj)
		return ((t_rt_color){0, 0, 0, 255});
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
//			color = all_the_colors(pixel, scene);
			t_rt_vector D = canvas_to_viewport(pixel.x, pixel.y, scene);
			color = trace_ray((t_rt_vector){0,0,0}, D, scene);
			if (color.r == 0 && color.g == 0 && color.b == 0 && color.a == 255)
				color = all_the_colors(pixel, scene);
//			color = trace_ray(scene->cameras[0].coordinates, D, scene);
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
