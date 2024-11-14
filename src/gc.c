/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:06 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/11 17:22:23 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

int	add_gc_node(t_gc **garbage, void *ptr)
{
	t_gc	*new_node;
	t_gc	*current;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
	{
		free(ptr);
		write(1, "Memory allocation failed!", 25);
		return (1);
	}
	new_node->ptr = ptr;
	new_node->next = NULL;
	if (*garbage == NULL)
		*garbage = new_node;
	else
	{
		current = *garbage;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}

void	*ft_malloc(t_gc **garbage, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(1, "Memory allocation failed!", 25);
		return (NULL);
	}
	if (add_gc_node(garbage, ptr) != 0)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

void	collect_garbage(t_gc **garbage)
{
	t_gc	*current;
	t_gc	*next_node;

	if (*garbage == NULL)
		return ;
	current = *garbage;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->ptr);
		free(current);
		current = next_node;
	}
	*garbage = NULL;
}
