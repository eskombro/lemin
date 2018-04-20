/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:08:43 by sjimenez          #+#    #+#             */
/*   Updated: 2018/03/08 22:09:50 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

void	draw_background(t_sdlobj *a)
{
	SDL_Rect rect;

	rect.x = PAD_BG_X;
	rect.y = PAD_BG_Y;
	rect.w = RES_X - (2 * PAD_BG_X);
	rect.h = (RES_Y - PAD_Y) / 2;
	SDL_SetRenderDrawColor(a->rend, 0x66, 0x66, 0x66, 255);
	SDL_RenderFillRect(a->rend, &rect);
	rect.y += (RES_Y - PAD_Y) / 2;
	SDL_SetRenderDrawColor(a->rend, 0x70, 0x70, 0x70, 255);
	SDL_RenderFillRect(a->rend, &rect);
	rect.x = PAD_BG_X + 20;
	rect.y = PAD_BG_Y + 20;
	rect.w = RES_X - (2 * PAD_BG_X + 40);
	rect.h = (RES_Y - (PAD_Y + 40)) / 2;
	SDL_SetRenderDrawColor(a->rend, 0x33, 0x33, 0x33, 255);
	SDL_RenderFillRect(a->rend, &rect);
	rect.y += (RES_Y - (PAD_Y + 40)) / 2;
	SDL_SetRenderDrawColor(a->rend, 0x37, 0x37, 0x37, 255);
	SDL_RenderFillRect(a->rend, &rect);
	draw_title("Lem-in Visualizer", a);
}

void	draw_tunnels(t_anthill *f, t_sdlobj *a)
{
	int			i;
	t_pos		st;
	t_pos		end;
	t_room_lst	*lst;

	lst = f->head;
	while (lst)
	{
		i = -1;
		while (lst->salle && lst->salle->links && lst->salle->links[++i])
		{
			st.x = lst->salle->vis_x;
			st.y = lst->salle->vis_y;
			end.x = lst->salle->links[i]->vis_x;
			end.y = lst->salle->links[i]->vis_y;
			SDL_SetRenderDrawColor(a->rend, 0xFF, 0xFF, 0xFF, 255);
			SDL_RenderDrawLine(a->rend, st.x, st.y, end.x, end.y);
			SDL_RenderDrawLine(a->rend, st.x + 1, st.y, end.x + 1, end.y);
			SDL_RenderDrawLine(a->rend, st.x, st.y + 1, end.x, end.y + 1);
		}
		lst = lst->next;
	}
}

void	show_room_names(SDL_Rect *r, t_pos *pos, t_sdlobj *a, t_room_lst *lst)
{
	r->x = pos->x - 40;
	r->y = pos->y + 30;
	r->w = 80;
	r->h = 45;
	SDL_SetRenderDrawColor(a->rend, 0xCC, 0xCC, 0xCC, 100);
	SDL_RenderFillRect(a->rend, r);
	r->x = pos->x - 35;
	r->y = pos->y + 35;
	r->w = 70;
	r->h = 35;
	SDL_SetRenderDrawColor(a->rend, 0xFF, 0xFF, 0xFF, 100);
	SDL_RenderFillRect(a->rend, r);
	SDL_SetRenderDrawColor(a->rend, 0xCC, 0xCC, 0xCC, 255);
	draw_room_title(r, lst->salle->name, a);
}

void	draw_room_circles(t_anthill *f, t_sdlobj *a)
{
	t_room_lst	*lst;
	t_pos		pos;
	SDL_Rect	rect;

	f->room_ct <= 20 && !f->room_size ? f->room_size = 40 : 0;
	f->room_ct <= 30 && !f->room_size ? f->room_size = 20 : 0;
	f->room_ct > 30 && !f->room_size ? f->room_size = 12 : 0;
	f->room_ct <= 20 && !f->ant_size ? f->ant_size = 12 : 0;
	f->room_ct <= 30 && !f->ant_size ? f->ant_size = 11 : 0;
	f->room_ct > 30 && !f->ant_size ? f->ant_size = 9 : 0;
	lst = f->head;
	while (lst)
	{
		pos.x = lst->salle->vis_x;
		pos.y = lst->salle->vis_y;
		if (f->boolean & SHOW_NAMES)
			show_room_names(&rect, &pos, a, lst);
		if (f->boolean & SHOW_ST_END && (lst->salle == f->room_start
			|| lst->salle == f->room_end))
			draw_fill_circle(pos, f->room_size + 10, a->rend, 0x000000FF);
		draw_fill_circle(pos, f->room_size, a->rend, 0xCCCCCCFF);
		draw_fill_circle(pos, f->room_size - 10, a->rend, 0xFFFFFFFF);
		lst = lst->next;
	}
}
