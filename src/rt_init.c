#include <math.h>
#include <libft.h>
#include <rt_datatypes.h>

t_err	rt_mlx_init(t_rt_mlx *mlx, t_rt_scene_size resolution)
{
	mlx->mlx = mlx_init(resolution.width, resolution.height, "miniRT", true);
	if (!mlx->mlx)
		return (MLX_INIT_F);
	mlx->img = mlx_new_image(mlx->mlx, resolution.width, resolution.height);
	if (!mlx->img)
		return (MLX_NEW_IMG_F);
	mlx->text = mlx_new_image(mlx->mlx, resolution.width, resolution.height);
	if (!mlx->text)
		return (MLX_NEW_IMG_F);
	return (NO_ERR);
}

t_err	init_rt(t_mini_rt *mini_rt)
{
	ft_bzero(mini_rt, sizeof(t_mini_rt));
	mini_rt->scene.blue = 0.25f;
	mini_rt->scene.aspect_ratio = 16.0f / 9.0f;
	mini_rt->scene.size.width = IMAGE_WIDTH;
	mini_rt->scene.size.height = IMAGE_WIDTH / mini_rt->scene.aspect_ratio;
	return (rt_mlx_init(&mini_rt->mlx, mini_rt->scene.size));
}

void	init_mock_rt(t_rt_scene *scene)
{
	scene->ambient_light.intensity = 0.2f;
	scene->ambient_light.color = (t_rt_color){255, 255, 255, 255};

	scene->cameras[0].coordinates = (t_rt_point){-50, 0, 20};
	scene->cameras[0].orientation = (t_rt_vector){0, 0, 0};
	scene->cameras[0].fov = 70;
	scene->spot_lights[0].coordinates = (t_rt_point){-40, 0, 30};
	scene->spot_lights[0].intensity = 0.7f;
	scene->spot_lights[0].color = (t_rt_color){255, 255, 255, 255};

	scene->objects[0].plane.type = PLANE;
	scene->objects[0].plane.coordinates = (t_rt_point){0, 0, 0};
	scene->objects[0].plane.orientation = (t_rt_vector){0, 1.0f, 0};
	scene->objects[0].plane.color = (t_rt_color){255, 0, 255, 255};
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_rt_point){0, 0, 20};
	scene->objects[1].sphere.diameter = 20;
	scene->objects[1].sphere.color = (t_rt_color){255, 0, 0, 255};
	scene->objects[1].cylinder.type = CYLINDER;
	scene->objects[2].cylinder.coordinates = (t_rt_point){50.0f, 0.0f, 20.6f};
	scene->objects[2].cylinder.orientation = (t_rt_vector){0, 0, 1.0f};
	scene->objects[2].cylinder.diameter = 14.2f;
	scene->objects[2].cylinder.height = 21.42f;
	scene->objects[2].cylinder.color = (t_rt_color){10, 0, 255, 255};
}
