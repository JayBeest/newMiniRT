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

t_rt_color	precalculate_light(t_rt_obj_union *closest_obj, t_rt_vector o, t_rt_vector d, double closest_t, t_rt_scene *scene, int recursion_depth);

#endif
