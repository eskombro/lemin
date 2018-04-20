/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:32:38 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/10 15:07:04 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				find_max_path(t_anthill *f)
{
	int st;
	int end;

	st = 0;
	end = 0;
	while (f->room_start && f->room_start->links[st])
		st++;
	while (f->room_end && f->room_end->links[end])
		end++;
	return (st > end ? st : end);
}

void			order_paths(t_anthill *f)
{
	int		i;
	t_salle	*tmp;

	i = -1;
	while (f->room_start->next_start[++i] && f->room_start->next_start[i + 1])
	{
		if (f->room_start->next_start[i]->len_end >
			f->room_start->next_start[i + 1]->len_end)
		{
			tmp = f->room_start->next_start[i];
			f->room_start->next_start[i] = f->room_start->next_start[i + 1];
			f->room_start->next_start[i-- + 1] = tmp;
		}
	}
	if (f->room_start->next_start[0])
		f->room_start->next = f->room_start->next_start[0];
}

void			printf_paths(t_anthill *f)
{
	int		i;
	t_salle	*tmp;

	i = -1;
	while (f->room_start->next_start[++i])
	{
		tmp = f->room_start->next_start[i];
		ft_dprintf(2, "Path %d:\n", i + 1);
		ft_dprintf(2, "%s->", f->room_start->name);
		while (tmp)
		{
			ft_dprintf(2, "%s", tmp->name);
			if (tmp->next)
				ft_dprintf(2, "->");
			tmp = tmp->next;
		}
		ft_dprintf(2, "\n");
	}
}

void			initiaize_rooms(t_anthill *f)
{
	t_room_lst	*tmp2;

	tmp2 = f->head;
	while (tmp2)
	{
		if (tmp2->salle->taken == 0)
		{
			if (tmp2->salle != f->room_end && tmp2->salle != f->room_start)
				tmp2->salle->next = NULL;
			tmp2->salle->len_end = -1;
		}
		tmp2 = tmp2->next;
	}
}

void			look_for_paths(t_anthill *f, int *room_tab)
{
	t_salle		*tmp;
	int			ret;

	initiaize_rooms(f);
	ft_bzero(room_tab, sizeof(int) * (f->room_ct + 1));
	if ((ret = recursive(f->room_start, room_tab, f, 0) > 0))
	{
		f->path_len[f->current_path] = ret;
		tmp = f->room_start->next_start[f->current_path];
		while (tmp)
		{
			if (tmp != f->room_end && tmp != f->room_start)
				tmp->taken = 1;
			tmp = tmp->next;
		}
	}
	else if (f->current_path == 0)
		free_exit(f, NULL, 1);
	f->current_path++;
}
