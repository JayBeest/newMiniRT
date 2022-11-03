/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_rotate.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:20:36 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:20:37 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ROTATE_H
# define RT_ROTATE_H

t_vector	rotate_vector(t_vector original_vector, t_vector rotation);
t_vector	rotate_vector_x(t_vector original_vector, double radians);
t_vector	rotate_vector_y(t_vector original_vector, double radians);

#endif
