#include <stdlib.h>
#include <rt_datatypes.h>
#include <libft.h>
#include <rt_init.h>
#include <rt_check_infile.h>
#include <rt_parser.h>
#include <rt_scene_printer.h>
#include <rt_alloc.h>
#include <rt_error.h>

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

int main(int argc, char **argv)
{
	t_rt_scene	scene;

	init_rt(&scene);
	if (argc == 2)
	{
		if (check_file(argv[1]) != NO_ERR)
			return (1);
		if (parse_file_and_alloc_scene(argv[1], &scene) != NO_ERR)
			return (free_scene(scene, 1));
	}
	else
	{
		scene.light_amount = 1;
		scene.object_amount = 3;
		scene.camera_amount = 1;
		if (allocate_scene(&scene) != NO_ERR)
			return (free_scene(scene, 1));
		init_mock_rt(&scene);
	}

	print_scene(scene);

	printf("\namount of camera's: %d\namount of lights: %d\namount of objects: %d\n", scene.camera_amount, scene.light_amount, scene.object_amount);

	return 0;
}
