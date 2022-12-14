/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_color.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:19:53 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:19:54 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COLOR_H
# define RT_COLOR_H

t_color_intensity	color_to_intensity(t_color color);
int					color_to_int(t_color color);

void				init_intensity(t_color_intensity *intensity, \
					double init, t_color color);
void				update_intensity(t_color_intensity *intensity, \
					t_color_intensity add, t_color color);
t_color_intensity	update_multiply_intensity(t_color_intensity og, \
					double factor, t_color color);

int					aggregate_to_int(t_color_aggregate agg);
t_color				aggregate_to_color(t_color_aggregate agg);
t_color				add_color(t_color a, t_color b);
void				add_to_aggregate(t_color_aggregate *agg, \
					t_color_intensity to_add);
t_color				multiply_color(t_color_intensity intensity, t_color color);
t_color				y_gradient(t_vector o, t_vector d, t_scene *scene);
t_color				all_the_colors(t_resolution pixel, t_scene *scene);

#endif
