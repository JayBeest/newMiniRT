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

t_canvas_size	get_multi_pix(t_scene *scene, int id)
{
	t_canvas_size	multi_pix;

	multi_pix.min.y = 0;
	multi_pix.max.y = scene->canvas.y - 1;
	if (id == 0)
	{
		multi_pix.min.x = 0;
		multi_pix.max.x = scene->canvas.x / scene->thread_amount;
		return (multi_pix);
	}
	else if (id == scene->thread_amount - 1)
	{
		multi_pix.min.x = (scene->canvas.x / scene->thread_amount) * id;
		multi_pix.max.x = scene->canvas.x;
		return (multi_pix);
	}
	multi_pix.min.x = (scene->canvas.x / scene->thread_amount) * id;
	multi_pix.max.x = multi_pix.min.x + scene->canvas.x / scene->thread_amount;
	return (multi_pix);
}


void	*render_thread(void *a)
{
	t_thread_arg		*arg;
	t_resolution		pixel;
	t_canvas_size		canvas;

	arg = (t_thread_arg *)a;
	canvas = get_multi_pix(arg->scene, arg->id);
	pixel.y = canvas.min.y;
	while (pixel.y < canvas.max.y)
	{
		pixel.x = canvas.min.x;
		while (pixel.x < canvas.max.x)
		{
			render_pixel(pixel, arg->mlx, arg->scene);
			pixel.x++;
		}
		pixel.y++;
	}
	arg->scene->frame_counter++;
	return (NULL);
}

void	init_t_thread_arg(t_thread_arg *arg, t_mlx *mlx, \
	t_scene *scene, int index)
{
	arg->id = index;
	arg->scene = scene;
	arg->mlx = mlx;
}

t_err	multi_thread(t_mlx *mlx, t_scene *scene)
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
