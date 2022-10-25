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


void	print_vector(t_rt_vector vector)
{
	printf("x: %f  y: %f  z: %f\n", vector.x, vector.y, vector.z);
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
		mini_rt.scene.light_amount = 2;
		mini_rt.scene.object_amount = 5;
		mini_rt.scene.camera_amount = 1;
		if (allocate_scene(&mini_rt.scene) != NO_ERR)
			return (free_scene(mini_rt.scene, 1));
//		init_mock_rt(&mini_rt.scene);
		init_new_rt(&mini_rt.scene);
	}

	print_scene(mini_rt.scene);
	printf("\namount of camera's: %d\namount of lights: %d\namount of objects: %d\n", mini_rt.scene.camera_amount, mini_rt.scene.light_amount, mini_rt.scene.object_amount);

	set_viewport(&mini_rt.scene.viewport, &mini_rt.scene.cameras[0], mini_rt.scene.aspect_ratio);

	render_scene(&mini_rt.mlx, &mini_rt.scene);
	mlx_image_to_window(mini_rt.mlx.mlx, mini_rt.mlx.img, 0, 0);
	mini_rt.mlx.text = mlx_put_string(mini_rt.mlx.mlx, "Control fov (up/down)", 20, 20);
	mlx_loop_hook(mini_rt.mlx.mlx, &hook, &mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	mlx_delete_image(mini_rt.mlx.mlx, mini_rt.mlx.img);
	mlx_delete_image(mini_rt.mlx.mlx, mini_rt.mlx.text);
	mlx_delete_image(mini_rt.mlx.mlx, mini_rt.mlx.fps);
	mlx_terminate(mini_rt.mlx.mlx);
	return free_scene(mini_rt.scene, 0);
}
