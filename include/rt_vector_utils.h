/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:51 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:28:52 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS_H
# define VECTOR_UTILS_H

t_rt_vector	add_vector(t_rt_vector a, t_rt_vector b);
t_rt_vector	substract_rt_vector(t_rt_vector a, t_rt_vector b);
t_rt_vector	multip_vector(t_rt_vector a, float num);
t_rt_vector	cross_product(t_rt_vector a, t_rt_vector b);
float		dot_product(t_rt_vector a, t_rt_vector b);

#endif
