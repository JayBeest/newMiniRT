/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_intersect.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:48 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:28:49 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

typedef struct s_quad_abc
{
	double				a;
	double				b;
	double				c;
}		t_quad_abc;

typedef	struct s_quad_result
{
	double				t1;
	double				t2;
}		t_quad_result;

typedef struct s_intersect_result
{
	double				closest_t;
	t_obj_union		*closest_obj;
}				t_intersect_result;

typedef t_quad_result(*t_intersect)(t_vector, t_vector, t_obj_union *);

t_quad_result		intersect_obj(t_vector origin, t_vector viewport, t_obj_union *obj);
t_intersect_result	get_closest_intersection(t_scene *scene, t_vector o, t_vector d, double t_min, double t_max);

#endif
