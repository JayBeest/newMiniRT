/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_init.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:22:56 by jcorneli      #+#    #+#                 */
/*   Updated: 2023/04/28 00:26:44 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_datatypes.h>

#include <stdio.h>


t_err	rt_mlx_init(t_mlx *mlx, t_resolution resolution)
{
	mlx->mlx = mlx_init(resolution.x, resolution.y, "miniRT", true);
	if (!mlx->mlx)
		return (MLX_INIT_F);
	mlx->img = mlx_new_image(mlx->mlx, resolution.x, resolution.y);

	printf("\nNEW IMAGE SIZE - x: %d y: %d\n\n", resolution.x, resolution.y);

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
	mini_rt->scene.bg_color.x = 0.5;
	mini_rt->scene.bg_color.y = 0.7;
	mini_rt->scene.bg_color.z = 1.0;
//	mini_rt->scene.aspect_ratio = 1;
//	mini_rt->scene.aspect_ratio = 4.0 / 3.0;
//	mini_rt->scene.aspect_ratio = 16.0 / 9.0;
//	mini_rt->scene.aspect_ratio = 9.0 / 16.0;
	mini_rt->scene.aspect_ratio = 16.0 / 10.0;
//	mini_rt->scene.aspect_ratio = 21.0 / 9.0;
//	mini_rt->scene.aspect_ratio = 32.0 / 9.0;
	mini_rt->scene.canvas.x = IMAGE_WIDTH;
	mini_rt->scene.canvas.y = IMAGE_WIDTH / mini_rt->scene.aspect_ratio;
	mini_rt->scene.viewport.height = 2.0f;

	mini_rt->scene.recursion_depth = 0;
	mini_rt->scene.msaa = MULTI_SAMPLE;
	rt_mlx_init(&mini_rt->mlx, mini_rt->scene.canvas);
	mini_rt->scene.hud = 1;
	mini_rt->scene.bare_toggle = false;
	mini_rt->scene.thread_amount = RT_THREADS;
	mini_rt->scene.fps = FPS;
	return (NO_ERR);

}

void	init_mock_rt(t_scene *scene)
{
	scene->ambient_light.intensity = 0.2;
	scene->ambient_light.color = (t_color){255, 255, 255, 255};

	scene->cameras[0].coordinates = (t_vector){-50, 0, 20};
	scene->cameras[0].orientation = (t_vector){0, 0, 0};
	scene->cameras[0].fov = 70;
	scene->cameras[0].zoom_level = 0;
	scene->lights[0].coordinates = (t_vector){-40, 0, 30};
	scene->lights[0].intensity = 0.7;
	scene->lights[0].color = (t_color){255, 255, 255, 255};

	scene->objects[0].plane.type = PLANE;
	scene->objects[0].plane.coordinates = (t_vector){0, 0, 0};
	scene->objects[0].plane.orientation = (t_vector){0, 1.0, 0};
	scene->objects[0].plane.color = (t_color){255, 0, 255, 255};
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_vector){0, 0, 20};
	scene->objects[1].sphere.radius = 20.0 / 2;
	scene->objects[1].sphere.color = (t_color){255, 0, 0, 255};
//	scene->objects[2].cylinder.type = CYLINDER;
//	scene->objects[2].cylinder.coordinates = (t_rt_vector){50.0, 0.0, 20.6};
//	scene->objects[2].cylinder.orientation = (t_rt_vector){0, 0, 1.0};
//	scene->objects[2].cylinder.radius = 14.2.0 / 2;
//	scene->objects[2].cylinder.height = 21.42;
//	scene->objects[2].cylinder.color = (t_rt_color){10, 0, 255, 255};
}

void	init_new_rt(t_scene *scene)
{
	scene->ambient_light.intensity = 0.1;
	scene->ambient_light.color = (t_color){255, 255, 255, 255};

	scene->cameras[0].coordinates = (t_vector){0, -1, -5};
	scene->cameras[0].orientation = (t_vector){0, 0, 0};
	scene->cameras[0].fov = 70;
	scene->cameras[0].zoom_level = 1;

	scene->lights[0].type = POINT;
	scene->lights[0].coordinates = (t_vector){0, 20, 4};
	scene->lights[0].intensity = 0.4;
	scene->lights[0].color = (t_color){255, 255, 255, 255};
	scene->lights[1].type = POINT;
	scene->lights[1].coordinates = (t_vector){0.8, 15, -3.5};
	scene->lights[1].intensity = 0.3;
	scene->lights[1].color = (t_color){255, 255, 255, 255};
	scene->lights[2].type = POINT;
	scene->lights[2].coordinates = (t_vector){0, 5, -3};
	scene->lights[2].intensity = 0.1;
	scene->lights[2].color = (t_color){255, 196, 23, 255};
	scene->lights[0].toggle = true;
	scene->lights[1].toggle = true;
	scene->lights[2].toggle = true;

	scene->objects[0].sphere.type = SPHERE;
	scene->objects[0].sphere.coordinates = (t_vector){0, -1, 3}; // red
	scene->objects[0].sphere.radius = 1.0 / 2;
	scene->objects[0].sphere.color = (t_color){255, 0, 0, 255};
	scene->objects[0].sphere.specular = 80;
	scene->objects[0].sphere.reflective = 0.6f;
	scene->objects[0].sphere.metal_fuzz = 0;
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_vector){2, 1, 3}; // blue
	scene->objects[1].sphere.radius = 2.0 / 2;
	scene->objects[1].sphere.color = (t_color){0, 0, 255, 255};
	scene->objects[1].sphere.specular = 3;
	scene->objects[1].sphere.reflective = 0.9f; //0.35f;
	scene->objects[1].sphere.metal_fuzz = 0;
	scene->objects[2].sphere.type = SPHERE;
	scene->objects[2].sphere.coordinates = (t_vector){-2, 0, 4}; // green
	scene->objects[2].sphere.radius = 1.0 / 2;
	scene->objects[2].sphere.color = (t_color){0, 255, 0, 255};
	scene->objects[2].sphere.specular = 1000;
	scene->objects[2].sphere.reflective = 0.3f;
	scene->objects[2].sphere.metal_fuzz = 0;
	scene->objects[3].sphere.type = SPHERE;
	scene->objects[3].sphere.coordinates = (t_vector){-0.5, 0.25, 32}; // turquoise
	scene->objects[3].sphere.radius = 2.0 / 2;
	scene->objects[3].sphere.specular = 300;
	scene->objects[3].sphere.reflective = 1;
	scene->objects[3].sphere.metal_fuzz = 0;
	scene->objects[3].sphere.color = (t_color){64, 200, 128, 255};
	scene->objects[4].sphere.type = SPHERE;
	scene->objects[4].sphere.coordinates = (t_vector){0, -198, -10}; // purple
	scene->objects[4].sphere.radius = 195.0;
	scene->objects[4].sphere.color = (t_color){128, 64, 196, 255};
	scene->objects[4].sphere.specular = 0;
	scene->objects[4].sphere.reflective = 0.01f;
	scene->objects[4].sphere.metal_fuzz = 0;
	scene->objects[5].sphere.type = SPHERE;
	scene->objects[5].sphere.coordinates = (t_vector){1.85, -1.5, 3.3}; // yellow
	scene->objects[5].sphere.radius = 3.6 / 2;
	scene->objects[5].sphere.color = (t_color){255, 255, 0, 255};
	scene->objects[5].sphere.specular = 0;
	scene->objects[5].sphere.reflective = 0.8f;
	scene->objects[5].sphere.metal_fuzz = 0;
	scene->objects[6].plane.type = PLANE;
	scene->objects[6].plane.coordinates = (t_vector){0, -4, 0};
	scene->objects[6].plane.orientation = (t_vector){1, 1, 0};
	scene->objects[6].plane.color = (t_color){255, 255, 255, 255};
	scene->objects[6].plane.specular = 0;
	scene->objects[6].plane.reflective = 0.6f;
	scene->objects[6].plane.metal_fuzz = 0;
	// scene->objects[6].cylinder.type = CYLINDER;
	// scene->objects[6].cylinder.coordinates = (t_vector){1.85, -1.5, 3.3};
	// scene->objects[6].cylinder.height = 4;
	// scene->objects[6].cylinder.orientation = (t_vector){1, 1, 1};
	// scene->objects[6].cylinder.radius = 1.7;
	// scene->objects[6].cylinder.color = (t_color){255, 255, 0, 255};;
	
	
	scene->recursion_depth = 1;
}
