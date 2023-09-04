/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_str_to_wordtab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:25:23 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 02:41:19 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_str_str(char *str, char *find, int len)
{
	int		len_f;
	int		pos;
	char	*s;
	char	*f;

	len_f = strlen(find);
	if (len_f > len)
		return (-1);
	pos = 0;
	while (str[len_f - 1])
	{
		s = str;
		f = find;
		while (*f++ == *s++)
			if (!*f)
				return (pos);
		++str;
		++pos;
	}
	return (-1);
}

int	mlx_int_str_str_cote(char *str, char *find, int len)
{
	int		len_f;
	int		pos;
	char	*s;
	char	*f;
	int		cote;

	len_f = strlen(find);
	if (len_f > len)
		return (-1);
	cote = 0;
	pos = 0;
	while (str[len_f - 1])
	{
		cote = (*str == '"') * (1 - cote) + (*str != '"') * cote;
		++str;
		++pos;
		if (cote)
			continue ;
		s = str - 1;
		f = find;
		while (*f++ == *s++)
			if (!*f)
				return (pos - 1);
	}
	return (-1);
}

char	**_mlx_int_str_to_wordtab(char *str, int len, char **tab)
{
	int	nb_word;
	int	pos;

	nb_word = 0;
	pos = 0;
	while (pos < len)
	{
		while (str[pos] == ' ' || str[pos] == '\t')
		{
			str[pos] = 0;
			++pos;
		}
		if (str[pos])
		{
			tab[nb_word] = str + pos;
			nb_word ++;
		}
		while (str[pos] && str[pos] != ' ' && str[pos] != '\t')
			++pos;
	}
	tab[nb_word] = 0;
	return (tab);
}

char	**mlx_int_str_to_wordtab(char *str)
{
	char	**tab;
	int		pos;
	int		nb_word;
	int		len;

	len = strlen(str);
	nb_word = 0;
	pos = 0;
	while (pos < len)
	{
		while (str[pos] == ' ' || str[pos] == '\t')
			++pos;
		if (str[pos])
			nb_word ++;
		while (str[pos] && str[pos] != ' ' && str[pos] != '\t')
			++pos;
	}
	tab = (char **) malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return ((char **) 0);
	return (_mlx_int_str_to_wordtab(str, len, tab));
}
