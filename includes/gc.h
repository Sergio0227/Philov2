/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:51:48 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/11 17:23:40 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

void			*ft_malloc(t_gc **garbage, size_t size);
int				add_gc_node(t_gc **garbage, void *ptr);
void			collect_garbage(t_gc **garbage);

#endif