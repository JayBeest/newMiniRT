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
//	mlx->text = mlx_new_image(mlx->mlx, resolution.x, resolution.y);
//	if (!mlx->text)
//		return (MLX_NEW_IMG_F);
	return (NO_ERR);
}

t_err	init_rt(t_mini_rt *mini_rt)
{
	ft_bzero(mini_rt, sizeof(t_mini_rt));
	mini_rt->scene.red = 0.5;
	mini_rt->scene.green = 0.7;
	mini_rt->scene.blue = 1.0;
//	mini_rt->scene.aspect_ratio = 1;
	mini_rt->scene.aspect_ratio = 4.0 / 3.0;
//	mini_rt->scene.aspect_ratio = 16.0 / 9.0;
//	mini_rt->scene.aspect_ratio = 9.0 / 16.0;
//	mini_rt->scene.aspect_ratio = 16.0 / 10.0;
//	mini_rt->scene.aspect_ratio = 21.0 / 9.0;
//	mini_rt->scene.aspect_ratio = 32.0 / 9.0;
	mini_rt->scene.canvas.x = IMAGE_WIDTH;
	mini_rt->scene.canvas.y = IMAGE_WIDTH / mini_rt->scene.aspect_ratio;
	return (rt_mlx_init(&mini_rt->mlx, mini_rt->scene.canvas));
}

void	init_mock_rt(t_rt_scene *scene)
{
	scene->ambient_light.intensity = 0.2;
	scene->ambient_light.color = (t_rt_color){255, 255, 255, 255};

	scene->cameras[0].coordinates = (t_rt_vector){-50, 0, 20};
	scene->cameras[0].orientation = (t_rt_vector){0, 0, 0};
	scene->cameras[0].fov = 70;
	scene->spot_lights[0].coordinates = (t_rt_vector){-40, 0, 30};
	scene->spot_lights[0].intensity = 0.7;
	scene->spot_lights[0].color = (t_rt_color){255, 255, 255, 255};

	scene->objects[0].plane.type = PLANE;
	scene->objects[0].plane.coordinates = (t_rt_vector){0, 0, 0};
	scene->objects[0].plane.orientation = (t_rt_vector){0, 1.0, 0};
	scene->objects[0].plane.color = (t_rt_color){255, 0, 255, 255};
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_rt_vector){0, 0, 20};
	scene->objects[1].sphere.radius = 20.0 / 2;
	scene->objects[1].sphere.color = (t_rt_color){255, 0, 0, 255};
//	scene->objects[2].cylinder.type = CYLINDER;
//	scene->objects[2].cylinder.coordinates = (t_rt_vector){50.0, 0.0, 20.6};
//	scene->objects[2].cylinder.orientation = (t_rt_vector){0, 0, 1.0};
//	scene->objects[2].cylinder.radius = 14.2.0 / 2;
//	scene->objects[2].cylinder.height = 21.42;
//	scene->objects[2].cylinder.color = (t_rt_color){10, 0, 255, 255};
}

void	init_new_rt(t_rt_scene *scene)
{
	scene->ambient_light.intensity = 0.2;
	scene->ambient_light.color = (t_rt_color){255, 255, 255, 255};

	scene->cameras[0].coordinates = (t_rt_vector){-50, 0, 20};
	scene->cameras[0].orientation = (t_rt_vector){0, 0, 0};
	scene->cameras[0].fov = 100;
	scene->spot_lights[0].coordinates = (t_rt_vector){0, 20, 0};
	scene->spot_lights[0].intensity = 0.5;
	scene->spot_lights[0].color = (t_rt_color){255, 255, 255, 255};
	scene->spot_lights[1].coordinates = (t_rt_vector){0.8, 15, -3.5};
	scene->spot_lights[1].intensity = 0.3;
	scene->spot_lights[1].color = (t_rt_color){255, 255, 255, 255};
	scene->spot_lights[2].coordinates = (t_rt_vector){0, 5, -3};
	scene->spot_lights[2].intensity = 0;
	scene->spot_lights[2].color = (t_rt_color){255, 196, 23, 255};

	scene->objects[0].sphere.type = SPHERE;
	scene->objects[0].sphere.coordinates = (t_rt_vector){0, -1, 3}; // red
	scene->objects[0].sphere.radius = 1.0 / 2;
	scene->objects[0].sphere.color = (t_rt_color){255, 0, 0, 255};
	scene->objects[0].sphere.specular = 500;
	scene->objects[0].sphere.reflective = 0;
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_rt_vector){2, 1, 3}; // blue
	scene->objects[1].sphere.radius = 2.0 / 2;
	scene->objects[1].sphere.color = (t_rt_color){0, 0, 255, 255};
	scene->objects[1].sphere.specular = 5;
	scene->objects[1].sphere.reflective = 0;
	scene->objects[2].sphere.type = SPHERE;
	scene->objects[2].sphere.coordinates = (t_rt_vector){-2, 0, 4}; // green
	scene->objects[2].sphere.radius = 1.0 / 2;
	scene->objects[2].sphere.color = (t_rt_color){0, 255, 0, 255};
	scene->objects[2].sphere.specular = 1000;
	scene->objects[2].sphere.reflective = 0.5f;
	scene->objects[3].sphere.type = SPHERE;
	scene->objects[3].sphere.coordinates = (t_rt_vector){-0.5, 0.25, 32}; // turquoise
	scene->objects[3].sphere.radius = 2.0 / 2;
	scene->objects[3].sphere.specular = 300;
	scene->objects[3].sphere.reflective = 0.4f;
	scene->objects[3].sphere.color = (t_rt_color){64, 200, 128, 255};
	scene->objects[4].sphere.type = SPHERE;
	scene->objects[4].sphere.coordinates = (t_rt_vector){0, -198, -10}; // purple
	scene->objects[4].sphere.radius = 195.0;
	scene->objects[4].sphere.color = (t_rt_color){128, 64, 196, 255};
	scene->objects[4].sphere.specular = 0;
	scene->objects[4].sphere.reflective = 0;
	scene->objects[5].sphere.type = SPHERE;
	scene->objects[5].sphere.coordinates = (t_rt_vector){1.85, -1.5, 3.3}; // yellow
	scene->objects[5].sphere.radius = 3.6 / 2;
	scene->objects[5].sphere.color = (t_rt_color){255, 255, 0, 255};
	scene->objects[5].sphere.specular = 0;
	scene->objects[5].sphere.reflective = 0;
}
