#include <stdlib.h>
#include <alloc.h>
#include <libft.h>

t_err	allocate_objects(t_rt_obj_union **objects, int amount)
{
	*objects = ft_calloc(sizeof(t_rt_obj_union) * amount);
	if (!*objects)
		return (MALLOC_F);
	return (NO_ERR);
}

t_err	allocate_spot_lights(t_rt_spot_light **spot_lights, int amount)
{
	*spot_lights = ft_calloc(sizeof(t_rt_spot_light) * amount);
	if (!*spot_lights)
		return (MALLOC_F);
	return (NO_ERR);
}