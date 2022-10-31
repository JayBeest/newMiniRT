#ifndef RT_COLOR_H
#define RT_COLOR_H

t_rt_color_intensity color_to_intensity(t_rt_color color);
int			color_to_int(t_rt_color color);
int			aggregate_to_int(t_rt_color_aggregate agg);
t_rt_color	aggregate_to_color(t_rt_color_aggregate agg);
t_rt_color	add_color(t_rt_color a, t_rt_color b);\
void		add_to_aggregate(t_rt_color_aggregate *agg, t_rt_color_intensity to_add);
t_rt_color	multiply_color(t_rt_color_intensity intensity, t_rt_color color);
t_rt_color	y_gradient(t_rt_vector o, t_rt_vector d, t_rt_scene *scene);
t_rt_color	all_the_colors(t_rt_resolution pixel, t_rt_scene *scene);

#endif
