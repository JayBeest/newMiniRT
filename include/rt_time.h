/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_time.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:20:43 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:20:44 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TIME_H
# define RT_TIME_H

typedef long	t_s;
typedef long	t_ms;
typedef long	t_nano;

typedef struct s_time_stamp
{
	t_s		s;
	t_ms	ms;
	t_nano	nano;
}			t_time_stamp;

t_time_stamp	set_time(void);
long			nano_passed(t_time_stamp start);
long			ms_passed(t_time_stamp start);
void			rt_sleep_ms(t_ms ms);
void			rt_sleep_nano(t_nano nano);

#endif
