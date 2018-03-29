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

//TODO: error handling
//TODO: ft_strsplit review
//TODO: check every malloc() for size

int			set_sides(t_map *map)
{
	char	*player_exec;
	int		is_p1;

	if (get_next_line(0, &player_exec) == -1)
		return (FAILURE_CODE);
	is_p1 = ft_strstr(player_exec, "p1");
	map->me = is_p1 ? 'O' : 'X';
	map->enemy = is_p1 ? 'X' : 'O';
	free(player_exec);
	return (0);
}

static int	*get_line(int width)
{
	int *line;
	int	i;

	line = (int*)malloc(sizeof(int) * (width + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < width)
	{
		line[i] = 1;
		i++;
	}
	line[i] = -3;
	return (line);
}

int			set_default_field(t_map *map)
{
	int		i;

	if (get_size(&(map->length), &(map->width)) == FAILURE_CODE)
		return (FAILURE_CODE);
	map->field = (int**)malloc(sizeof(int*) * map->length);
	if (!map->field)
		return (FAILURE_CODE);
	i = 0;
	while (i < map->length)
	{
		map->field[i] = get_line(map->width);
		if (!map->field[i])
			return (FAILURE_CODE);
		i++;
	}
	return (0);
}

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	int		updates;

	updates = update_map(map);
	// piece = get_piece();
	// coordinates = place_piece(map, piece); //TODO: implement it
	// ft_printf("%d %d\n", coordinates[0], coordinates[1]);
	free_piece(&piece);
	free(coordinates);
	return (1);
}

int			main(void)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (FAILURE_CODE);
	if (set_sides(map) || set_default_field(map))
	{
		free_map(&map);
		return (FAILURE_CODE);
	}
	while (1) // free_map(&map);
	{
		execute_algorithm(map);
		// visualise_map(map);
	}
	return (0);
}
