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

int	color_to_int(t_color color);
t_err	rt_putpixel(int x, int y, int color, t_minirt *rt);

#endif