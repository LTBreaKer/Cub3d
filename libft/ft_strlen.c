/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:18:53 by rel-mham          #+#    #+#             */
/*   Updated: 2023/06/01 13:54:31 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n')
	{
		i++;
	}
	return (i);
}

size_t	ft_double_strlen(char **s)
{
	size_t	i;

	i = 0;
	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	count_char(char *str, char c)
{
	int	v;
	int	i;

	i = 0;
	v = 0;
	while (str[i])
	{
		if (str[i] == c)
			v++;
		i++;
	}
	return (v);
}
