/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:52 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 15:44:57 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

t_intersect_result	get_closest_intersection(t_rt_shape *node, t_vector o, t_vector d, double t_min, double t_max, t_rt_shape *self);
t_err	            render_scene(t_minirt *rt);

#endif