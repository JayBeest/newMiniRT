#include <MLX42.h>
#include <stdlib.h>
#include <rt_datatypes.h>
#include <libft.h>
#include <rt_init.h>
#include <rt_check_infile.h>
#include <rt_parser.h>
#include <rt_scene_printer.h>
#include <rt_alloc.h>
#include <rt_render.h>
#include <rt_hook.h>

#include <stdio.h>
#include <time.h>

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

void	clean_images(t_rt_mlx *mlx)
{
	if (mlx->img)
		mlx_delete_image(mlx->mlx, mlx->img);
	if (mlx->text)
		mlx_delete_image(mlx->mlx, mlx->text);
	if (mlx->fps)
		mlx_delete_image(mlx->mlx, mlx->fps);
	if (mlx->rgb)
		mlx_delete_image(mlx->mlx, mlx->rgb);
	if (mlx->img)
		mlx_delete_image(mlx->mlx, mlx->ref);
	if (mlx->img)
		mlx_delete_image(mlx->mlx, mlx->msaa);
	if (mlx->thread)
		mlx_delete_image(mlx->mlx, mlx->thread);
}

int main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	srand(time(NULL));
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
		mini_rt.scene.light_amount = 3;
		mini_rt.scene.object_amount = 6;
		mini_rt.scene.camera_amount = 1;
		if (allocate_scene(&mini_rt.scene) != NO_ERR)
			return (free_scene(mini_rt.scene, 1));
//		init_mock_rt(&mini_rt.scene);
		init_new_rt(&mini_rt.scene);
	}
	print_scene(mini_rt.scene);
	printf("\namount of camera's: %d\namount of lights: %d\namount of objects: %d\n", mini_rt.scene.camera_amount, mini_rt.scene.light_amount, mini_rt.scene.object_amount);
	set_viewport(&mini_rt.scene, mini_rt.scene.aspect_ratio);
	render_scene(&mini_rt.mlx, &mini_rt.scene);
	mlx_image_to_window(mini_rt.mlx.mlx, mini_rt.mlx.img, 0, 0);
//	mini_rt.mlx.text = mlx_put_string(mini_rt.mlx.mlx, "Control: fov (up/down) rgb (WASDQE) light (PLUS/MINUS)", 20, 20);
	mlx_resize_hook(mini_rt.mlx.mlx, &rt_resize_hook, &mini_rt);
	mlx_mouse_hook(mini_rt.mlx.mlx, &rt_mouse_hook, &mini_rt);
	mlx_loop_hook(mini_rt.mlx.mlx, &rt_hook, &mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	clean_images(&mini_rt.mlx);
	mlx_terminate(mini_rt.mlx.mlx);
	return free_scene(mini_rt.scene, 0);
}
