#include <stdlib.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_alloc.h>
#include <rt_error.h>

t_err	allocate_objects(t_rt_obj_union **objects, int amount)
{
	*objects = ft_calloc(amount, sizeof(t_rt_obj_union));
	if (!*objects)
		return (err_msg(MALLOC_F, __FILE__, __LINE__, NULL));
	return (NO_ERR);
}

t_err	allocate_spot_lights(t_rt_spot_light **spot_lights, int amount)
{
	*spot_lights = ft_calloc(amount, sizeof(t_rt_spot_light));
	if (!*spot_lights)
		return (err_msg(MALLOC_F, __FILE__, __LINE__, NULL));
	return (NO_ERR);
}

t_err	allocate_cameras(t_rt_camera **cameras, int amount)
{
	*cameras = ft_calloc(amount, sizeof(t_rt_camera));
	if (!*cameras)
		return (err_msg(MALLOC_F, __FILE__, __LINE__, NULL));
	return (NO_ERR);
}

t_err	allocate_scene(t_rt_scene *scene)
{
	if (allocate_objects(&scene->objects, scene->object_amount) != NO_ERR)
		return (MALLOC_F);
	if (allocate_spot_lights(&scene->spot_lights, scene->light_amount) != NO_ERR)
	{
		return (MALLOC_F);
	}
	if (allocate_cameras(&scene->cameras, scene->camera_amount) != NO_ERR)
		return (MALLOC_F);
	return (NO_ERR);
}
