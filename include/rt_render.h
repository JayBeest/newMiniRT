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

# include <rt_intersect.h>

typedef struct s_mult_pixel
{
	int					min_x;
	int					max_x;
	int					min_y;
	int					max_y;
}		t_mult_pixel;

typedef struct s_multipt
{
	t_mini_rt			*rt;
	int 				id;
}		t_pthr_arg;

t_intersect_result	get_closest_intersection(t_rt_scene *scene, t_rt_vector o, t_rt_vector d, double t_min, double t_max);
t_rt_color			trace_ray(t_rt_vector o, t_rt_vector d, t_rt_scene *scene, t_rt_resolution pixel);
void				set_viewport(t_rt_viewport *viewport, t_rt_camera *camera, float aspect_ratio);
t_rt_vector			canvas_to_viewport(int x, int y, t_rt_scene *scene);
t_err				render_scene(t_rt_mlx *mlx, t_rt_scene *scene);
//t_err	            render_scene(t_minirt *rt);

#endif
