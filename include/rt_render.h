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

# include <rt_time.h>
# include <rt_intersect.h>

# define RECURSION_DEPTH 3

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
	t_point	origin;
	t_point	destination;
	double		t_max;
	double		t_min;
	t_point	intersection_point;
	t_point	normal;
	t_point	reverse_direction;

}			t_rt_ray;

void			render_text(t_mlx *mlx, t_scene *scene, t_ms time_spend);
void			set_viewport(t_scene *scene, double aspect_ratio);
t_vector		canvas_to_viewport(double x, double y, t_scene *scene);
void			render_pixel(t_resolution pixel, t_mlx *mlx, t_scene *scene);
t_err			render_scene(t_mlx *mlx, t_scene *scene);

#endif
