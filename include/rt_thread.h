#ifndef RT_THREAD_H
# define RT_THREAD_H

typedef struct s_thread_arg
{
	int			id;
	t_scene		*scene;
	t_mlx		*mlx;
}			t_thread_arg;

t_err	multi_thread(t_mlx *mlx, t_scene *scene);

#endif
