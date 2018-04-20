/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:13:26 by ollevche          #+#    #+#             */
/*   Updated: 2018/04/07 17:13:26 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ollevche_filler.h"

static void	set_field(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			map->field[i][j] = INITIAL_ID;
			j++;
		}
		i++;
	}
}

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	int		is_placed;
	int		r_len;
	int		r_wid;

	set_field(map);
	if (map->iteration && skip_lines(0, 1) == FAILURE_CODE)
		return (FAILURE_CODE);
	if (update_map(map) == FAILURE_CODE)
		return (FAILURE_CODE);
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	r_len = -1;
	r_wid = -1;
	is_placed = place_piece(map, piece, &r_len, &r_wid);
	free_piece(&piece);
	ft_printf("%d %d\n", r_len, r_wid);
	map->iteration++;
	return (is_placed);
}

void		free_piece(t_piece **piece)
{
	int i;

	i = 0;
	while ((*piece)->field[i] && i < (*piece)->length)
	{
		free((*piece)->field[i]);
		i++;
	}
	free((*piece)->field);
	free(*piece);
	*piece = NULL;
}
