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

static char	**read_field(t_map *map)
{
	char		**field;
	char		*line;
	int			i;

	if (skip_lines(0, 1) == FAILURE_CODE)
		return (NULL);
	field = (char**)malloc(sizeof(char*) * (map->length + 1));
	if (!field)
		return (NULL);
	i = 0;
	while (i < map->length)
	{
		line = safe_gnl(0);
		field[i] = ft_strsub(line, 4, map->width);
		field[i] = ft_strtolow(field[i]);
		free(line);
		if (!field[i])
		{
			ft_free_strarr(&field);
			return (NULL);
		}
		i++;
	}
	field[i] = NULL;
	return (field);
}

static void	mark_as(t_map *map, char **latest, int target, int mark)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			if (latest[i][j] == target)
				map->field[i][j] = mark;
			j++;
		}
		i++;
	}
}

static int	update_cell(t_map *map, int i, int j, int new_id)
{
	if (i < 0 || i >= map->length)
		return (0);
	if (j < 0 || j >= map->width)
		return (0);
	if (map->field[i][j] != -2)
		return (0);
	map->field[i][j] = new_id;
	return (1);
}

static int	calculating(t_map *map, int index)
{
	int	updated_cells;
	int	id;
	int	i;
	int	j;

	updated_cells = 0;
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->field[i][j] == index)
			{
				id = map->field[i][j] + 1;
				updated_cells += update_cell(map, i - 1, j, id);
				updated_cells += update_cell(map, i + 1, j, id);
				updated_cells += update_cell(map, i, j - 1, id);
				updated_cells += update_cell(map, i, j + 1, id);
			}
			j++;
		}
		i++;
	}
	return (updated_cells);
}

int			update_map(t_map *map)
{
	char	**latest;
	int		index;

	latest = read_field(map);
	if (!latest)
		return (FAILURE_CODE);
	mark_as(map, latest, map->enemy, ENEMY_ID);
	index = ENEMY_ID;
	while (calculating(map, index))
		index++;
	mark_as(map, latest, map->ally, ALLY_ID);
	ft_free_strarr(&latest);
	return (1);
}
