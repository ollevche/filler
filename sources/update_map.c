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

#include <fcntl.h>
static void	put_field(char **field)
{
	int		i;
	int		fd;

	fd = open("debug", O_RDWR | O_APPEND);
	i = 0;
	while (field[i])
	{
		ft_putstr_fd(field[i], fd);
		write(fd, "\n", 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

static char	**read_field(t_map *map)
{
	char		**field;
	char		*line;
	int			i;
	static int	skipping = 1;

	if (skip_lines(skipping) == FAILURE_CODE)
		return (NULL);
	skipping = 2;
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
	put_field(field); //DEL
	return (field);
}

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
			else if (map->field[i][j] != ALLY_ID)
				map->field[i][j] = ENEMY_ID;
			j++;
		}
		i++;
	}
	return (1);
}

int			update_map(t_map *map)
{
	char	**latest;
	int		updates;
	int		i;
	int		j;

	latest = read_field(map);
	if (!latest)
		return (FAILURE_CODE);
	updates = 0;
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			if (latest[i][j] == map->enemy && map->field[i][j] > 0)
				updates += set_enemy_cell(map, i, j);
			else if (latest[i][j] == map->ally)
				map->field[i][j] = ALLY_ID;
			j++;
		}
		i++;
	}
	return (updates);
}
