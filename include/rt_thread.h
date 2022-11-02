#ifndef RT_THREAD_H
# define RT_THREAD_H

typedef struct s_multi_thr_pixels
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}			t_multi_thr_pixels;

typedef struct s_thread_arg
{
	int					id;
	t_rt_scene			*scene;
	t_rt_mlx			*mlx;
	t_multi_thr_pixels	pixel;
	t_rt_color			color;
}			t_thread_arg;

t_err	multi_thread(t_rt_mlx *mlx, t_rt_scene *scene);

#endif
