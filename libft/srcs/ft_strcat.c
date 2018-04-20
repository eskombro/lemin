/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:16:43 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/12 06:30:54 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1t, const char *s2)
{
	size_t i;
	size_t t;

	i = ft_strlen(s1t);
	t = 0;
	while (s2[t])
		s1t[i++] = s2[t++];
	s1t[i] = '\0';
	return (s1t);
}
