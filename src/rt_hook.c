#include <unistd.h>
#include <math.h>
#include <MLX42.h>
#include <rt_datatypes.h>
#include <rt_render.h>
#include <rt_vector_utils.h>

#include <pthread.h>
#include <stdio.h>

void	rt_resize_hook(int x, int y, void *arg)
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

void	rt_mouse_hook(enum mouse_key e_key, enum action e_action, enum modifier_key e_modifier, void *arg)
{
	t_mini_rt			*mini_rt;
	t_rt_mlx			*mlx;
	t_rt_resolution		mouse;

	mini_rt = arg;
	mlx = &mini_rt->mlx;
	if (e_key == MLX_MOUSE_BUTTON_LEFT && e_action == MLX_PRESS)
	{
		mlx_get_mouse_pos(mlx->mlx, &mouse.x, &mouse.y);
//		printf("mouse - x: %d  y: %d\n", mouse.x, mouse.y);
//		printf("  - converted - x: %f  y: %f\n", (double)(mini_rt->scene.canvas.x / -2 + mouse.x) / (mini_rt->scene.canvas.x / 2), (double)(mini_rt->scene.canvas.y / -2 + mouse.y) / (mini_rt->scene.canvas.y / -2));
		mini_rt->scene.cameras[0].orientation = rotate_vector_x(mini_rt->scene.cameras[0].orientation, (double)(mini_rt->scene.canvas.x / -2 + mouse.x) / (mini_rt->scene.canvas.x / 2) * M_PI );
		mini_rt->scene.cameras[0].orientation = rotate_vector_y(mini_rt->scene.cameras[0].orientation, (double)(mini_rt->scene.canvas.y / -2 + mouse.y) / (mini_rt->scene.canvas.y / -2) * M_PI );
		set_viewport(&mini_rt->scene.viewport, &mini_rt->scene.cameras[0], mini_rt->scene.aspect_ratio);
		render_scene(mlx, &mini_rt->scene);
	}
	(void)e_key;
	(void)e_action;
	(void)e_modifier;
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
		if (mini_rt->scene.bg_color.z < 0.95)
		{
			mini_rt->scene.bg_color.z += 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
	{
		if (mini_rt->scene.bg_color.z > 0.05)
		{
			mini_rt->scene.bg_color.z -= 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
	{
		if (mini_rt->scene.bg_color.y < 0.95)
		{
			mini_rt->scene.bg_color.y += 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
	{
		if (mini_rt->scene.bg_color.y > 0.05)
		{
			mini_rt->scene.bg_color.y -= 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_I))
	{
		if (mini_rt->scene.cameras[0].coordinates.z < 100)
		{
			mini_rt->scene.cameras[0].coordinates.z += CAMERA_MOVE_STEP;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_K))
	{
		if (mini_rt->scene.cameras[0].coordinates.z > -100)
		{
			mini_rt->scene.cameras[0].coordinates.z -= CAMERA_MOVE_STEP;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_L))
	{
		if (mini_rt->scene.cameras[0].coordinates.x < 100)
		{
			mini_rt->scene.cameras[0].coordinates.x += CAMERA_MOVE_STEP;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_J))
	{
		if (mini_rt->scene.cameras[0].coordinates.x > -100)
		{
			mini_rt->scene.cameras[0].coordinates.x -= CAMERA_MOVE_STEP;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_U))
	{
		if (mini_rt->scene.cameras[0].coordinates.y < 100)
		{
			mini_rt->scene.cameras[0].coordinates.y += CAMERA_MOVE_STEP;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_M))
	{
		if (mini_rt->scene.cameras[0].coordinates.y > -100)
		{
			mini_rt->scene.cameras[0].coordinates.y -= CAMERA_MOVE_STEP;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}

	if (mlx_is_key_down(mlx->mlx, MLX_KEY_Q))
	{
		if (mini_rt->scene.bg_color.x < 0.95)
		{
			mini_rt->scene.bg_color.x += 0.05;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_E))
	{
		if (mini_rt->scene.bg_color.x > 0.05)
		{
			mini_rt->scene.bg_color.x -= 0.05;
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

	mini_rt
}
