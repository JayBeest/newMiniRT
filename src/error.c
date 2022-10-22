#include <datatypes.h>
#include <stdio.h>

t_err	err_msg(t_err err, char *file, int line, char *str)
{
	static char *message[ERR_COUNTER] = {
			[MALLOC_F] = "%s: line: %d: malloc failed\n",
			[INVALID_FILE] = "%s: line: %d: %s: invalid file\n",
			[INVALID_EXT] = "%s: line: %d: %s: invalid extension\n",
			[OPEN_F] = "%s: line: %d: %s: error opening file\n",
			[AMBIENT_SET] = "%s: line: %d: %s: ambient light already set\n"
	};
	printf(message[err], file, line, str);
	return (err);
}
