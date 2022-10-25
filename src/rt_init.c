//#include <math.h>
#include <libft.h>
#include <rt_datatypes.h>

t_err	rt_mlx_init(t_rt_mlx *mlx, t_rt_resolution resolution)
{
	mlx->mlx = mlx_init(resolution.x, resolution.y, "miniRT", true);
	if (!mlx->mlx)
		return (MLX_INIT_F);
	mlx->img = mlx_new_image(mlx->mlx, resolution.x, resolution.y);
	if (!mlx->img)
		return (MLX_NEW_IMG_F);
	mlx->text = mlx_new_image(mlx->mlx, resolution.x, resolution.y);
	if (!mlx->text)
		return (MLX_NEW_IMG_F);
	return (NO_ERR);
}

t_err	init_rt(t_mini_rt *mini_rt)
{
	ft_bzero(mini_rt, sizeof(t_mini_rt));
	mini_rt->scene.red = 0.5f;
	mini_rt->scene.green = 0.7f;
	mini_rt->scene.blue = 1.0f;
//	mini_rt->scene.aspect_ratio = 1;
//	mini_rt->scene.aspect_ratio = 4.0f / 3.0f;
	mini_rt->scene.aspect_ratio = 16.0f / 9.0f;
//	mini_rt->scene.aspect_ratio = 16.0f / 10.0f;
//	mini_rt->scene.aspect_ratio = 21.0f / 9.0f;
//	mini_rt->scene.aspect_ratio = 32.0f / 9.0f;
	mini_rt->scene.canvas.x = IMAGE_WIDTH;
	mini_rt->scene.canvas.y = IMAGE_WIDTH / mini_rt->scene.aspect_ratio;
	return (rt_mlx_init(&mini_rt->mlx, mini_rt->scene.canvas));
}

void	init_mock_rt(t_rt_scene *scene)
{
	scene->ambient_light.intensity = 0.2f;
	scene->ambient_light.color = (t_rt_color){255, 255, 255, 255};

	scene->cameras[0].coordinates = (t_rt_vector){-50, 0, 20};
	scene->cameras[0].orientation = (t_rt_vector){0, 0, 0};
	scene->cameras[0].fov = 70;
	scene->spot_lights[0].coordinates = (t_rt_vector){-40, 0, 30};
	scene->spot_lights[0].intensity = 0.7f;
	scene->spot_lights[0].color = (t_rt_color){255, 255, 255, 255};

	scene->objects[0].plane.type = PLANE;
	scene->objects[0].plane.coordinates = (t_rt_vector){0, 0, 0};
	scene->objects[0].plane.orientation = (t_rt_vector){0, 1.0f, 0};
	scene->objects[0].plane.color = (t_rt_color){255, 0, 255, 255};
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_rt_vector){0, 0, 20};
	scene->objects[1].sphere.diameter = 20;
	scene->objects[1].sphere.color = (t_rt_color){255, 0, 0, 255};
//	scene->objects[2].cylinder.type = CYLINDER;
//	scene->objects[2].cylinder.coordinates = (t_rt_vector){50.0f, 0.0f, 20.6f};
//	scene->objects[2].cylinder.orientation = (t_rt_vector){0, 0, 1.0f};
//	scene->objects[2].cylinder.diameter = 14.2f;
//	scene->objects[2].cylinder.height = 21.42f;
//	scene->objects[2].cylinder.color = (t_rt_color){10, 0, 255, 255};
}

void	init_new_rt(t_rt_scene *scene)
{
	scene->ambient_light.intensity = 0.2f;
	scene->ambient_light.color = (t_rt_color){255, 255, 255, 255};

	scene->cameras[0].coordinates = (t_rt_vector){-50, 0, 20};
	scene->cameras[0].orientation = (t_rt_vector){0, 0, 0};
	scene->cameras[0].fov = 135;
	scene->spot_lights[0].coordinates = (t_rt_vector){0, 20, 0};
	scene->spot_lights[0].intensity = 0.6f;
	scene->spot_lights[0].color = (t_rt_color){255, 255, 255, 255};
	scene->spot_lights[1].coordinates = (t_rt_vector){0.8f, 15, -3.5f};
	scene->spot_lights[1].intensity = 0.5f;
	scene->spot_lights[1].color = (t_rt_color){255, 255, 255, 255};

	scene->objects[0].sphere.type = SPHERE;
	scene->objects[0].sphere.coordinates = (t_rt_vector){0, -1, 3}; // red
	scene->objects[0].sphere.diameter = 1;
	scene->objects[0].sphere.color = (t_rt_color){255, 0, 0, 255};
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_rt_vector){2, 0, 4}; // blue
	scene->objects[1].sphere.diameter = 2;
	scene->objects[1].sphere.color = (t_rt_color){0, 0, 255, 255};
	scene->objects[2].sphere.type = SPHERE;
	scene->objects[2].sphere.coordinates = (t_rt_vector){-2, 0, 4}; // green
	scene->objects[2].sphere.diameter = 1;
	scene->objects[2].sphere.color = (t_rt_color){0, 255, 0, 255};
	scene->objects[3].sphere.type = SPHERE;
	scene->objects[3].sphere.coordinates = (t_rt_vector){-0.5f, 0.25f, 32}; // turquoise
	scene->objects[3].sphere.diameter = 2;
	scene->objects[3].sphere.color = (t_rt_color){64, 200, 128, 255};
	scene->objects[4].sphere.type = SPHERE;
	scene->objects[4].sphere.coordinates = (t_rt_vector){0, -100, 10}; // purple
	scene->objects[4].sphere.diameter = 195;
	scene->objects[4].sphere.color = (t_rt_color){128, 64, 196, 255};
}
