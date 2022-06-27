#include "cub.h"

int	check_argv(int argc, char **argv)
{
	char	*file_type;

	if (argc > 2)
		return (TOO_MANY_ARGS);
	if (argc < 2)
		return (NO_FILE_PASSED);
	file_type = ft_strchr(argv[1], '.');
	if (!file_type)
		return (WRONG_FILE_TYPE);
	if (ft_strlen(file_type) != 4 || ft_strncmp(file_type, ".cub", 4))
		return (WRONG_FILE_TYPE);
	return (CUB_OK);
}
