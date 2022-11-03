/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_math_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:03 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:23:04 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

double	deg_to_rad(int deg)
{
	return ((double)deg * (double)M_PI / 180);
}

double	random_double(void)
{
	return rand() / (RAND_MAX + 1.0);
}

double random_double_in(double min, double max)
{
	return (min + (max - min) * random_double());
}
