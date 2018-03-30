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

//TODO: ft_strsplit review

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	int		updates;

	updates = update_map(map);
	if (updates == FAILURE_CODE)
		return (FAILURE_CODE);
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);

	// coordinates = place_piece(map, piece); //TODO: implement it
	// ft_printf("%d %d\n", coordinates[0], coordinates[1]);
	free_piece(&piece);
	free(coordinates);
	return (1);
}

int			main(void)
{
	t_map	*map;
	int		progress;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (FAILURE_CODE);
	if (set_sides(map) || set_default_field(map))
	{
		free_map(&map);
		return (FAILURE_CODE);
	}
	progress = 1;
	while (progress > 0)
	{
		progress = execute_algorithm(map);
		//visualise_map(map);
	}
	free_map(&map);
	return (progress > -1 ? 1 : FAILURE_CODE);
}
