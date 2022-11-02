#include <pthread.h>
#include <math.h>
#include <rt_datatypes.h>
#include <rt_render.h>
#include <rt_render_utils.h>
#include <rt_trace.h>
#include <rt_msaa.h>
#include <rt_color.h>
#include <rt_thread.h>
#include <stdio.h>

//t_multi_thr_pixels	get_multi_x(t_rt_scene *scene, t_multi_thr_pixels multi, int id)
//{
//	if (id / 2 > 2)
//	{
//		multi.min_x /= 2;
//		if (multi.min_x != 0)
//			multi.min_x++;
//		multi.max_x /= 2;
//		multi = get_multi_x(scene, multi, id / 2);
//	}
//
//	return (multi);
//}
//
//t_multi_thr_pixels	get_multi_y(t_rt_scene *scene, t_multi_thr_pixels multi, int id)
//{
//	if (id / 2 > 2)
//	{
//		multi.min_y /= 2;
//		if (multi.min_y != 0)
//			multi.min_y++;
//		multi.max_y /= 2;
//		multi = get_multi_y(scene, multi, id / 2);
//	}
//
//	return (multi);
//}

t_multi_thr_pixels	get_multi_pix(t_rt_scene *scene, int id)
{
	t_multi_thr_pixels	multi_pix;

	multi_pix.min_y = 0;
	multi_pix.max_y = scene->canvas.y - 1;
	if (id == 0)
	{
		multi_pix.min_x = 0;
		multi_pix.max_x = scene->canvas.x / scene->thread_amount;
		return(multi_pix);
	}
	else if (id == scene->thread_amount - 1)
	{
		multi_pix.min_x = (scene->canvas.x / scene->thread_amount) * id;
		multi_pix.max_x = scene->canvas.x;
		return (multi_pix);
	}
	multi_pix.min_x = (scene->canvas.x / scene->thread_amount) * id;
	multi_pix.max_x = multi_pix.min_x + scene->canvas.x / scene->thread_amount;
	return (multi_pix);
}

void	*render_thread(void *a)
{
	t_thread_arg		*arg;
	t_rt_resolution 	pixel;

	arg = (t_thread_arg *)a;
	pixel.y = arg->pixel.min_y;
	while (pixel.y < arg->pixel.max_y)
	{
		pixel.x = arg->pixel.min_x;
		while (pixel.x < arg->pixel.max_x)
		{
			if (arg->scene->msaa > 0 && !arg->scene->bare_toggle)
				arg->color = rand_multi_sample(arg->scene, pixel);
			else
				arg->color = trace_ray(init_rt_ray(arg->scene->cameras[0].coordinates, \
				canvas_to_viewport(pixel.x, pixel.y, arg->scene), 1, INFINITY), arg->scene, arg->scene->recursion_depth);
			mlx_put_pixel(arg->mlx->img, pixel.x, pixel.y, color_to_int(arg->color));
			pixel.x++;
		}
		pixel.y++;
	}
	arg->scene->frame_counter++;
	return (NULL);
}

void	init_t_thread_arg(t_thread_arg *arg, t_rt_mlx *mlx, t_rt_scene *scene, int index)
{
	arg->id = index;
	arg->scene = scene;
	arg->mlx = mlx;
	arg->pixel = get_multi_pix(scene, arg->id);
}

t_err	multi_thread(t_rt_mlx *mlx, t_rt_scene *scene)
{
	pthread_t		pthread[RT_MAX_THREADS];
	t_thread_arg	arg[RT_MAX_THREADS];
	t_time_stamp	start_of_frame;
	int				i;

	start_of_frame = set_time();
	i = 0;
	while (i < scene->thread_amount)
	{
		init_t_thread_arg(&arg[i], mlx, scene, i);
		if (pthread_create(&pthread[i], NULL, &render_thread, &arg[i]))
			printf("pthread_create id[%d] failed\n", i);
		i++;
	}
	i = 0;
	while (i < scene->thread_amount)
	{
		pthread_join(pthread[i], NULL);
		i++;
	}
	render_text(mlx, scene, ms_passed(start_of_frame));
	return (NO_ERR);
}
