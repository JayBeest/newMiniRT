/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_alloc.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:19:44 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:19:45 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ALLOC_H
# define RT_ALLOC_H

t_err	allocate_objects(t_obj_union **objects, int amount);
t_err	allocate_spot_lights(t_light **spot_lights, int amount);
t_err	allocate_scene(t_scene *scene);

#endif
