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

typedef struct s_multi_pixel
{
	int					min_x;
	int					max_x;
	int					min_y;
	int					max_y;
}			t_multi_pixel;

typedef struct s_pthread_arg
{
	t_mini_rt			*rt;
	int 				id;
}			t_pthread_arg;

typedef struct s_rt_ray
{
	t_rt_point	origin;
	t_rt_point	direction;
	double		t_max;
	double		t_min;
	int			recursion_depth;
	t_rt_point	intersection_point;
	t_rt_point	normal;
	t_rt_point	reverse_direction;

}			t_rt_ray;

t_rt_color			trace_ray(t_rt_ray ray, t_rt_scene *scene, int recursion_depth);
void				set_viewport(t_rt_viewport *viewport, t_rt_camera *camera, double aspect_ratio);
t_rt_vector			canvas_to_viewport(int x, int y, t_rt_scene *scene);
t_err				render_scene(t_rt_mlx *mlx, t_rt_scene *scene);

#endif
