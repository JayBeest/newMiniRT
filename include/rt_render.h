/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_render.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:21:25 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:21:26 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# include <rt_time.h>
# include <rt_intersect.h>

void		render_text(t_mlx *mlx, t_scene *scene, t_ms time_spend);
void		set_viewport(t_scene *scene, double aspect_ratio);
t_vector	canvas_to_viewport(double x, double y, t_scene *scene);
void		render_pixel(t_resolution pixel, t_mlx *mlx, t_scene *scene);
t_err		single_thread(t_mlx *mlx, t_scene *scene, t_canvas_size canvas);
t_err		render_scene(t_mlx *mlx, t_scene *scene);

#endif
