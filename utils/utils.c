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
