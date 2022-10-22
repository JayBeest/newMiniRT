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

typedef t_quad_result(*t_intersect)(t_vector, t_vector, t_rt_shape*);

t_quad_result	intersect_shape(t_vector origin, t_vector viewport, t_rt_shape *shape);

#endif
