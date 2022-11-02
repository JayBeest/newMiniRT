#ifndef RT_ALLOC_H
# define RT_ALLOC_H

t_err	allocate_objects(t_obj_union **objects, int amount);
t_err	allocate_spot_lights(t_spot_light **spot_lights, int amount);
t_err	allocate_scene(t_scene *scene);

#endif
