#include <datatypes.h>
#include <stdio.h>

t_err	err_msg(t_err err, char *return_fun, char *str)
{
	static char *message[DEFAULT_ERR] = {
			[MALLOC_F] = "[%s] malloc failed\n",
			[INVALID_FILE] = "[%s] %s: invalid file\n",
			[INVALID_EXT] = "[%s] %s: invalid extension\n",
			[OPEN_F] = "[%s] %s: error opening file\n",
			[AMBIENT_SET] = "[%s] %s: ambient light already set\n"
	};
	printf(message[err], return_fun, str);
	return (err);
}
