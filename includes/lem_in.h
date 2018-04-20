/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 21:55:46 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/10 15:46:44 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

enum	{ANT, ROOM, LINK};
enum	{COMMENT, START, END};

typedef struct			s_salle
{
	int					x;
	int					y;
	char				*name;
	struct s_salle		**links;
	struct s_salle		*next;
	struct s_salle		**next_start;
	int					nb_fr;
	int					len_end;
	int					id;
	int					taken;
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
	int					current_path;
	int					max_path;
	int					*path_len;
	char				*buf;
	int					buf_error;
	int					comment;
	int					*room_tab;
	int					limit_rec;
	int					print_path;
}						t_anthill;

/*
** main.c
*/
void					free_exit(t_anthill *f, char *l_free, int error);
int						recursive(t_salle *salle, int *room_tab,
									t_anthill *f, int lim);

/*
** parsing.c
*/
void					add_line_buf(char **l);
int						handle_comment(t_anthill *f, char *l);
int						handle_valid_line(char **l, t_anthill *f, int *step,
									int *exit_pars);
int						lemin_parsing(t_anthill *f);

/*
** parsing2.c
*/
void					assign_room(t_salle *salle, char **tab,
									t_anthill *f, t_room_lst *tmp);
int						room_malloc(t_salle **salle, t_room_lst **tmp,
									char ***tab, char *l);
int						create_room(char *l, t_anthill *f);
int						assign_link(t_salle *salle, t_salle *link, int room_ct);
int						create_link(char *l, t_room_lst *head, int room_ct);

/*
** move_ants.c
*/
int						move_ants(t_anthill *f);
void					print_ants(t_anthill *f, t_salle **ants, int *end_ct);

/*
** paths.c
*/
int						find_max_path(t_anthill *f);
void					order_paths(t_anthill *f);
void					printf_paths(t_anthill *f);
void					initiaize_rooms(t_anthill *f);
void					look_for_paths(t_anthill *f, int *room_tab);

#endif
