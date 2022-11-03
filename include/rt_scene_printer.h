/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_scene_printer.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:20:39 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:20:40 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_PRINTER_H
# define RT_SCENE_PRINTER_H

void	print_vector(t_vector vector);
void	print_color(t_color color);
void	print_coordinates(t_vector coordinates);
void	print_orientation(t_vector orientation);
void	print_ambient_light(t_ambient_light ambient);
void	print_camera(t_camera *camera, int amount);
void	print_spotlights(t_light *spotlights, int amount);
void	print_sphere(t_obj_sphere sphere);
void	print_plane(t_obj_plane plane);
void	print_cylinder(t_obj_cylinder cylinder);
void	print_objects(t_obj_union *objects, int amount);
void	print_scene(t_scene scene);

#endif
