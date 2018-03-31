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
// TODO: fix segfault (or it's not a segfault?)

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	t_pos	*position;
	int		updates;
	int		iter_result;

	updates = update_map(map);
	if (updates == FAILURE_CODE)
		return (FAILURE_CODE);
	// write(2, "updated map\n", 12); // DEL
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	// write(2, "got piece\n", 10); // DEL
	position = place_piece(map, piece);
	free_piece(&piece);
	if (!position)
		return (FAILURE_CODE);
	// write(2, "placed piece\n", 13); // DEL
	ft_printf("%d %d\n", position->length, position->width);
	// write(2, "printed position\n", 17); // DEL
	iter_result = 1;
	if (position->length < 0 && position->width < 0)
		iter_result = 0;
	free(position);
	map->iteration++;
	// if (updates || iter_result) // DEL
		// write(2, "result: OK\n", 11); // DEL
	// else // DEL
		// write(2, "result: NOT OK\n", 15); // DEL
	return (updates || iter_result);
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
