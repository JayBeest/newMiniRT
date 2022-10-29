#ifndef RT_SCENE_PRINTER_H
# define RT_SCENE_PRINTER_H

void	print_color(t_rt_color color);
void	print_coordinates(t_rt_vector coordinates);
void	print_orientation(t_rt_vector orientation);
void	print_ambient_light(t_rt_ambient_light ambient);
void	print_camera(t_rt_camera *camera, int amount);
void	print_spotlights(t_rt_spot_light *spotlights, int amount);
void	print_sphere(t_rt_obj_sphere sphere);
void	print_plane(t_rt_obj_plane plane);
void	print_cylinder(t_rt_obj_cylinder cylinder);
void	print_objects(t_rt_obj_union *objects, int amount);
void	print_scene(t_rt_scene scene);

#endif
