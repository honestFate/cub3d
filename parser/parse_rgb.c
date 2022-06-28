#include "cub.h"

static int	get_next_number(char *str, int *nmb, char del, int i)
{
	while (ft_isspace(str[i++]));
	if (!ft_isdigit(str[i]))
		return (-1);
	*nmb = ft_atoi(str);
	while (ft_isdigit(str[i++]));
	while (ft_isspace(str[i++]));
	if (str[i] != del)
		return (-1);
	return (i);
}

int	parse_rgb(char *str, int *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	i = get_next_number(str, &r, ',', i);
	if (i < 0)
		return (CUB_ERR);
	i = get_next_number(str, &g, ',', i);
	if (i < 0)
		return (CUB_ERR);
	i = get_next_number(str, &b, '\0', i);
	if (i < 0)
		return (CUB_ERR);
	*color = create_trgb(0, r, g, b);
	return (CUB_OK);
}
