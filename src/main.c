#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <datatypes.h>
#include <libft.h>
#include <init.h>
#include <scene_printer.h>
#include <alloc.h>

#include <stdio.h>
#include <string.h>

t_err	err_msg(t_err err, char *return_fun, char *str)
{
	static char *message[DEFAULT_ERR] = {
			[INVALID_FILE] = "[%s] %s: invalid file\n",
			[INVALID_EXT] = "[%s] %s: invalid extension\n",
			[OPEN_F] = "[%s] %s: error opening file\n",
			[AMBIENT_SET] = "[%s] %s: ambient light already set\n"
	};
	printf(message[err], return_fun, str);
	return (err);
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
	t_err	err;
	int		fd;
	char	*line;

	err = check_file(file);
	if (err != NO_ERR)
		return (err);
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

	return (NO_ERR);
}

t_err	parse_scene(char *file, t_rt_scene *scene)
{
	// Check(partial) validity and count Objects, count Lights
	return (count_scene(file, scene));
	// Alloc arrays
	// fill scene(check parameter validity)
	return (NO_ERR);
}

int main(int argc, char **argv)
{
	t_rt_scene	scene;

	init_rt(&scene);
	if (argc == 2)
	{
		if (parse_scene(argv[1], &scene) != NO_ERR)
			return (1);
	}
	else
	{
		scene.g_mockup = true;
		scene.light_amount = 1;
		scene.object_amount = 3;
	}
	allocate_objects(&scene.objects, scene.object_amount);
	allocate_spot_lights(&scene.spot_lights, scene.light_amount);
	if (scene.g_mockup)
		init_mock_rt(&scene);

	print_scene(scene);

	printf("\namount of camera's: %d\namount of lights: %d\namount of objects: %d\n", scene.camera_amount, scene.light_amount, scene.object_amount);

	return 0;
}
