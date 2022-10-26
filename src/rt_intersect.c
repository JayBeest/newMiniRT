/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_intersect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:58 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 18:43:35 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <rt_datatypes.h>
#include <rt_intersect.h>
#include <rt_vector_utils.h>
#include <math.h>

#include <stdio.h>

t_quad_result	intersect_sphere(t_rt_vector o, t_rt_vector d, t_rt_obj_union *obj)
{
	t_quad_abc		quad;
	t_quad_result	result;
	t_rt_vector		co;
	double 			discriminant;

	co = substract_rt_vector(o, obj->sphere.coordinates);
	quad.a = dot_product(d, d);
	quad.b = 2 * dot_product(co, d);
	quad.c = dot_product(co, co) - obj->sphere.diameter / 2 * obj->sphere.diameter / 2; /// radius?
	discriminant = quad.b * quad.b - 4 * quad.a * quad.c;
	if (discriminant < 0)
		return ((t_quad_result){INFINITY, INFINITY});
	result.t1 = (-1 * quad.b + sqrtf(discriminant)) / (2 * quad.a);
	result.t2 = (-1 * quad.b - sqrtf(discriminant)) / (2 * quad.a);
	return (result);
}

t_quad_result	intersect_plane(t_rt_vector o, t_rt_vector d, t_rt_obj_union *obj)
{
	t_quad_result	result;
	double			denominator;

	result.t2 = INFINITY;
	denominator	= dot_product(obj->plane.orientation, d);
	if (denominator > EPSILON)
	{
		result.t1 = dot_product(substract_rt_vector(obj->plane.coordinates, o), obj->plane.orientation) / denominator;
		if (result.t1 < 0)
			result.t1 = INFINITY;
		return (result);
	}
	result.t1 = INFINITY;
	return (result);
}


t_quad_result	intersect_obj(t_rt_vector origin, t_rt_vector viewport, t_rt_obj_union *obj)
{
	static t_intersect	function_pointers[NO_OBJECT] = {
			[SPHERE] = intersect_sphere,
			[PLANE] = intersect_plane
	};
	return (function_pointers[obj->def.type](origin, viewport, obj));
}

t_intersect_result	get_closest_intersection(t_rt_scene *scene, t_rt_vector o, t_rt_vector d, double t_min, double t_max)
{
	t_intersect_result	intersect_result;
	t_quad_result		quad_result;

	intersect_result.closest_obj = NULL;
	intersect_result.closest_t = INFINITY;
	int i = 0;
	while (i < scene->object_amount)
	{
		quad_result = intersect_obj(o, d, &scene->objects[i]);
		if (quad_result.t1 > t_min && quad_result.t1 < t_max && quad_result.t1 < intersect_result.closest_t)
		{
			intersect_result.closest_t = quad_result.t1;
			intersect_result.closest_obj = &scene->objects[i];
		}
		if (quad_result.t2 > t_min && quad_result.t2 < t_max && quad_result.t2 < intersect_result.closest_t)
		{
			intersect_result.closest_t = quad_result.t2;
			intersect_result.closest_obj = &scene->objects[i];
		}
		i++;
	}
	return (intersect_result);
}
