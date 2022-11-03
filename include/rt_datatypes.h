/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_datatypes.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:19:58 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:19:59 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DATATYPES_H
# define RT_DATATYPES_H

# include <stdbool.h>
# include <MLX42.h>

# define IMAGE_WIDTH 768
# define EPSILON 1e-6

# define CAMERA_MOVE_STEP 0.1
# define CAMERA_ZOOM_FACTOR 1.5
# define FPS 60
# define MULTI_SAMPLE 0
# define RT_THREADS 4
# define RT_MAX_THREADS 32

typedef enum e_err
{
	NO_ERR,
	MALLOC_F,
	OPEN_F,
	MLX_INIT_F,
	MLX_NEW_IMG_F,
	PARSE_F,
	INVALID_ARG,
	INVALID_FILE,
	INVALID_EXT,
	INVALID_OBJ,
	AMBIENT_SET,
	PIXEL_OOB,
	ERR_COUNTER
}			t_err;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	NO_OBJECT
}			t_obj_type;

typedef enum e_light_type
{
	POINT,
	DIRECT
}			t_light_type;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
}			t_vector;

typedef t_vector	t_point;
typedef t_vector	t_color_ratio;

typedef struct s_resolution
{
	int				x;
	int				y;
}			t_resolution;

typedef struct s_canvas_size
{
	t_resolution	min;
	t_resolution	max;
}			t_canvas_size;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}			t_color;

typedef struct s_color_intensity
{
	double			r;
	double			g;
	double			b;
	double			a;
}			t_color_intensity;

typedef struct s_color_aggregate
{
	t_color_intensity	intensity;
	unsigned long		source_counter;
}			t_color_aggregate;

typedef struct s_obj_default
{
	t_obj_type		type;
	t_color			color;
	t_point			coordinates;
	float			reflective;
	float			metal_fuzz;
	int				specular;
}			t_obj_default;

typedef struct s_obj_sphere
{
	t_obj_type		type;
	t_color			color;
	t_point			coordinates;
	float			reflective;
	float			metal_fuzz;
	int				specular;
	double			radius;
}			t_obj_sphere;

typedef struct s_obj_plane
{
	t_obj_type		type;
	t_color			color;
	t_point			coordinates;
	float			reflective;
	float			metal_fuzz;
	int				specular;
	t_vector		orientation;
}			t_obj_plane;

typedef struct s_obj_cylinder
{
	t_obj_type		type;
	t_color			color;
	t_point			coordinates;
	float			reflective;
	float			metal_fuzz;
	int				specular;
	t_vector		orientation;
	double			radius;
	double			height;
}			t_obj_cylinder;

typedef union u_obj_union
{
	t_obj_default	def;
	t_obj_sphere	sphere;
	t_obj_plane		plane;
	t_obj_cylinder	cylinder;
}			t_obj_union;

typedef struct s_ambient_light
{
	double			intensity;
	t_color			color;
	bool			set;
}			t_ambient_light;

typedef struct s_spot_light
{
	t_light_type	type;
	t_point			coordinates;
	double			intensity;
	t_color			color;
	bool			toggle;
}			t_light;

typedef struct s_camera
{
	t_point			coordinates;
	t_vector		orientation;
	int				fov;
	int				zoom_level;
}			t_camera;

typedef struct s_viewport
{
	double			width;
	double			height;
	double			focal_length;
	t_point			coordinates;
	t_vector		orientation;
	double			x_ratio;
	double			y_ratio;
}			t_viewport;

typedef struct s_rt_ray
{
	t_point			origin;
	t_point			dest;
	double			t_max;
	double			t_min;
	t_point			inters_p;
	t_point			normal;
	t_point			reverse_direction;

}			t_ray;

typedef struct s_scene
{
	t_obj_union		*objects;
	t_light			*lights;
	t_ambient_light	ambient_light;
	t_camera		*cameras;
	int				cc;
	t_resolution	canvas;
	t_viewport		viewport;
	t_color_ratio	bg_color;
	int				object_amount;
	int				light_amount;
	int				camera_amount;
	unsigned long	frame_counter;
	int				thread_amount;

	double			aspect_ratio;
	int				fps;

	int				recursion_depth;
	int				msaa;
	int				hud;
	bool			bare_toggle;
}			t_scene;

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*text;
	mlx_image_t		*fps;
	mlx_image_t		*rgb;
	mlx_image_t		*ref;
	mlx_image_t		*msaa;
	mlx_image_t		*thread;
}			t_mlx;

typedef struct s_mini_rt
{
	t_mlx			mlx;
	t_scene			scene;
}			t_mini_rt;

#endif
