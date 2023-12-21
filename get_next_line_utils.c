/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:27:56 by acharik           #+#    #+#             */
/*   Updated: 2023/12/20 12:00:31 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = start;
	j = 0;
	if (start >= ft_strlen(s))
	{
		substr = malloc(1);
		substr[0] = '\0';
		return (substr);
	}
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (j < len)
		substr[j++] = s[i++];
	substr[j] = '\0';
	return (substr);
}

t_list	*ft_lstnew(void *content, int *lst_size)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	*lst_size += 1;
	return (ptr);
}

char	*copy_linked_list(t_list *lst, int lst_size)
{
	char	*str;
	t_list	*node;
	char	*mini_str;
	int		i;

	if (!(lst))
		return (NULL);
	str = malloc(lst_size + 1);
	i = 0;
	while (lst)
	{
		mini_str = lst->content;
		node = lst;
		if (mini_str)
			str[i] = mini_str[0];
		lst = lst->next;
		free(node->content);
		free(node);
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	read_file(int fd, char **buffer)
{
	int	bytes_read;

	if (!(*buffer))
	{
		*buffer = malloc(BUFFER_SIZE + 1);
		if (!*buffer)
			return (-1);
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*buffer);
			*buffer = NULL;
			return (-1);
		}
		if (bytes_read)
			(*buffer)[bytes_read] = '\0';
		else
		{
			free(*buffer);
			*buffer = NULL;
			return (0);
		}
	}
	return (1);
}
