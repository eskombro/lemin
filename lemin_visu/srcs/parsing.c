/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 21:54:18 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/06 03:05:29 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

int		handle_comment(t_anthill *f, char *l)
{
	int error;

	error = 0;
	if (!ft_strcmp(l, "##start"))
		!f->room_start && f->comment == COMMENT ? f->comment = START : error++;
	else if (!ft_strcmp(l, "##end"))
		!f->room_end && f->comment == COMMENT ? f->comment = END : error++;
	return (error);
}

int		handle_valid_line(char **l, t_anthill *f, int *step, int *exit_pars)
{
	if (*l[0] == '#')
	{
		*exit_pars += handle_comment(f, *l);
		f->buf_error = add_line_buf(f, l);
	}
	else if (*step == ANT && ft_isstrdigit(*l) && ft_atoi(*l) >= 0)
	{
		f->ant_ct = ft_atol(*l);
		*step = ROOM;
		f->buf_error = add_line_buf(f, l);
	}
	else if (*step == ROOM && ft_countchar(*l, ' ') == 2)
	{
		if ((*exit_pars += create_room(*l, f)) == 0)
			f->buf_error = add_line_buf(f, l);
	}
	else if ((*step == ROOM || *step == LINK) && ft_countchar(*l, '-') == 1)
	{
		*step != ROOM ? *step = LINK : 0;
		if ((*exit_pars += create_link(*l, f->head, f->room_ct)) == 0)
			f->buf_error = add_line_buf(f, l);
	}
	else if (*l[0] == 0)
		*step != MOVE ? *step = MOVE : 0;
	return (*exit_pars);
}

int		parse_line_algo(char *l, t_anthill *f)
{
	char		**line;
	int			i;
	int			t;
	t_room_lst	*lst;

	i = -1;
	if (!l || l[0] != 'L' || !(line = ft_strsplit(l, ' ')))
		return (1);
	while (line[++i])
	{
		t = 0;
		if (line[i][t++] != 'L' || ft_atoi(line[i] + 1) > f->ant_ct)
			return (1);
		while (ft_isdigit(line[i][t]))
			t++;
		if (line[i][t++] != '-' || ft_countchar(line[i], '-') > 1)
			return (1);
		lst = f->head;
		while (line[i] + t && lst && ft_strcmp(lst->salle->name, line[i] + t))
			lst = lst->next;
		if (!lst)
			return (1);
	}
	line ? ft_freetabstr(line) : 0;
	return (0);
}

void	parsing_handle_gnl(t_anthill *f, char *l)
{
	static int	empty_lines = 0;
	int			exit_pars;
	static int	step;

	exit_pars = 0;
	if (!ft_strcmp(l, "ERROR"))
		free_exit(f, l, 1);
	else if (handle_valid_line(&l, f, &step, &exit_pars))
		free_exit(f, l, 1);
	if (l && !*l && empty_lines++)
		free_exit(f, l, 1);
	else if (l && *l && empty_lines == 1 && parse_line_algo(l, f))
		free_exit(f, l, 1);
	if (step != 0 && f->ant_ct < 1)
		free_exit(f, l, 1);
	f->algo_ret = ft_maltabtab(f->algo_ret, l);
	if (f->algo_ret)
		f->frames++;
	l ? ft_strdel(&l) : 0;
}

int		lemin_parsing(t_anthill *f)
{
	char	*l;
	int		step;

	f->comment = 0;
	f->frames = 0;
	f->limits_x[0] = INT_MIN;
	f->limits_x[1] = INT_MIN;
	f->limits_y[0] = INT_MIN;
	f->limits_y[0] = INT_MIN;
	step = 0;
	if (!(f->buf = ft_strnew(1)))
		return (-1);
	while (ft_gnl(0, &l) > 0)
		parsing_handle_gnl(f, l);
	if (!f->algo_ret)
		free_exit(f, l, 1);
	f->ant_ct >= 1 ? set_ants(f) : 0;
	l ? ft_strdel(&l) : 0;
	return (0);
}
