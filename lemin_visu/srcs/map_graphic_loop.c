/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_graphic_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:18:45 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/10 16:02:34 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

void		refresh_screen(t_sdlobj *a, t_anthill *f)
{
	SDL_SetRenderDrawColor(a->rend, 0, 0, 0, 255);
	SDL_RenderClear(a->rend);
	draw_background(a);
	set_room_coor(f);
	draw_tunnels(f, a);
	draw_room_circles(f, a);
	draw_ants(f, a);
	SDL_RenderPresent(a->rend);
	f->boolean ^= VISU_CHANGE;
}

void		handle_key_events(SDL_Event e, t_anthill *f, t_sdlobj *a)
{
	if (e.key.keysym.sym == SDLK_ESCAPE)
		f->boolean |= VISU_QUIT;
	if (e.key.keysym.sym == SDLK_RIGHT)
		if (f->ants[f->ant_ct - 1] != f->room_end || a->frame < f->frames ||
		(f->ant_ct == 1 && a->frame < f->path_len + 3))
			a->frame++;
	if (e.key.keysym.sym == SDLK_LEFT)
		a->frame > 0 ? a->frame-- : 0;
	if (e.key.keysym.sym == SDLK_n)
		f->boolean ^= SHOW_NAMES;
	if (e.key.keysym.sym == SDLK_s)
		f->boolean ^= SHOW_ST_END;
	if (a->frame >= f->frames)
		a->frame = f->frames - 1;
	if (e.key.keysym.sym == SDLK_PERIOD)
		f->room_size < 60 ? f->room_size++ : 0;
	if (e.key.keysym.sym == SDLK_COMMA)
		f->room_size > 5 ? f->room_size-- : 0;
	if (e.key.keysym.sym == SDLK_RIGHTBRACKET)
		f->ant_size < 45 ? f->ant_size++ : 0;
	if (e.key.keysym.sym == SDLK_LEFTBRACKET)
		f->ant_size > 5 ? f->ant_size-- : 0;
}

void		main_graphic_loop(t_sdlobj *a, t_anthill *f)
{
	SDL_Event	e;

	f->boolean |= VISU_CHANGE;
	f->boolean ^= SHOW_ST_END;
	a->frame = 0;
	while (!(f->boolean & VISU_QUIT))
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				f->boolean |= VISU_QUIT;
			if (e.type == SDL_KEYDOWN)
			{
				handle_key_events(e, f, a);
				ants_position(a, f);
				f->boolean |= VISU_CHANGE;
			}
		}
		if (f->boolean & VISU_CHANGE)
			refresh_screen(a, f);
	}
}

void		show_map(t_anthill *f)
{
	t_sdlobj	a;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	a.win = SDL_CreateWindow("Lemin Visualizer || sjimenez - dhigelin",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES_X, RES_Y, 0);
	a.rend = SDL_CreateRenderer(a.win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(a.rend, SDL_BLENDMODE_BLEND);
	TTF_Init();
	main_graphic_loop(&a, f);
	TTF_Quit();
	SDL_RenderClear(a.rend);
	SDL_DestroyRenderer(a.rend);
	SDL_DestroyWindow(a.win);
	SDL_Quit();
}
