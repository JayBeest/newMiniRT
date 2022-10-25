/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:00 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:01 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include <math.h>
#include <rt_datatypes.h>

t_rt_vector	add_vector(t_rt_vector a, t_rt_vector b)
{
	t_rt_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_rt_vector	substract_rt_vector(t_rt_vector a, t_rt_vector b)
{
	t_rt_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_rt_vector	multip_vector(t_rt_vector a, float num)
{
	t_rt_vector	result;

	result.x = a.x * num;
	result.y = a.y * num;
	result.z = a.z * num;
	return (result);
}

t_rt_vector	cross_product(t_rt_vector a, t_rt_vector b)
{
	t_rt_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.x * b.z - a.z * b.x;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

float	dot_product(t_rt_vector a, t_rt_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}