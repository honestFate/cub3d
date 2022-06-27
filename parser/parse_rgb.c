#include "cub.h"

int	rgb_parse(char *str, int *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	if (!ft_isdigit(str[0]))
		return (CUB_ERR);
	r = ft_atoi(str);
	while (ft_isdigit(str[i++]));
	while (ft_isspace(str[i++]));
	if (str[i] != ',')
		return (-1);
	while (ft_isspace(str[i++]));
	if (!ft_isdigit(str[0]));
	r = ft_atoi(str);
	while (ft_isdigit(str[i++]));
	while (ft_isspace(str[i++]));
	if (str[i] != ',')
		return (-1);
	while (ft_isspace(str[i++]));
	if (!ft_isdigit(str[0]));
	r = ft_atoi(str);
	while (ft_isdigit(str[i++]));
	while (ft_isspace(str[i++]));
	if (str[i] != ',')
		return (-1);
}
