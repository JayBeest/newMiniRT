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

void	set_viewport_ratio(t_viewport *viewport, t_resolution canvas);
void	set_viewport(t_scene *scene, double aspect_ratio);

#endif
