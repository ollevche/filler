/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 12:17:51 by ollevche          #+#    #+#             */
/*   Updated: 2018/03/21 12:17:52 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ollevche_filler.h"

// TODO: ft_strsplit review
// TODO: fix segfault

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	t_pos	*position;
	int		updates;

	updates = update_map(map);
	if (updates == FAILURE_CODE)
		return (FAILURE_CODE);
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	position = place_piece(map, piece);
	if (position)
		ft_printf("%d %d\n", position->length, position->width);
	free_piece(&piece);
	if (!position)
		return (FAILURE_CODE);
	free(position);
	map->iteration++;
	return (1);
}

int			main(void)
{
	t_map	*map;
	int		iter_result;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (FAILURE_CODE);
	if (set_sides(map) == FAILURE_CODE ||
		set_default_field(map) == FAILURE_CODE)
	{
		free_map(&map);
		return (FAILURE_CODE);
	}
	map->iteration = 1;
	iter_result = 1;
	while (iter_result > 0)
	{
		iter_result = execute_algorithm(map);
		//visualise_map(map);
	}
	free_map(&map);
	return (iter_result > -1 ? 1 : FAILURE_CODE);
}
