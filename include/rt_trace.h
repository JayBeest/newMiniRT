/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_trace.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:20:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2023/04/27 23:52:59 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TRACE_H
# define RT_TRACE_H

# include <rt_intersect.h>

typedef t_vector(*t_reflect_fun)(t_vector,  t_vector);

t_ray		init_ray(t_point origin, t_point destination, t_minmax t);
t_vector	reflect_sphere(t_vector ray, t_vector normal);
t_color		trace_ray(t_ray ray, t_scene *scene, int recursion_depth);

#endif
