/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_thread.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:20:41 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:20:42 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_THREAD_H
# define RT_THREAD_H

typedef struct s_thread_arg
{
	int			id;
	t_scene		*scene;
	t_mlx		*mlx;
}			t_thread_arg;

t_err	multi_thread(t_mlx *mlx, t_scene *scene);

#endif
