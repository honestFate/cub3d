#include "cub.h"

int	check_file_type(char *str, char *file_type)
{
	int		f_len;

	f_len = ft_strlen(file_type);
	if (ft_strncmp(str, file_type, f_len))
		return (CUB_ERR);
	str += f_len;
	if (!*str)
		return (CUB_OK);
	return (CUB_ERR);
}

int	check_argv(int argc, char **argv)
{
	char	*file_type;

	if (argc > 2)
		return (TOO_MANY_ARGS);
	if (argc < 2)
		return (NO_FILE_PASSED);
	file_type = ft_strrchr(argv[1], '.');
	if (!file_type || check_file_type(file_type, ".cub"))
		return (WRONG_FILE_TYPE);
	return (CUB_OK);
}
