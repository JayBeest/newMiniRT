#ifndef RT_ALLOC_H
# define RT_ALLOC_H

# include <datatypes.h>

t_err	allocate_objects(t_rt_obj_union **objects, int amount);
t_err	allocate_spot_lights(t_rt_spot_light **spot_lights, int amount);

#endif
