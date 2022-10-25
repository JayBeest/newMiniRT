#ifndef RT_COLOR_H
#define RT_COLOR_H

int			color_to_int(t_rt_color color);
t_rt_color	multip_color(t_rt_color_intensity intensity, t_rt_color color);
t_rt_color	y_gradient(t_rt_vector o, t_rt_vector d, t_rt_scene *scene);
t_rt_color	all_the_colors(t_rt_resolution pixel, t_rt_scene *scene);

#endif
