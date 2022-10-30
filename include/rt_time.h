#ifndef RT_RT_TIME_H
# define RT_RT_TIME_H

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
