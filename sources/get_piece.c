/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 12:07:06 by ollevche          #+#    #+#             */
/*   Updated: 2018/03/22 12:07:06 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ollevche_filler.h"

static char		**read_strarr(int length)
{
	char	**strarr;
	int		i;

	strarr = (char**)malloc(sizeof(char*) * (length + 1)); //error can be here
	i = 0;
	while (i < length)
	{
		get_next_line(0, &(strarr[i])); //error can be here
		i++;
	}
	strarr[length] = NULL;
	return (strarr);
}

static t_piece	*convert_to_piece(char **strarr)
{
	t_piece	*piece;
	int		i;
	int		j;

	piece = (t_piece*)malloc(sizeof(t_piece)); //error can be here
	piece->width = ft_strlen(strarr[0]);
	i = 0;
	while (strarr[i++]);
	piece->length = i - 1;
	piece->field = (int**)malloc(sizeof(int*) * i); //error can be here
	i = 0;
	while (i < piece->length)
	{
		piece->field[i] = (int*)malloc(sizeof(int) * piece->width); //error can be here
		j = 0;
		while (j < piece->width)
		{
			if (strarr[i][j] == '.')
				piece->field[i][j] = 0;
			else
				piece->field[i][j] = 1;
			j++;
		}
		i++;
	}
	return (piece);
}

t_piece			*get_piece(void)
{
	t_piece	*piece;
	char	**strarr;
	int		length;
	char	**cut_strarr;

	get_size(&length, NULL);  //error can be here
	strarr = read_strarr(length);  //error can be here
	cut_strarr = ft_strarr_trim(strarr, '*');  //error can be here
	ft_free_strarr(&strarr);
	piece = convert_to_piece(cut_strarr);  //error can be here
	ft_free_strarr(&cut_strarr);
	return (piece);
}