/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_intersect.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:48 by jcorneli      #+#    #+#                 */
/*   Updated: 2023/05/01 12:23:26 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INTERSECT_H
# define RT_INTERSECT_H

typedef struct s_minmax
{
	double		min;
	double		max;
}		t_minmax;

typedef struct s_quad_abc
{
	double			a;
	double			b;
	double			c;
}		t_quad_abc;

typedef struct s_quad_result
{
	double			t1;
	double			t2;
}		t_quad_result;

typedef struct s_intersect_result
{
	double			closest_t;
	t_obj_union		*closest_obj;
}				t_intersect_result;

typedef t_quad_result(*t_intersect_fun)(t_vector, t_vector, t_obj_union *);

t_quad_result		intersect_obj(t_vector origin, t_vector viewport, \
					t_obj_union *obj);
t_intersect_result	get_closest_intersection(t_scene *scene, t_vector o, \
					t_vector d, t_minmax t);

#endif
