/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhigelin <dhigelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:24:05 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/11 15:11:36 by dhigelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

int			set_ants(t_anthill *f)
{
	int			i;

	if (!(f->ants = (t_salle**)ft_memalloc(sizeof(t_salle*) * (f->ant_ct + 1))))
		return (-1);
	i = 0;
	while (i < f->ant_ct)
		f->ants[i++] = f->room_start;
	return (0);
}

int			check_start(t_sdlobj *a, t_anthill *f)
{
	int			i;

	i = -1;
	if (a->frame == 0)
	{
		while (f->ants[++i])
			f->ants[i] = f->room_start;
		return (1);
	}
	while (f->ants[++i])
		f->ants[i] != f->room_end ? f->ants[i] = f->room_start : 0;
	return (0);
}

void		ants_position(t_sdlobj *a, t_anthill *f)
{
	char		**line;
	int			s;
	int			i;
	int			ind;
	t_room_lst	*lst;

	i = -1;
	s = 0;
	line = ft_strsplit(f->algo_ret[a->frame], ' ');
	if (check_start(a, f))
		return ;
	i = -1;
	while (line[++i])
	{
		lst = f->head;
		ind = -1;
		while (lst && ft_strcmp(lst->salle->name, ft_strchr(line[i], '-') + 1))
			lst = lst->next;
		ind = ft_atoi(line[i] + 1) - 1;
		f->ants[ind] = lst->salle;
		s == 0 ? s = ind : 0;
	}
	while (s--)
		f->ants[s + 1] == f->room_end ? f->ants[s] = f->room_end : 0;
	ft_freetabstr(line);
}

void		draw_ant_img(t_pos *pos, int st, t_sdlobj *a, unsigned int color)
{
	draw_fill_circle(*pos, st, a->rend, 0x111111FF);
	draw_fill_circle(*pos, st - 2, a->rend, color);
	pos->x += st;
	draw_fill_circle(*pos, st - 4, a->rend, 0x111111FF);
	draw_fill_circle(*pos, st - 6, a->rend, color);
	pos->x += st;
	draw_fill_circle(*pos, st, a->rend, 0x111111FF);
	draw_fill_circle(*pos, st - 2, a->rend, color);
	SDL_SetRenderDrawColor(a->rend, 0x11, 0x11, 0x11, 255);
	SDL_RenderDrawLine(a->rend, pos->x + st, pos->y - 3,
		pos->x + st + 6, pos->y - 6);
	SDL_RenderDrawLine(a->rend, pos->x + st + 1, pos->y - 3,
		pos->x + st + 7, pos->y - 6);
	SDL_RenderDrawLine(a->rend, pos->x + st, pos->y + 3,
		pos->x + st + 6, pos->y + 6);
	SDL_RenderDrawLine(a->rend, pos->x + st + 1, pos->y + 3,
	pos->x + st + 7, pos->y + 6);
	pos->x += st / 2;
	pos->y -= st / 4;
	draw_fill_circle(*pos, st * 0.1, a->rend, 0x111111FF);
	pos->y += 2 * (st / 4);
	draw_fill_circle(*pos, st * 0.1, a->rend, 0x111111FF);
}

void		draw_ants(t_anthill *f, t_sdlobj *a)
{
	int				i;
	t_pos			pos;
	unsigned int	color;
	int				st;
	int				end_shown;

	i = f->ant_ct;
	st = f->ant_size;
	end_shown = 0;
	while (--i + 1)
	{
		if (!(f->ants[i] == f->room_end && end_shown) && (!f->ants[i + 1]
			|| (f->ants[i + 1] && f->ants[i + 1]->next != f->room_start)))
		{
			color = 0x776655FF + (0x00912100 * i);
			pos.x = f->ants[i]->vis_x - st;
			pos.y = f->ants[i]->vis_y;
			f->ants[i] == f->room_end ? end_shown = 1 : 0;
			draw_ant_img(&pos, st, a, color);
		}
	}
}
