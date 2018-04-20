/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 00:56:01 by sjimenez          #+#    #+#             */
/*   Updated: 2018/03/06 19:24:06 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

void	put_pixel_sdl(int x, int y, SDL_Renderer *rend, unsigned int color)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	r = (color & 0xFF000000) >> 24;
	g = (color & 0xFF0000) >> 16;
	b = (color & 0xFF00) >> 8;
	a = (color & 0xFF);
	SDL_SetRenderDrawColor(rend, r, g, b, a);
	SDL_RenderDrawPoint(rend, x, y);
}

void	put_big_pixel_sdl(int x, int y, SDL_Renderer *rend, unsigned int color)
{
	put_pixel_sdl(x, y, rend, color);
	put_pixel_sdl(x + 1, y, rend, color);
	put_pixel_sdl(x, y + 1, rend, color);
	put_pixel_sdl(x + 1, y + 1, rend, color);
}

void	draw_circle(t_pos pos, int rad, SDL_Renderer *rend, unsigned int c)
{
	int		pos_x;
	int		pos_y;
	float	dist;

	pos_x = pos.x - rad - 1;
	while (++pos_x <= pos.x + rad)
	{
		pos_y = pos.y - rad - 1;
		while (++pos_y <= pos.y + rad)
		{
			dist = sqrt(pow(pos_x - pos.x, 2) + pow(pos_y - pos.y, 2));
			if (dist <= rad && dist >= rad - 3)
				put_pixel_sdl(pos_x, pos_y, rend, c);
			else if (dist <= rad + 1 && dist > rad - 3)
				put_pixel_sdl(pos_x, pos_y, rend, c & 0xFFFFFF00
						+ (int)((1.0 - (dist - rad)) * 255));
			else if (dist < rad && dist >= rad - 4)
				put_pixel_sdl(pos_x, pos_y, rend, c & 0xFFFFFF00
						+ (int)((1.0 + (dist - rad)) * 255));
		}
	}
}

void	draw_fill_circle(t_pos pos, int rad, SDL_Renderer *rend, unsigned int c)
{
	int		pos_x;
	int		pos_y;
	float	dist;

	pos_x = pos.x - rad - 1;
	while (++pos_x <= pos.x + rad)
	{
		pos_y = pos.y - rad - 1;
		while (++pos_y <= pos.y + rad)
		{
			dist = sqrt(pow(pos_x - pos.x, 2) + pow(pos_y - pos.y, 2));
			if (dist <= rad)
				put_pixel_sdl(pos_x, pos_y, rend, c);
			else if (dist <= rad + 1)
				put_pixel_sdl(pos_x, pos_y, rend, ((c / 256) * 256)
						+ (int)((1.0 - (dist - rad)) * 255));
		}
	}
}
