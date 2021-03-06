/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 23:12:18 by sjimenez          #+#    #+#             */
/*   Updated: 2018/02/09 17:23:40 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isstrdigit(char *s)
{
	int		i;

	i = -1;
	if (!s || !*s)
		return (0);
	while (s[++i])
		if (s[i] > '9' || s[i] < '0')
			return (0);
	return (1);
}
