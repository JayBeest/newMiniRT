/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_render_utils.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:49 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:50 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_UTILS_H
# define RT_RENDER_UTILS_H

t_rt_ray	init_rt_ray(t_rt_point origin, t_rt_point destination, double t_min, double t_max);


#endif
