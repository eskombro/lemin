/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 21:54:18 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/10 15:47:22 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_line_buf(char **l)
{
	ft_putstr(*l);
	ft_putchar('\n');
	ft_strdel(l);
}

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
		add_line_buf(l);
	}
	else if (*step == ANT && ft_isstrdigit(*l) && ft_atoi(*l) >= 0)
	{
		f->ant_ct = ft_atol(*l);
		*step = ROOM;
		add_line_buf(l);
	}
	else if (*step == ROOM && ft_countchar(*l, ' ') == 2)
	{
		*exit_pars += create_room(*l, f);
		if (!*exit_pars)
			add_line_buf(l);
	}
	else if (*step != ANT && ft_countchar(*l, '-') == 1)
	{
		*exit_pars += create_link(*l, f->head, f->room_ct);
		*step != ROOM ? *step = LINK : 0;
		if (!*exit_pars)
			add_line_buf(l);
	}
	return (*exit_pars);
}

int		lemin_parsing(t_anthill *f)
{
	char	*l;
	int		exit_pars;
	int		step;

	exit_pars = 0;
	f->comment = 0;
	step = 0;
	if (!(f->buf = ft_strnew(1)))
		return (-1);
	while (ft_gnl(0, &l))
	{
		if (handle_valid_line(&l, f, &step, &exit_pars))
			break ;
	}
	l ? ft_strdel(&l) : 0;
	return (0);
}
