#include <sys/time.h>
#include <unistd.h>
#include <rt_time.h>

t_time_stamp	set_time(void)
{
	t_time_stamp	time_stamp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_stamp.s = current.tv_sec;
	time_stamp.nano = current.tv_usec;
	time_stamp.ms = time_stamp.nano / 1000;
	return (time_stamp);
}

long	nano_passed(t_time_stamp start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - start.s) * 1000000 + \
			(current.tv_usec - start.nano));
}

long	ms_passed(t_time_stamp start)
{
	return (nano_passed(start) / 1000);
}

void	rt_sleep_ms(t_ms ms)
{
	t_time_stamp	start;

	if (ms < 0)
		return ;
	start = set_time();
	while (ms - ms_passed(start) > 0)
	{
		usleep(512);
	}
}

void	rt_sleep_nano(t_nano nano)
{
	t_time_stamp	start;

	start = set_time();
	while (nano - nano_passed(start) > 0)
	{
		usleep(128);
	}
}
