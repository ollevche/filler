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

static int	get_sum(t_map *map, t_piece *piece, int mi, int mj)
{
	int	ally_col;
	int	sum;
	int	pi;
	int	pj;

	ally_col = 0;
	sum = 0;
	pi = -1;
	while (++pi < piece->length && pi + mi < map->length)
	{
		pj = -1;
		while (++pj < piece->width && pj + mj < map->width)
			if (piece->field[pi][pj])
			{
				if (map->field[mi + pi][mj + pj] == ALLY_ID)
					ally_col++;
				else if (map->field[mi + pi][mj + pj] == ENEMY_ID)
					return (INT_MAX);
				else
					sum += map->field[mi + pi][mj + pj];
			}
	}
	pi -= piece->length;
	pj -= piece->width;
	return (ally_col == 1 && !(pi + pj) ? sum : INT_MAX);
}

t_pos		*place_piece(t_map *map, t_piece *piece)
{
	t_pos	*position;
	int		i;
	int		j;
	int		cur_sum;

	if (!(position = new_position()))
		return (NULL);
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			cur_sum = get_sum(map, piece, i, j);
			if (cur_sum < position->sum)
			{
				position->length = i;
				position->width = j;
				position->sum = cur_sum;
			}
			j++;
		}
		i++;
	}
	return (position);
}
