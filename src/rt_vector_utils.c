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

#include <math.h>
#include <rt_datatypes.h>

#include <stdlib.h>

t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	substract_vector(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector	multiply_vector(t_vector a, double num)
{
	t_vector	result;

	result.x = a.x * num;
	result.y = a.y * num;
	result.z = a.z * num;
	return (result);
}

t_vector	devide_vector(t_vector a, double num)
{
	t_vector	result;

	result.x = a.x / num;
	result.y = a.y / num;
	result.z = a.z / num;
	return (result);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.x * b.z - a.z * b.x;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	length_squared(t_vector vector)
{
	return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

double	vector_length(t_vector vector)
{
	return (sqrt(length_squared(vector)));
}

t_vector	unit_vector(t_vector vector)
{
	return (devide_vector(vector, vector_length(vector)));
}

double	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	rnd_scalar(void)
{
	t_vector	random;

	random.x = (double)rand() / RAND_MAX;
	random.y = (double)rand() / RAND_MAX;
	random.z = (double)rand() / RAND_MAX;
	return (random);
}
