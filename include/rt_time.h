#ifndef RT_RT_TIME_H
# define RT_RT_TIME_H

typedef long	t_secs;
typedef long	t_msecs;

typedef struct s_time_stamp
{
	t_secs	sec;
	t_msecs	m_sec;
}			t_time_stamp;

t_time_stamp	set_time(void);
long			ms_passed(t_time_stamp start);
void			custom_sleep(t_msecs ms);

#endif
