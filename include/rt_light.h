/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_light.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:20:25 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:20:26 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LIGHT_H
# define RT_LIGHT_H

t_color	calculate_light(t_obj_union *obj, t_ray ray, t_scene *scene);

#endif
