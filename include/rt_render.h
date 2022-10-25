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

t_intersect_result	get_closest_intersection(t_rt_scene *scene, t_rt_vector o, t_rt_vector d, double t_min, double t_max);
t_rt_color	trace_ray(t_rt_vector o, t_rt_vector d, t_rt_scene *scene);
//t_err	            render_scene(t_minirt *rt);

#endif
