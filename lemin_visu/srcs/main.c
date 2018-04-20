/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 20:47:49 by sjimenez          #+#    #+#             */
/*   Updated: 2018/03/08 22:03:31 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

void		free_exit(t_anthill *f, char *l_free, int error)
{
	t_room_lst	*to_free;

	error ? ft_putendl("ERROR") : 0;
	l_free ? free(l_free) : 0;
	to_free = f->head;
	while (f->head)
	{
		to_free = f->head->next;
		if (f->head->salle)
		{
			ft_strdel(&f->head->salle->name);
			f->head->salle->links ? free(f->head->salle->links) : 0;
			free(f->head->salle);
		}
		free(f->head);
		f->head = to_free;
	}
	ft_strdel(&f->buf);
	exit(0);
}

void		set_room_coor(t_anthill *f)
{
	t_room_lst	*lst;

	lst = f->head;
	while (lst)
	{
		lst->salle->vis_x = PAD_X + (int)(((float)(RES_X - (2 * PAD_X))
			/ (float)(f->limits_x[1] - f->limits_x[0]))
			* (float)(lst->salle->x - f->limits_x[0]));
		lst->salle->vis_x > RES_X ? lst->salle->vis_x = RES_X - PAD_X : 0;
		lst->salle->vis_y = PAD_Y + (PAD_Y / 2) + (int)(((float)
			(RES_Y - (2 * PAD_Y + PAD_BG_Y))
			/ (float)(f->limits_y[1] - f->limits_y[0]))
			* (float)(lst->salle->y - f->limits_y[0]));
		lst->salle->vis_y > RES_Y ? lst->salle->vis_y = (RES_Y - 100)
			- PAD_Y : 0;
		lst = lst->next;
	}
}

int			add_line_buf(t_anthill *f, char **l)
{
	if (!(f->buf = ft_strjoin_free(f->buf, *l, 3)))
		return (1);
	if (!(f->buf = ft_strjoin_free(f->buf, "\n", 1)))
		return (1);
	*l = NULL;
	return (0);
}

int			main(void)
{
	t_room_lst	*salles;
	t_anthill	f;

	ft_bzero(&f, sizeof(t_anthill));
	f.ant_ct = -1;
	salles = NULL;
	if (!lemin_parsing(&f))
	{
		!f.room_start || !f.room_end ? free_exit(&f, NULL, 1) : 0;
		ft_printf("----------\nShortcuts:\n----------\n");
		ft_printf("Rigth  -> Advance 1 step\n");
		ft_printf("Left   -> Return 1 step\nN      -> Show names\n");
		ft_printf("S      -> Show Start - End\nESC    -> Exit program\n");
		ft_printf("[      -> Ants Size - 1\n]      -> Ants Size + 1\n");
		ft_printf(",      -> Room Size - 1\n.      -> Room Size + 1\n");
		show_map(&f);
	}
	free_exit(&f, NULL, 0);
	return (0);
}
