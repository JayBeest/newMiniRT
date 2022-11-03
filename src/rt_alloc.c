/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_alloc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:22:24 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:22:25 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_alloc.h>
#include <rt_error.h>

t_err	allocate_objects(t_obj_union **objects, int amount)
{
	*objects = ft_calloc(amount, sizeof(t_obj_union));
	if (!*objects)
		return (err_msg(MALLOC_F, __FILE__, __LINE__, NULL));
	return (NO_ERR);
}

t_err	allocate_spot_lights(t_light **spot_lights, int amount)
{
	*spot_lights = ft_calloc(amount, sizeof(t_light));
	if (!*spot_lights)
		return (err_msg(MALLOC_F, __FILE__, __LINE__, NULL));
	return (NO_ERR);
}

t_err	allocate_cameras(t_camera **cameras, int amount)
{
	*cameras = ft_calloc(amount, sizeof(t_camera));
	if (!*cameras)
		return (err_msg(MALLOC_F, __FILE__, __LINE__, NULL));
	return (NO_ERR);
}

t_err	allocate_scene(t_scene *scene)
{
	if (allocate_objects(&scene->objects, scene->object_amount) != NO_ERR)
		return (MALLOC_F);
	if (allocate_spot_lights(&scene->lights, scene->light_amount) != NO_ERR)
		return (MALLOC_F);
	if (allocate_cameras(&scene->cameras, scene->camera_amount) != NO_ERR)
		return (MALLOC_F);
	return (NO_ERR);
}
