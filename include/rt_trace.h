/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:47 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 20:23:16 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TRACE_H
# define RT_TRACE_H

# include <rt_intersect.h>

t_rt_ray	init_ray(t_point origin, t_point destination, double t_min, double t_max);
t_vector	reflect_sphere(t_vector ray, t_vector normal);
t_color		trace_ray(t_rt_ray ray, t_scene *scene, int recursion_depth);

#endif
