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

static int	set_field(t_map *map)
{
	int	i;
	int	j;

	if (get_size(&(map->length), &(map->width)) == FAILURE_CODE)
		return (FAILURE_CODE);
	if (map->iteration == 0)
		map->field = (int**)malloc(sizeof(int*) * map->length);
	if (!map->field)
		return (FAILURE_CODE);
	i = 0;
	while (i < map->length)
	{
		if (map->iteration == 0)
			map->field[i] = (int*)malloc(sizeof(int) * map->width);
		if (!map->field[i])
			return (FAILURE_CODE);
		j = 0;
		while (j < map->width)
		{
			map->field[i][j] = INITIAL_ID;
			j++;
		}
		i++;
	}
	return (1);
}

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	t_pos	*position;
	int		is_placed;

	if (set_field(map) == FAILURE_CODE)
		return (FAILURE_CODE);
	if (update_map(map) == FAILURE_CODE)
		return (FAILURE_CODE);
	put_map(map);
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	position = place_piece(map, piece);
	free_piece(&piece);
	if (!position)
		return (FAILURE_CODE);
	ft_printf("%d %d\n", position->length, position->width);
	is_placed = 1;
	if (position->length < 0 || position->width < 0)
		is_placed = 0;
	free(position);
	map->iteration++;
	return (is_placed);
}

static int	set_sides(t_map *map)
{
	char	*player_exec;
	int		is_p1;

	player_exec = safe_gnl(0);
	if (!player_exec)
		return (FAILURE_CODE);
	is_p1 = ft_strstr(player_exec, "p1") ? 1 : 0;
	map->ally = is_p1 ? 'o' : 'x';
	map->enemy = is_p1 ? 'x' : 'o';
	free(player_exec);
	return (1);
}

int			main(void)
{
	t_map	*map;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (FAILURE_CODE);
	if (set_sides(map) == FAILURE_CODE)
	{
		free_map(&map);
		return (FAILURE_CODE);
	}
	map->iteration = 0;
	while (execute_algorithm(map) > 0);
	free_map(&map);
	return (1);
}
