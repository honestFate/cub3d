#include "cub.h"



int	main(int argc, char **argv)
{
	int		err;
	t_cub	*cub;

	err = check_argv(argc, argv);
	if (err)
		return (print_error(err), CUB_ERR);
	cub = NULL;
	err = map_parse(&cub, argv[1]);
	if (err)
		return (print_error(err), CUB_ERR);
	//start draw
}
