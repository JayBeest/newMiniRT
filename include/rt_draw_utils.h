/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_draw_utils.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:45 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:28:47 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DRAW_UTILS_H
# define RT_DRAW_UTILS_H

int		color_to_int(t_rt_color color);
t_err	rt_put_pixel(t_rt_resolution pixel, int color, t_rt_scene *scene, t_rt_mlx *mlx);

#endif
