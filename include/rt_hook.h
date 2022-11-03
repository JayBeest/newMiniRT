/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_hook.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:20:15 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:20:16 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HOOK_H
# define RT_HOOK_H

void	rt_resize_hook(int x, int y, void *arg);
void	rt_mouse_hook(enum mouse_key e_key, enum action e_action, \
		enum modifier_key e_modifier, void *arg);
void	rt_hook(void *arg);

#endif
