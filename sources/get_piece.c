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

static char	**read_strarr(int length)
{
	char	**strarr;
	int		i;

	strarr = (char**)malloc(sizeof(char*) * (length + 1));
	if (!strarr)
		return (NULL);
	i = 0;
	while (i < length)
	{
		strarr[i] = safe_gnl(0);
		if (!strarr[i])
		{
			ft_free_strarr(&strarr);
			return (NULL);
		}
		i++;
	}
	strarr[length] = NULL;
	return (strarr);
}

static int	convert_to_piece(char **strarr, t_piece *piece)
{
	int		i;
	int		j;

	piece->field = (int**)malloc(sizeof(int*) * piece->length);
	if (!piece->field)
		return (FAILURE_CODE);
	i = 0;
	while (i < piece->length)
	{
		piece->field[i] = (int*)malloc(sizeof(int) * piece->width);
		if (!piece->field[i])
			return (FAILURE_CODE);
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
	return (1);
}

t_piece		*get_piece(void)
{
	int		length;
	char	**strarr;
	t_piece	*piece;

	if (get_size(&length, NULL) == FAILURE_CODE)
		return (NULL);
	strarr = read_strarr(length);
	if (!strarr)
		return (NULL);
	piece = (t_piece*)malloc(sizeof(t_piece));
	if (piece)
	{
		piece->width = ft_strlen(strarr[0]);
		piece->length = length;
		piece->field = NULL;
		if (convert_to_piece(strarr, piece) == FAILURE_CODE)
			free_piece(&piece);
	}
	ft_free_strarr(&strarr);
	return (piece);
}
