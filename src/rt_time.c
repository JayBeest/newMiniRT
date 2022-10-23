#include <sys/time.h>
#include <unistd.h>
#include <rt_time.h>

t_time_stamp	set_time(void)
{
	t_time_stamp	time_stamp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_stamp.sec = current.tv_sec;
	time_stamp.m_sec = current.tv_usec / 1000;
	return (time_stamp);
}

long	ms_passed(t_time_stamp start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - start.sec) * 1000 + \
			(current.tv_usec / 1000 - start.m_sec));
}

void	custom_sleep(t_msecs ms)
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

