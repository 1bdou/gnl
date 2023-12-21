/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:27:01 by acharik           #+#    #+#             */
/*   Updated: 2023/12/20 12:10:41 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	helper_function(char **buffer, int i)
{
	char	*to_free;

	if ((*buffer)[i] == '\n')
	{
		to_free = *buffer;
		*buffer = ft_substr(*buffer, i + 1, ft_strlen(*buffer));
		free(to_free);
		return (1);
	}
	else
	{
		return (0);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*to_free;

	if (!lst || !del)
		return ;
	node = *lst;
	to_free = node;
	while (node)
	{
		del(node->content);
		to_free = node;
		node = node->next;
		free(to_free);
	}
	*lst = NULL;
}

int	line_search(char **buffer, t_list **node, t_list **first_node,
		int *list_size)
{
	int	i;

	i = 0;
	while ((*buffer)[i])
	{
		if ((*buffer)[i] && *first_node)
		{
			(*node)->next = ft_lstnew(ft_substr(*buffer, i, 1), list_size);
			*node = (*node)->next;
		}
		if (!*first_node)
		{
			*first_node = ft_lstnew(ft_substr(*buffer, i, 1), list_size);
			*node = *first_node;
		}
		if (helper_function(buffer, i))
			return (1);
		i++;
	}
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (0);
}

char	*process_buffer(t_list **first_node, char **buffer, t_list **node,
		int fd)
{
	char	*line;
	int		bytes_read;
	int		list_size;

	line = NULL;
	list_size = 0;
	while (1)
	{
		bytes_read = read_file(fd, buffer);
		if (bytes_read == -1)
		{
			ft_lstclear(first_node, free);
			return (NULL);
		}
		if (!bytes_read && !*buffer)
			break ;
		else if (line_search(buffer, node, first_node, &list_size))
			break ;
		else if (bytes_read)
			continue ;
		else
			break ;
	}
	line = copy_linked_list(*first_node, list_size);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	t_list		*first_node;
	t_list		*node;

	first_node = NULL;
	node = first_node;
	return (process_buffer(&first_node, &buffer, &node, fd));
}
