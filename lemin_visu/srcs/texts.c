/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:13:36 by sjimenez          #+#    #+#             */
/*   Updated: 2018/03/08 22:16:22 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

void		draw_title(char *text, t_sdlobj *a)
{
	SDL_Rect	text_rect;
	TTF_Font	*font;
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	color;

	color.r = 66;
	color.g = 66;
	color.b = 66;
	color.a = 255;
	text_rect.x = RES_X / 3;
	text_rect.y = 10;
	text_rect.w = RES_X / 3;
	text_rect.h = text_rect.w / 6;
	font = TTF_OpenFont("lemin_visu/d3egoistism.ttf", 96);
	surface = TTF_RenderText_Solid(font, text, color);
	texture = SDL_CreateTextureFromSurface(a->rend, surface);
	SDL_RenderCopy(a->rend, texture, NULL, &text_rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void		draw_room_title(SDL_Rect *rect, char *text, t_sdlobj *a)
{
	SDL_Rect	text_rect;
	TTF_Font	*font;
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	color;

	color.r = 0xEE;
	color.g = 0xEE;
	color.b = 0xEE;
	color.a = 255;
	font = TTF_OpenFont("lemin_visu/f1.ttf", 96);
	surface = TTF_RenderText_Solid(font, text, color);
	texture = SDL_CreateTextureFromSurface(a->rend, surface);
	text_rect.x = rect->x + 7;
	text_rect.y = rect->y - 4;
	text_rect.w = rect->w - 14;
	text_rect.h = rect->h + 7;
	SDL_RenderCopy(a->rend, texture, NULL, &text_rect);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
}
