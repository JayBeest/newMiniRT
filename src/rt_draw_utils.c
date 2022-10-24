/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_draw_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:28:56 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_error.h>



int	color_to_int(t_rt_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}
