/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 05:06:59 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/30 05:09:27 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtolower(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		s[i] = ft_tolower(s[i]);
	return (s);
}
