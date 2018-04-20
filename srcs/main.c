/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 20:47:49 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/11 19:39:43 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		change_salle_next(t_anthill *f, t_salle *salle, int ret, int i)
{
	if (salle->len_end == -1 || ret + 1 < salle->len_end)
	{
		salle->next = salle->links[i];
		salle->len_end = ret + 1;
	}
	if (ret >= 0 && salle == f->room_start)
		salle->next_start[f->current_path] = salle->links[i];
}

int				recursive(t_salle *salle, int *room_tab, t_anthill *f, int lim)
{
	int			i;
	int			ret;
	int			*room_tab_l;

	i = -1;
	if (salle == f->room_end)
		return (0);
	if (lim > f->limit_rec || (f->path_len[f->current_path] > 0 && lim
		> f->path_len[f->current_path])
		|| !(room_tab_l = (int *)malloc(sizeof(int) * (f->room_ct + 1))))
		return (-1);
	ft_memcpy(room_tab_l, room_tab, sizeof(int) * (f->room_ct + 1));
	while (salle->links && salle->links[++i])
	{
		ret = 0;
		if (salle->links[i]->taken != 1 && !room_tab[salle->links[i]->id])
		{
			room_tab_l[salle->id] = 1;
			if ((ret = recursive(salle->links[i], room_tab_l, f, lim + 1)) >= 0)
				change_salle_next(f, salle, ret, i);
		}
	}
	room_tab_l ? free(room_tab_l) : 0;
	return (salle->len_end);
}

void			free_exit(t_anthill *f, char *l_free, int error)
{
	t_room_lst	*to_free;

	error ? ft_printf("ERROR\n") : 0;
	l_free ? free(l_free) : 0;
	to_free = f->head;
	if (f->room_start && f->room_start->next_start)
	ft_memdel((void**)&f->room_start->next_start);
	while (f->head)
	{
		to_free = f->head->next;
		if (f->head->salle)
		{
			ft_strdel(&f->head->salle->name);
			f->head->salle->links ? free(f->head->salle->links) : 0;
			ft_memdel((void**)&f->head->salle);
		}
		ft_memdel((void**)&f->head);
		f->head = to_free;
	}
	f->path_len ? free(f->path_len) : 0;
	ft_strdel(&f->buf);
	exit(0);
}

int				launch_algo(t_anthill *f)
{
	int		*room_tab;

	if (!f->room_start->links || !f->room_end->links)
		return (1);
	f->max_path = find_max_path(f);
	if (!(room_tab = (int *)ft_memalloc(sizeof(int) * (f->room_ct + 1)))
		|| !(f->room_start->next_start = (t_salle**)ft_memalloc(sizeof(t_salle*)
			* (f->max_path + 1)))
		|| !(f->path_len = (int*)ft_memalloc(sizeof(int) * (f->max_path + 1))))
		return (1);
	while (f->current_path < f->max_path)
		look_for_paths(f, room_tab);
	order_paths(f);
	f->print_path ? printf_paths(f) : 0;
	ft_printf("%s\n", f->buf);
	if (move_ants(f) != -1)
		free_exit(f, NULL, 0);
	return (0);
}

int				main(int ac, char **av)
{
	t_anthill	f;

	if (ac > 2 || (ac == 2 &&
		(!ft_isstrdigit(av[1]) || av[1][0] == '0' || ft_atoi(av[1]) < 1)))
	{
		ft_printf("Usage: ./lem-in < target_map [recursion_limit]\n");
		exit(1);
	}
	ft_bzero(&f, sizeof(t_anthill));
	f.ant_ct = -1;
	f.limit_rec = INT_MAX;
	if (ac == 2)
		f.limit_rec = ft_atoi(av[1]);
	if (lemin_parsing(&f))
		free_exit(&f, NULL, 1);
	if (f.room_start && f.room_end && f.ant_ct > 0)
	{
		if (launch_algo(&f))
			free_exit(&f, NULL, 1);
	}
	else
		free_exit(&f, NULL, 1);
	return (0);
}
