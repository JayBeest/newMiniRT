#include <MLX42.h>
#include <rt_datatypes.h>
#include <rt_render.h>
#include <rt_render_utils.h>

void	hook(void *arg)
{
	t_mini_rt	*mini_rt;
	t_rt_mlx	*mlx;

	mini_rt = arg;
	mlx = &mini_rt->mlx;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_UP))
	{
		if (mini_rt->scene.cameras[0].fov < 180)
		{
			mini_rt->scene.cameras[0].fov += 1;
			set_viewport(&mini_rt->scene.viewport, &mini_rt->scene.cameras[0], mini_rt->scene.aspect_ratio);
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
	{
		if (mini_rt->scene.cameras[0].fov > 0)
		{
			mini_rt->scene.cameras[0].fov -= 1;
			set_viewport(&mini_rt->scene.viewport, &mini_rt->scene.cameras[0], mini_rt->scene.aspect_ratio);
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
	{
		if (mini_rt->scene.blue < 0.95f)
		{
			mini_rt->scene.blue += 0.05f;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
	{
		if (mini_rt->scene.blue > 0.05f)
		{
			mini_rt->scene.blue -= 0.05f;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
}
