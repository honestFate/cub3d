#include "cub.h"

char	**lst_to_arr(t_list *list, int len)
{
	int		i;
	char	**arr;
	t_list	*ptr;

	i = -1;
	arr = ft_calloc(len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i < len)
	{
		//printf("list:\t%s", list->content);
		arr[i] = ft_strtrim(list->content, "\n");
		free(list->content);
		ptr = list;
		list = list->next;
		free(ptr);
		//printf("arr:\t%s", arr[i]);
	}
	return (arr);
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

void	ft_log(char *str)
{
	ft_putstr_fd("log: ", 1);
	ft_putendl_fd(str, 1);
}