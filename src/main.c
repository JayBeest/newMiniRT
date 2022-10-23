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
#include <rt_time.h>

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
	t_rt_color		color;
	t_time_stamp	start_of_frame;
	t_msecs			time_spend;

	start_of_frame = set_time();
	pixel.y = scene->size.height - 1;
	color.a = 255;
	float	r;
	float	g;
	float	b;
	while (pixel.y >= 0)
	{
		pixel.x = 0;
		while (pixel.x < scene->size.width)
		{
			r = (float)pixel.x / ((float)scene->size.width - 1);
			g = (float)pixel.y / ((float)scene->size.height - 1);
			b = scene->blue;
			color.r = (int)(255.999 * r);
			color.g = 255 - (int)(255.999 * g);
			color.b = (int)(255.999 * b);
			mlx_put_pixel(mlx->img, pixel.x, pixel.y, color_to_int(color));
			pixel.x++;
		}
		pixel.y--;
	}
	char	*temp = ft_itoa(color.b);
	char	fps[64];
	time_spend = ms_passed(start_of_frame);
	sprintf(fps, "frame took %lu ms - (%.1f fps)\n", time_spend, 1000.0f / (float)time_spend);
	mlx_delete_image(mlx->mlx, mlx->text);
	mlx_delete_image(mlx->mlx, mlx->fps);
	mlx->fps = mlx_put_string(mlx->mlx, fps, scene->size.width - 300, scene->size.height - 50);
	mlx->text = mlx_put_string(mlx->mlx, temp, 50, 50);
	free(temp);
	custom_sleep(16 - time_spend);
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
		{
			mini_rt->scene.blue += 0.005f;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
	{
		if (mini_rt->scene.blue > 0.005f)
		{
			mini_rt->scene.blue -= 0.005f;
			render_scene(&mini_rt->mlx, &mini_rt->scene);
		}
	}
//	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
//		mlx->img->instances[0].x -= 5;
//	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
//		mlx->img->instances[0].x += 5;
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
	mini_rt.mlx.text = mlx_put_string(mini_rt.mlx.mlx, "Control the blue (up/down)", 20, 20);
	mlx_loop_hook(mini_rt.mlx.mlx, &hook, &mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	mlx_delete_image(mini_rt.mlx.mlx, mini_rt.mlx.img);
	mlx_delete_image(mini_rt.mlx.mlx, mini_rt.mlx.text);
	mlx_delete_image(mini_rt.mlx.mlx, mini_rt.mlx.fps);
	mlx_terminate(mini_rt.mlx.mlx);
	return free_scene(mini_rt.scene, 0);
}
