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

static void	set_enemy_cell(t_map *map, int enemy_i, int enemy_j)
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
}

static char	**read_field(t_map *map)
{
	char	**field;
	char	*line;
	int		i;

	get_next_line(0, &line);
	free(line);
	field = (char**)malloc(sizeof(char*) * map->length); //error can be here
	i = 0;
	while (i < map->length)
	{
		get_next_line(0, &line); //error can be here
		field[i] = ft_strsub(line, 4, map->width); //error can be here
		free(line);
		i++;
	}
	return (field);
}

void		update_map(t_map *map)
{
	char	**latest;
	int		i;
	int		j;

	latest = read_field(map); //error can be here
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			if (latest[i][j] == map->enemy &&
				map->field[i][j] > 0)
				set_enemy_cell(map, i, j);
			else if (latest[i][j] == map->me)
				map->field[i][j] = 0;
			j++;
		}
		i++;
	}
	ft_free_strarr(&latest);
}
