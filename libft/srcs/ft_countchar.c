/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhigelin <dhigelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 21:57:03 by sjimenez          #+#    #+#             */
/*   Updated: 2018/02/12 16:25:50 by dhigelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_countchar(char *s, char c)
{
	int i;
	int ct_sp;

	ct_sp = 0;
	i = -1;
	while (s[++i])
		if (s[i] == c)
			ct_sp++;
	return (ct_sp);
}
