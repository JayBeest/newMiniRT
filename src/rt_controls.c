#include <rt_datatypes.h>
#include <rt_render.h>

void	rt_controls(t_rt_mlx *mlx, t_rt_scene *scene)
{
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_UP))
	{
		if (scene->cameras[0].fov < 180)
		{
			scene->cameras[0].fov += 1;
			set_viewport(&scene->viewport, &scene->cameras[0], scene->aspect_ratio);
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
	{
		if (scene->cameras[0].fov > 0)
		{
			scene->cameras[0].fov -= 1;
			set_viewport(&scene->viewport, &scene->cameras[0], scene->aspect_ratio);
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
	{
		if (scene->objects[1].sphere.coordinates.x < 10)
		{
			scene->objects[1].sphere.coordinates.x += 1.0 / 8;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
	{
		if (scene->objects[1].sphere.coordinates.x > -10)
		{
			scene->objects[1].sphere.coordinates.x -= 1.0 / 8;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
	{
		if (scene->bg_color.z < 0.95)
		{
			scene->bg_color.z += 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
	{
		if (scene->bg_color.z > 0.05)
		{
			scene->bg_color.z -= 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
	{
		if (scene->bg_color.y < 0.95)
		{
			scene->bg_color.y += 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
	{
		if (scene->bg_color.y > 0.05)
		{
			scene->bg_color.y -= 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_I))
	{
		if (scene->cameras[0].coordinates.z < 100)
		{
			scene->cameras[0].coordinates.z += CAMERA_MOVE_STEP;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_K))
	{
		if (scene->cameras[0].coordinates.z > -100)
		{
			scene->cameras[0].coordinates.z -= CAMERA_MOVE_STEP;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_L))
	{
		if (scene->cameras[0].coordinates.x < 100)
		{
			scene->cameras[0].coordinates.x += CAMERA_MOVE_STEP;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_J))
	{
		if (scene->cameras[0].coordinates.x > -100)
		{
			scene->cameras[0].coordinates.x -= CAMERA_MOVE_STEP;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_U))
	{
		if (scene->cameras[0].coordinates.y < 100)
		{
			scene->cameras[0].coordinates.y += CAMERA_MOVE_STEP;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_M))
	{
		if (scene->cameras[0].coordinates.y > -100)
		{
			scene->cameras[0].coordinates.y -= CAMERA_MOVE_STEP;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_Q))
	{
		if (scene->bg_color.x < 0.95)
		{
			scene->bg_color.x += 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_E))
	{
		if (scene->bg_color.x > 0.05)
		{
			scene->bg_color.x -= 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_EQUAL))
	{
		if (scene->spot_lights[2].intensity < 0.95)
		{
			scene->spot_lights[2].intensity += 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_MINUS))
	{
		if (scene->spot_lights[2].intensity > 0.05)
		{
			scene->spot_lights[2].intensity -= 0.05;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_0))
	{
		if (scene->objects[1].sphere.specular < 2000)
		{
			scene->objects[1].sphere.specular += 5;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_9))
	{
		if (scene->objects[1].sphere.specular > 0)
		{
			scene->objects[1].sphere.specular -= 5;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_7))
	{
		if (scene->spot_lights[0].coordinates.y < 20.0)
		{
			scene->spot_lights[0].coordinates.y += 0.5;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_8))
	{
		if (scene->spot_lights[0].coordinates.y > -10)
		{
			scene->spot_lights[0].coordinates.y	-= 0.5;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_PAGE_UP))
	{
		scene->objects[5].sphere.reflective += 0.01f;
		if (scene->objects[5].sphere.reflective > 1)
			scene->objects[5].sphere.reflective = 1;
		render_scene(mlx, scene);
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_PAGE_DOWN))
	{
		scene->objects[5].sphere.reflective	-= 0.01f;
		if (scene->objects[5].sphere.reflective < 0)
			scene->objects[5].sphere.reflective = 0;
		render_scene(mlx, scene);
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_INSERT))
	{
		if (scene->recursion_depth < 50)
		{
			scene->recursion_depth += 1;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DELETE))
	{
		if (scene->recursion_depth > 0)
		{
			scene->recursion_depth	-= 1;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_INSERT))
	{
		if (scene->recursion_depth < 50)
		{
			scene->recursion_depth += 1;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DELETE))
	{
		if (scene->recursion_depth > 0)
		{
			scene->recursion_depth	-= 1;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_Z))
	{
		if (scene->viewport.height < 30)
		{
			scene->viewport.height += 0.1;
			scene->viewport.width += 0.1 * scene->aspect_ratio;
			render_scene(mlx, scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_X))
	{
		if (scene->viewport.height > 0.2)
		{
			scene->viewport.height	-= 0.1;
			scene->viewport.width	-= 0.1 * scene->aspect_ratio;
			render_scene(mlx, scene);
		}
	}
}
