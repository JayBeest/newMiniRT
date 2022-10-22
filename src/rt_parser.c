#include <rt_datatypes.h>
#include <rt_check_infile.h>
#include <rt_alloc.h>

t_err	parse_file_and_alloc_scene(char *file, t_rt_scene *scene)
{
	t_err	err;

	// Check(partial) validity and count Objects, count Lights
	err = count_scene(file, scene);
	if (err != NO_ERR)
		return (err);
	// Alloc arrays
	err = allocate_scene(scene);
	if (err != NO_ERR)
		return (err);
	// fill scene(check parameter validity)
//	err = parse_file(file, scene);
//	if (err != NO_ERR)
//		return (err);
	return (NO_ERR);
}
