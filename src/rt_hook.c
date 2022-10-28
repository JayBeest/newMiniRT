#include <unistd.h>
#include <MLX42.h>
#include <rt_datatypes.h>
#include <rt_render.h>

#include <pthread.h>
#include <stdio.h>

void	rt_resize(int x, int y, void *arg)
{
	t_mini_rt			*mini_rt;
	t_rt_mlx			*mlx;

	if (y < 100 || x < 100)
		return ;
	mini_rt = arg;
	mlx = &mini_rt->mlx;
	mini_rt->scene.canvas.x = x;
	mini_rt->scene.canvas.y = y;
	mini_rt->scene.aspect_ratio = (double)x / y;
	set_viewport(&mini_rt->scene.viewport, &mini_rt->scene.cameras[0], mini_rt->scene.aspect_ratio);
	mlx_resize_image(mlx->img, x, y);
	render_scene(mlx, &mini_rt->scene);
}

void	rt_hook(void *arg)
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
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
	{
		if (mini_rt->scene.objects[1].sphere.coordinates.x < 10)
		{
			mini_rt->scene.objects[1].sphere.coordinates.x += 1.0 / 8;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
	{
		if (mini_rt->scene.objects[1].sphere.coordinates.x > -10)
		{
			mini_rt->scene.objects[1].sphere.coordinates.x -= 1.0 / 8;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
	{
		if (mini_rt->scene.blue < 0.95)
		{
			mini_rt->scene.blue += 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
	{
		if (mini_rt->scene.blue > 0.05)
		{
			mini_rt->scene.blue -= 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
	{
		if (mini_rt->scene.green < 0.95)
		{
			mini_rt->scene.green += 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
	{
		if (mini_rt->scene.green > 0.05)
		{
			mini_rt->scene.green -= 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_Q))
	{
		if (mini_rt->scene.red < 0.95)
		{
			mini_rt->scene.red += 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_E))
	{
		if (mini_rt->scene.red > 0.05)
		{
			mini_rt->scene.red -= 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_EQUAL))
	{
		if (mini_rt->scene.spot_lights[2].intensity < 0.95)
		{
			mini_rt->scene.spot_lights[2].intensity += 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_MINUS))
	{
		if (mini_rt->scene.spot_lights[2].intensity > 0.05)
		{
			mini_rt->scene.spot_lights[2].intensity -= 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_0))
	{
		if (mini_rt->scene.objects[1].sphere.specular < 2000)
		{
			mini_rt->scene.objects[1].sphere.specular += 5;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_9))
	{
		if (mini_rt->scene.objects[1].sphere.specular > 0)
		{
			mini_rt->scene.objects[1].sphere.specular -= 5;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_7))
	{
		if (mini_rt->scene.spot_lights[0].coordinates.y < 20.0)
		{
			mini_rt->scene.spot_lights[0].coordinates.y += 0.5;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_8))
	{
		if (mini_rt->scene.spot_lights[0].coordinates.y > -10)
		{
			mini_rt->scene.spot_lights[0].coordinates.y	-= 0.5;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	usleep(150);
}
