#include <math.h>
#include <stdlib.h>

double	deg_to_rad(int deg)
{
	return ((double)deg * (double)M_PI / 180);
}

double	random_double(void)
{
	return rand() / (RAND_MAX + 1.0);
}

double random_double_in(double min, double max)
{
	return (min + (max - min) * random_double());
}
