#include "cub.h"

char	**lst_to_arr(t_list *list, int len)
{
	int		i;
	char	**arr;
	t_list	*ptr;

	i = -1;
	arr = ft_calloc(len, sizeof(char *));
	if (!arr)
		return (CUB_ERR);
	while (++i < len)
	{
		arr[i] = list->content;
		ptr = list;
		list = list->next;
		free(ptr);
	}
}

int	is_space(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (1);
	return (0);
}

int is_map_object(char c)
{
	if (c == ' ' || c == '0'
		|| c == '1')
		return (1);
	return (0);
}

int	is_inner_object(char c)
{
	if (is_player(c) || c == '0')
		return (1);
	return (0);
}