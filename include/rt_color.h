#ifndef RT_COLOR_H
#define RT_COLOR_H

int			color_to_int(t_rt_color color);
//t_color		multip_color(t_color_intensity intensity, t_color color);
t_rt_color	all_the_colors(t_rt_resolution pixel, t_rt_scene *scene);

#endif
