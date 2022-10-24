#include <math.h>
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

t_rt_color	all_the_colors(t_rt_resolution pixel, t_rt_scene *scene)
{
	float		r;
	float		g;
	float		b;
	t_rt_color	color;

	r = (float)pixel.x / ((float)scene->size.width - 1);
	g = (float)pixel.y / ((float)scene->size.height - 1);
	b = scene->blue;
	color.a = 255;
	color.r = (int)(255.999 * r);
	color.g = 255 - (int)(255.999 * g);
	color.b = (int)(255.999 * b);
	return (color);
}

t_err	render_scene(t_rt_mlx *mlx, t_rt_scene *scene)
{
	t_rt_resolution	pixel;
	t_rt_color		color;
	t_time_stamp	start_of_frame;
	t_msecs			time_spend;

	start_of_frame = set_time();
	pixel.y = 0;
	while (pixel.y < scene->size.height)
	{
		pixel.x = 0;
		while (pixel.x < scene->size.width)
		{
			color = all_the_colors(pixel, scene);
			mlx_put_pixel(mlx->img, pixel.x, pixel.y, color_to_int(color));
			pixel.x++;
		}
		pixel.y++;
	}
	char	blue[32];
	char	fps[64];
	time_spend = ms_passed(start_of_frame);
	mlx_delete_image(mlx->mlx, mlx->fps);
	mlx_delete_image(mlx->mlx, mlx->text);
	sprintf(blue, "blue: %d\n", color.b);
	sprintf(fps, "frame took %lu ms - (%.1f fps)\n", time_spend, 1000.0f / (float)time_spend);
	mlx->text = mlx_put_string(mlx->mlx, blue, 20, 20);
	mlx->fps = mlx_put_string(mlx->mlx, fps, scene->size.width - 325, scene->size.height - 50);
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
}

void	set_viewport(t_rt_viewport *viewport, t_rt_camera *camera, float aspect_ratio)
{
	float radians;

	radians = (float)camera->fov * (float)M_PI / 180;
	viewport->width = 2.0f;
	viewport->height = viewport->width / aspect_ratio;
	viewport->diagonal = sqrtf(viewport->width * viewport->width + viewport->height * viewport->height);
	viewport->focal_length = viewport->diagonal / 2 / tanf(radians / 2);
	printf("\n\nwidth: %f\nheight: %f\ndiagonal: %f\nfov: %d\nfocal length: %f\n\n", viewport->width, viewport->height, viewport->diagonal,  camera->fov, viewport->focal_length);
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

	set_viewport(&mini_rt.scene.viewport, &mini_rt.scene.cameras[0], mini_rt.scene.aspect_ratio);

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
