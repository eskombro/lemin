/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:23:40 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/06 20:58:03 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_VISU_H
# define LEM_IN_VISU_H
# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

# define RES_X 1600
# define RES_Y 1000
# define PAD_X 150
# define PAD_Y 150
# define PAD_BG_X 50
# define PAD_BG_Y 100

enum	{ANT, ROOM, LINK, MOVE};
enum	{COMMENT, START, END};
enum	{VISU_QUIT = 1, VISU_CHANGE = 2, SHOW_NAMES = 4, SHOW_ST_END = 8};

typedef struct			s_salle
{
	int					x;
	int					y;
	unsigned int		vis_x;
	unsigned int		vis_y;
	char				*name;
	struct s_salle		**links;
	struct s_salle		*next;
	int					nb_fr;
}						t_salle;

typedef struct			s_room_lst
{
	t_salle				*salle;
	struct s_room_lst	*next;
}						t_room_lst;

typedef struct			s_anthill
{
	long				ant_ct;
	int					room_ct;
	t_salle				*room_start;
	t_salle				*room_end;
	t_room_lst			*head;
	int					path_len;
	char				*buf;
	int					buf_error;
	int					comment;
	int					limits_x[2];
	int					limits_y[2];
	char				**algo_ret;
	int					frames;
	t_salle				**ants;
	char				boolean;
	unsigned int		ant_size;
	unsigned int		room_size;
}						t_anthill;

typedef struct			s_sdlobj
{
	SDL_Window			*win;
	SDL_Event			event;
	SDL_Renderer		*rend;
	SDL_Texture			*imgbg;
	int					frame;
}						t_sdlobj;

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct			s_line
{
	float				gradient;
	float				xend;
	float				yend;
	int					xpxl1;
	int					xpxl2;
	int					ypxl1;
	int					ypxl2;
	float				inter;
	int					i;
	float				gap;
	int					horizontal;
}						t_line;

/*
** main.c
*/
void					free_exit(t_anthill *f, char *l_free, int error);
void					set_room_coor(t_anthill *f);
int						add_line_buf(t_anthill *f, char **l);

/*
** parsing.c
*/
int						handle_comment(t_anthill *f, char *l);
int						handle_valid_line(char **l, t_anthill *f,
									int *step, int *exit_pars);
int						parse_line_algo(char *l, t_anthill *f);
void					parsing_handle_gnl(t_anthill *f, char *l);
int						lemin_parsing(t_anthill *f);

/*
** parsing2.c
*/
void					assign_room(t_salle *salle, char **tab,
									t_anthill *f, t_room_lst *tmp);
int						room_malloc(t_salle **salle, t_room_lst **tmp,
									char ***tab, char *l);
int						create_room(char *l, t_anthill *f);
int						assign_link(t_salle *salle, t_salle *link,
									int room_ct);
int						create_link(char *l, t_room_lst *head, int room_ct);

/*
** map_graphic_loop.c
*/
void					refresh_screen(t_sdlobj *a, t_anthill *f);
void					handle_key_events(SDL_Event e, t_anthill *f,
									t_sdlobj *a);
void					main_graphic_loop(t_sdlobj *a, t_anthill *f);
void					show_map(t_anthill *f);

/*
** drawing.c
*/
void					draw_background(t_sdlobj *a);
void					draw_tunnels(t_anthill *f, t_sdlobj *a);
void					show_room_names(SDL_Rect *r, t_pos *pos, t_sdlobj *a,
									t_room_lst *lst);
void					draw_room_title(SDL_Rect *rect, char *text,
									t_sdlobj *a);
void					draw_room_circles(t_anthill *f, t_sdlobj *a);

/*
** ants.c
*/
int						set_ants(t_anthill *f);
void					ants_position(t_sdlobj *a, t_anthill *f);
void					draw_ant_img(t_pos *pos, int st, t_sdlobj *a,
									unsigned int color);
void					draw_ants(t_anthill *f, t_sdlobj *a);

/*
** sdl_basics.c
*/
void					put_pixel_sdl(int x, int y, SDL_Renderer *rend,
									unsigned int color);
void					put_big_pixel_sdl(int x, int y, SDL_Renderer *rend,
									unsigned int color);
void					draw_circle(t_pos pos, int rad, SDL_Renderer *rend,
									unsigned int c);
void					draw_fill_circle(t_pos pos, int rad, SDL_Renderer *rend,
									unsigned int color);

/*
** texts.c
*/
void					draw_title(char *text, t_sdlobj *a);
void					draw_room_title(SDL_Rect *rect, char *text,
									t_sdlobj *a);

#endif
