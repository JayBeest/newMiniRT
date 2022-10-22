#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_error.h>

t_err	count_ambient(t_rt_scene *scene, char *line)
{
	if (scene->ambient_light.set == true)
		return (err_msg(AMBIENT_SET, __FILE__, __LINE__, line));
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
		return (err_msg(INVALID_OBJ, __FILE__, __LINE__, line));
	return (NO_ERR);
}

t_err	count_scene(char *file, t_rt_scene *scene)
{
	int		fd;
	char	*line;


	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err_msg(OPEN_F, __FILE__, __LINE__, file));
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

t_err	check_file(char *file)
{
	int 	fd;
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (err_msg(INVALID_FILE, __FILE__, __LINE__, file));
	if (ft_strncmp(&(file[len - 3]), ".rt", 4) != 0)
		return (err_msg(INVALID_EXT, __FILE__, __LINE__, file));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return(err_msg(OPEN_F, __FILE__, __LINE__, file));
	close(fd);
	return (NO_ERR);
}
