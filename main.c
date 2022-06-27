#include "cub.h"



int	main(int argc, char **argv)
{
	t_cub	*cub;

	err = check_args(argc, argv);
	if (err)
		return (print_error(err), CUB_ERR);
	cub = NULL;
	err = map_parse(&cub, argv[1]);
	if (err)
		return (print_error(err), CUB_ERR);
	//start draw
}
