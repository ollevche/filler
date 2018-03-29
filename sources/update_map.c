/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 12:19:16 by ollevche          #+#    #+#             */
/*   Updated: 2018/03/21 12:19:17 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ollevche_filler.h"

static int	set_enemy_cell(t_map *map, int enemy_i, int enemy_j)
{
	int i;
	int j;

	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->field[i][j] > 0 && (i != enemy_i || j != enemy_j))
			{
				map->field[i][j] += (enemy_i - i) * (enemy_i > i ? 1 : -1);
				map->field[i][j] += (enemy_j - j) * (enemy_j > j ? 1 : -1);
			}
			else if (map->field[i][j] != 0)
				map->field[i][j] = -1;
			j++;
		}
		i++;
	}
	return (1);
}

static char	**read_field(t_map *map)
{
	char	**field;
	char	*line;
	int		i;

	if (get_next_line(0, &line) == -1) // potential leak
		return (NULL);
	free(line);
	field = (char**)malloc(sizeof(char*) * map->length);
	if (!field)
		return (NULL);
	i = 0;
	while (i < map->length)
	{
		if (get_next_line(0, &line) == -1)
		{
			field[i] = 0;
			return (NULL);
		}
		field[i] = ft_strsub(line, 4, map->width);
		free(line);
		if (!field[i])
			return (NULL);
		i++;
	}
	return (field);
}

int			compare_cells(t_map *map, char **latest, int i, int j)
{
	int result;

	result = 0;
	if (latest[i][j] == map->enemy && map->field[i][j] > 0)
		result = set_enemy_cell(map, i, j);
	else if (latest[i][j] == map->me)
		map->field[i][j] = 0;
	return (result);
}

int			update_map(t_map *map)
{
	char	**latest;
	int		updates;
	int		i;
	int		j;

	if (!(latest = read_field(map)))
	{
		ft_free_strarr(&latest);
		return (FAILURE_CODE);
	}
	updates = 0;
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			updates += compare_cells(map, latest, i, j);
			j++;
		}
		i++;
	}
	return (updates);
}
