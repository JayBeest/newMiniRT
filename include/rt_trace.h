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

#ifndef RT_LIGHTING_H
# define RT_LIGHTING_H

t_rt_color	trace_ray(t_rt_ray ray, t_rt_scene *scene, int recursion_depth);
t_rt_color	assemble_color(t_intersect_result intersect_result, t_rt_ray ray, t_rt_scene *scene, int recursion_depth);

#endif
