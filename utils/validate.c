#include "cub.h"

int	check_file_type(char *str, char *file_type)
{
	str = ft_strrchr(str, '.');
	if (!str)
		return (CUB_ERR);
	if (ft_strcmp(str, file_type))
		return (CUB_ERR);
	return (CUB_OK);
}

int	check_argv(int argc, char **argv)
{
	if (argc > 2)
		return (TOO_MANY_ARGS);
	if (argc < 2)
		return (NO_FILE_PASSED);
	if (!argv[1] || check_file_type(argv[1], ".cub"))
		return (WRONG_FILE_TYPE);
	return (CUB_OK);
}
