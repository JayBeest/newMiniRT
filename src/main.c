#include <MLX42.h>
#include <stdlib.h>
#include <rt_datatypes.h>
#include <libft.h>
#include <rt_init.h>
#include <rt_check_infile.h>
#include <rt_parser.h>
#include <rt_scene_printer.h>
#include <rt_vector_utils.h>
#include <rt_draw_utils.h>
#include <rt_alloc.h>

#include <stdio.h>
#include <unistd.h>

int	free_scene(t_rt_scene scene, int return_value)
{
	if (scene.objects != NULL)
		free(scene.objects);
	if (scene.spot_lights != NULL)
		free(scene.spot_lights);
	if (scene.cameras != NULL)
		free(scene.cameras);
	return (return_value);
}

t_err	render_scene(t_rt_mlx *mlx, t_rt_scene *scene)
{
	t_rt_resolution	pixel;
//	t_rt_resolution	ratio;
	t_rt_color		color;

	if (mlx->text)
	{
		mlx_delete_image(mlx->mlx, mlx->text);
		mlx->text = NULL;
	}
	pixel.y = scene->resolution.y - 1;
	color.a = 255;
//	ratio.x = scene->resolution.x / 256;
//	ratio.y = scene->resolution.y / 256;
	float	r;
	float	g;
	float	b;
	while (pixel.y >= 0)
	{
		pixel.x = 0;
		while (pixel.x < scene->resolution.x)
		{
			r = (float)pixel.x / ((float)scene->resolution.x - 1);
			g = (float)pixel.y / ((float)scene->resolution.y - 1);
			b = scene->blue;
			color.r = (int)(255.999 * r);
			color.g = 255 - (int)(255.999 * g);
			color.b = (int)(255.999 * b);
			mlx_put_pixel(mlx->img, pixel.x, pixel.y, color_to_int(color));
			pixel.x++;
		}
		pixel.y--;
	}
	char *temp = ft_itoa(color.b);
	mlx->text = mlx_put_string(mlx->mlx, temp, 50, 50);
	free(temp);
	usleep(16666);
	return (NO_ERR);
}

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
		if (mini_rt->scene.blue < 0.995f)
			mini_rt->scene.blue += 0.005f;
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
	{
		if (mini_rt->scene.blue > 0.005f)
			mini_rt->scene.blue -= 0.005f;
	}
//	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
//		mlx->img->instances[0].x -= 5;
//	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
//		mlx->img->instances[0].x += 5;
	render_scene(&mini_rt->mlx, &mini_rt->scene);
}

int main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	init_rt(&mini_rt);
	if (argc == 2)
	{
		if (check_file(argv[1]) != NO_ERR)
			return (1);
		if (parse_file_and_alloc_scene(argv[1], &(mini_rt.scene)) != NO_ERR)
			return (free_scene(mini_rt.scene, 1));
	}
	else
	{
		mini_rt.scene.light_amount = 1;
		mini_rt.scene.object_amount = 3;
		mini_rt.scene.camera_amount = 1;
		if (allocate_scene(&mini_rt.scene) != NO_ERR)
			return (free_scene(mini_rt.scene, 1));
		init_mock_rt(&mini_rt.scene);
	}

	print_scene(mini_rt.scene);

	printf("\namount of camera's: %d\namount of lights: %d\namount of objects: %d\n", mini_rt.scene.camera_amount, mini_rt.scene.light_amount, mini_rt.scene.object_amount);
	render_scene(&mini_rt.mlx, &mini_rt.scene);
	mlx_image_to_window(mini_rt.mlx.mlx, mini_rt.mlx.img, 0, 0);
//	mlx_image_to_window(mini_rt.mlx.mlx, mini_rt.mlx.text, 0, 0);
	mlx_loop_hook(mini_rt.mlx.mlx, &hook, &mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	mlx_terminate(mini_rt.mlx.mlx);

	return 0;
}
