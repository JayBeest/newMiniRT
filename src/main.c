#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <datatypes.h>
#include <libft.h>
#include <init.h>
#include <scene_printer.h>
#include <alloc.h>
#include <error.h>

#include <stdio.h>
#include <string.h>

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

t_err	check_file(char *file)
{
	int 	fd;
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (err_msg(INVALID_FILE, "check_file", file));
	if (ft_strncmp(&(file[len - 3]), ".rt", 4) != 0)
		return (err_msg(INVALID_EXT, "check_file", file));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return(err_msg(OPEN_F, "check_file", file));
	close(fd);
	return (NO_ERR);
}

t_err	count_ambient(t_rt_scene *scene, char *line)
{
	if (scene->ambient_light.set == true)
		return (err_msg(AMBIENT_SET, "count_ambient", line));
	scene->ambient_light.set = true;
	return (NO_ERR);
}

t_err	count_in_line(char *line, t_rt_scene *scene)
{
	printf("parsing line: %s$\n", line);
	line = ft_skipspace(line);
	if (ft_strlen(line) == 0)
		return (NO_ERR);
	else if (ft_strncmp(line, "A ", 2) == 0)
		return(count_ambient(scene, line));
	else if (ft_strncmp(line, "C ", 2) == 0)
		scene->camera_amount++;
	else if (ft_strncmp(line, "L ", 2) == 0)
		scene->light_amount++;
	else if (ft_strncmp(line, "sp ", 3) == 0 || \
			ft_strncmp(line, "pl ", 3) == 0 || \
			ft_strncmp(line, "cy ", 3) == 0)
			scene->object_amount++;
	else
		return (err_msg(INVALID_OBJ, "count_in_line", line));
	return (NO_ERR);
}

t_err	count_scene(char *file, t_rt_scene *scene)
{
	int		fd;
	char	*line;


	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err_msg(OPEN_F, "count_objs_lights", file));
	while (1)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		if (count_in_line(line, scene) != NO_ERR)
			return (INVALID_OBJ);
		free(line);
	}
	close(fd);
	//  scene complete? all objects++ accounted for?
	return (NO_ERR);
}

t_err	parse_file_and_alloc_scene(char *file, t_rt_scene *scene)
{
	t_err	err;

	// Check(partial) validity and count Objects, count Lights
	err = count_scene(file, scene);
	if (err != NO_ERR)
		return (err);
	// Alloc arrays
	err = allocate_scene(scene);
	if (err != NO_ERR)
		return (err);
	// fill scene(check parameter validity)
//	err = parse_file(file, scene);
//	if (err != NO_ERR)
//		return (err);
	return (NO_ERR);
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
