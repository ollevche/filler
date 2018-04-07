/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_n_place.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:57:16 by ollevche          #+#    #+#             */
/*   Updated: 2018/04/03 12:57:16 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ollevche_filler.h"

/*
**	get_piece()
*/

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

/*
**	place_piece()
*/

static int	calc_sum(t_map *map, t_piece *piece, int mi, int mj)
{
	int	ally_col;
	int	sum;
	int	pi;
	int	pj;

	ally_col = 0;
	sum = 0;
	pi = 0;
	while (pi < piece->length)
	{
		pj = 0;
		while (pj < piece->width)
		{
			if (piece->field[pi][pj])
			{
				ally_col += map->field[mi + pi][mj + pj] == ALLY_ID;
				if (map->field[mi + pi][mj + pj] == ENEMY_ID || ally_col > 1)
					return (INT_MAX);
				sum += map->field[mi + pi][mj + pj];
			}
			pj++;
		}
		pi++;
	}
	return (ally_col ? sum : INT_MAX);
}

int			place_piece(t_map *map, t_piece *piece, int *x, int *y)
{
	int		i;
	int		j;
	int		cur_sum;
	int		best_sum;

	best_sum = INT_MAX;
	i = 0;
	while (i <= map->length - piece->length)
	{
		j = 0;
		while (j <= map->width - piece->width)
		{
			cur_sum = calc_sum(map, piece, i, j);
			if (cur_sum < best_sum)
			{
				*x = i;
				*y = j;
				best_sum = cur_sum;
			}
			j++;
		}
		i++;
	}
	return (best_sum != INT_MAX);
}
