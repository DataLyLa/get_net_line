/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:03:46 by lylaurol          #+#    #+#             */
/*   Updated: 2024/07/20 23:03:46 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	is_new_line(t_list *input)
{
	t_list	*last;

	if (!input)
		return (0);
	last = ft_lstlast(input);
	if (!last)
		return (0);
	while (last->content[last->length] && last->content[last->length] != '\n')
		last->length += 1;
	if (last->content[last->length] == '\n')
	{
		last->length += 1;
		return (1);
	}
	return (0);
}

static void	read_line(t_list **input, int fd)
{
	int		is_read;
	char	*buffer;

	if (fd < 0 || !input)
		return ;
	while (!is_new_line(*input))
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return ;
		is_read = read(fd, buffer, BUFFER_SIZE);
		if (is_read > 0)
		{
			if (!buffer)
				return ;
			ft_add_back(input, ft_lstnew(buffer));
		}
		else
		{
			free(buffer);
			if (is_read == -1)
				ft_lstclear(input, free);
			return ;
		}
	}
}

static void	create_line(t_list *cache, char **line)
{
	t_list			*tmp;
	unsigned int	l_size;
	int				i;

	if (!cache || !line)
		return ;
	l_size = 0;
	tmp = cache;
	while (tmp)
	{
		l_size += tmp->length;
		tmp = tmp->next;
	}
	*line = ft_calloc(l_size + 1, sizeof(char));
	if (!*line)
		return ;
	l_size = 0;
	while (cache && cache->content)
	{
		i = 0;
		while (cache->content[i] && i < cache->length)
			(*line)[l_size++] = cache->content[i++];
		cache = cache->next;
	}
}

static void	trunc_line(t_list **input)
{
	t_list			*node;
	char			*buffer;
	unsigned int	i;

	buffer = NULL;
	node = NULL;
	if (!input || !*input)
		return ;
	node = ft_lstlast(*input);
	if (!node || !node->content || !node->length)
		return ;
	buffer = ft_calloc((BUFFER_SIZE - node->length) + 1, sizeof(char));
	if (!buffer)
		return ;
	if (buffer)
	{
		i = 0;
		while (node->length < BUFFER_SIZE && node->content[node->length])
			buffer[i++] = node->content[node->length++];
		ft_lstclear(input, free);
		ft_add_back(input, ft_lstnew(buffer));
	}
}

char	*get_next_line(int fd)
{
	static t_list	*input = NULL;
	t_list			*last;
	char			*output;

	output = NULL;
	last = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&input, fd);
	last = ft_lstlast(input);
	if (!input || last->length == 0)
	{
		ft_lstclear(&input, free);
		return (output);
	}
	create_line(input, &output);
	if (!output)
		return (NULL);
	trunc_line(&input);
	return (output);
}
