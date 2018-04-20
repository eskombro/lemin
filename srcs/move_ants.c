/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 00:38:58 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/10 15:34:20 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		move_middle_ants(t_anthill *f, t_salle **ants)
{
	int			i;

	i = -1;
	while (ants[++i])
	{
		if (ants[i] != f->room_start && ants[i] != f->room_end)
		{
			ants[i] = ants[i]->next;
			ft_printf("L%d-%s ", i + 1, ants[i]->name);
		}
	}
}

void		launch_start_ants(t_anthill *f, t_salle **ants)
{
	int			k;
	int			i;
	int			nb_path;

	nb_path = 0;
	k = -1;
	i = 0;
	while (f->room_start->next_start[nb_path])
		nb_path++;
	while (ants[i] && ants[i] != f->room_start)
		i++;
	while (++k < nb_path)
	{
		if (i + k < f->ant_ct)
		{
			ants[i + k] = f->room_start->next_start[k];
			ft_printf("L%d-%s ", k + i + 1, ants[k + i]->name);
		}
	}
}

void		print_ants(t_anthill *f, t_salle **ants, int *end_ct)
{
	int			i;

	move_middle_ants(f, ants);
	launch_start_ants(f, ants);
	i = 0;
	while (ants[i++] == f->room_end)
		*end_ct = i;
	ft_putchar('\n');
}

int			move_ants(t_anthill *f)
{
	t_salle		**ants;
	int			i;
	int			end_ct;

	end_ct = 0;
	if (!(ants = (t_salle**)ft_memalloc(sizeof(t_salle*) * (f->ant_ct + 1))))
		return (-1);
	i = -1;
	while (++i < f->ant_ct)
		ants[i] = f->room_start;
	i = -1;
	if (f->room_start->next_start[0] == f->room_end)
	{
		while (ants[++i])
		{
			ft_printf("L%d-%s", i + 1, f->room_end->name);
			ft_putchar(i == f->ant_ct - 1 ? '\n' : ' ');
		}
		free(ants);
		return (0);
	}
	while (end_ct < f->ant_ct)
		print_ants(f, ants, &end_ct);
	free(ants);
	return (0);
}
