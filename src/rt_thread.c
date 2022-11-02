#include <pthread.h>
#include <rt_datatypes.h>
#include <rt_render.h>
#include <rt_thread.h>
#include <stdio.h>

t_canvas_size	get_multi_threaded_canvas(t_scene *scene, int id)
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
	t_canvas_size		canvas;

	arg = (t_thread_arg *)a;
	canvas = get_multi_threaded_canvas(arg->scene, arg->id);
	return((void *)single_thread(arg->mlx, arg->scene, canvas));
}

t_err	multi_thread(t_mlx *mlx, t_scene *scene)
{
	pthread_t		pthread[RT_MAX_THREADS];
	t_thread_arg	arg[RT_MAX_THREADS];
	int				i;

	i = 0;
	while (i < scene->thread_amount)
	{
		arg[i].id = i;
		arg[i].scene = scene;
		arg[i].mlx = mlx;
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
	return (NO_ERR);
}
