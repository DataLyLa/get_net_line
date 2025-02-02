/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:45:44 by lylaurol          #+#    #+#             */
/*   Updated: 2024/07/25 01:45:45 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->length = 0;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_add_back(t_list **lst, t_list *new_lst)
{
	t_list	*last;

	if (!lst || !new_lst)
		return ;
	if (!*lst)
	{
		*lst = new_lst;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new_lst;
}

void	*ft_calloc(size_t nmemb, size_t siz)
{
	void			*s;
	size_t			s_len;
	size_t			s_size;

	s_len = 0;
	s_size = siz * nmemb;
	s = malloc(s_size);
	if (!s)
		return (NULL);
	while (s_size--)
		*((char *)s + s_len++) = 0;
	return (s);
}
