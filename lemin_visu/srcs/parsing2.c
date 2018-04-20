/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:36:53 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/11 15:01:04 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visu.h"

void	assign_room(t_salle *salle, char **tab, t_anthill *f, t_room_lst *tmp)
{
	salle->x = ft_atoi(tab[1]);
	salle->y = ft_atoi(tab[2]);
	salle->next = NULL;
	salle->links = NULL;
	tmp->salle = salle;
	if (f->head == NULL)
		tmp->next = NULL;
	else
		tmp->next = f->head;
	f->head = tmp;
	f->comment == 1 ? f->room_start = salle : 0;
	f->comment == 2 ? f->room_end = salle : 0;
	f->comment != 0 ? f->comment = 0 : 0;
	(f->room_ct)++;
	salle->x < f->limits_x[0] || f->limits_x[0] == INT_MIN ?
			f->limits_x[0] = salle->x : 0;
	salle->x > f->limits_x[1] || f->limits_x[1] == INT_MIN ?
			f->limits_x[1] = salle->x : 0;
	salle->y < f->limits_y[0] || f->limits_y[0] == INT_MIN ?
			f->limits_y[0] = salle->y : 0;
	salle->y > f->limits_y[1] || f->limits_y[1] == INT_MIN ?
			f->limits_y[1] = salle->y : 0;
}

int		room_malloc(t_salle **salle, t_room_lst **tmp, char ***tab, char *l)
{
	if (!(*salle = (t_salle*)ft_memalloc(sizeof(t_salle))))
		return (1);
	if (!(*tmp = (t_room_lst*)ft_memalloc(sizeof(t_room_lst))))
		return (1);
	if (!(*tab = ft_strsplit(l, ' ')))
		return (1);
	return (0);
}

int		create_room(char *l, t_anthill *f)
{
	char		**tab;
	t_salle		*salle;
	t_room_lst	*tmp;
	t_room_lst	*tmp2;

	if (room_malloc(&salle, &tmp, &tab, l))
		return (1);
	tmp2 = f->head;
	while (tmp2 && ft_strcmp(tmp2->salle->name, tab[0]) &&
		(tmp2->salle->x != ft_atoi(tab[1])
			|| tmp2->salle->y != ft_atoi(tab[2])))
		tmp2 = tmp2->next;
	if (tmp2 || !ft_isstrnumber(tab[1]) || !ft_isstrnumber(tab[2]) ||
		tab[0][0] == 'L')
	{
		ft_freetabstr(tab);
		free(salle);
		free(tmp);
		return (1);
	}
	if (!(salle->name = (char *)ft_strdup(tab[0])))
		return (1);
	assign_room(salle, tab, f, tmp);
	ft_freetabstr(tab);
	return (0);
}

int		assign_link(t_salle *salle, t_salle *link, int room_ct)
{
	int		i;

	i = 0;
	if (!salle->links)
		if (!(salle->links =
			(t_salle **)ft_memalloc(sizeof(t_salle*) * room_ct)))
			return (1);
	while (salle->links[i])
	{
		if (salle->links[i] == link)
			return (0);
		i++;
	}
	salle->links[i] = link;
	return (2);
}

int		create_link(char *l, t_room_lst *head, int room_ct)
{
	char		**tab;
	t_salle		*tmp[2];
	int			ret;

	if (!(tab = ft_strsplit(l, '-')))
		return (1);
	tmp[0] = NULL;
	tmp[1] = NULL;
	while (head)
	{
		if (!ft_strcmp(head->salle->name, tab[0]))
			tmp[0] = head->salle;
		else if (!ft_strcmp(head->salle->name, tab[1]))
			tmp[1] = head->salle;
		head = head->next;
	}
	ft_freetabstr(tab);
	if (!tmp[0] || !tmp[1])
		return (1);
	if ((ret = assign_link(tmp[0], tmp[1], room_ct)) != 2)
		return (ret);
	if ((ret = assign_link(tmp[1], tmp[0], room_ct)) != 2)
		return (ret);
	return (0);
}
