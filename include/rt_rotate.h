#ifndef RT_ROTATE_H
# define RT_ROTATE_H

t_rt_vector	rotate_vector(t_rt_vector original_vector, t_rt_vector rotation);
t_rt_vector	rotate_vector_x(t_rt_vector original_vector, double radians);
t_rt_vector	rotate_vector_y(t_rt_vector original_vector, double radians);

#endif
