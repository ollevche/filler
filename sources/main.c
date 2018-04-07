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

//TODO: move skip_lines(int fd, int amount) to lib

int		get_size(int *length, int *width)
{
	char	*input;
	char	**props;

	if (!(input = safe_gnl(0)))
		return (FAILURE_CODE);
	props = ft_strsplit(input, ' ');
	free(input);
	if (!props || !*props)
		return (FAILURE_CODE);
	if (length)
		*length = ft_atoi(props[1]);
	if (width)
		*width = ft_atoi(props[2]);
	ft_free_strarr(&props);
	return (1);
}

static int		set_sides(t_map *map)
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

static void		free_map(t_map **map)
{
	int i;

	i = 0;
	while ((*map)->field[i] && i < (*map)->length)
	{
		free((*map)->field[i]);
		i++;
	}
	free((*map)->field);
	free(*map);
	*map = NULL;
}

static int		**new_field(int length, int width)
{
	int	**field;
	int	i;

	field = (int**)malloc(sizeof(int*) * length);
	if (!field)
		return (NULL);
	i = 0;
	while (i < length)
	{
		field[i] = (int*)malloc(sizeof(int) * width);
		if (!field[i])
		{
			while (i > -1)
				free(field[--i]);
			free(field);
			return (NULL);
		}
		i++;
	}
	return (field);
}

int				main(void)
{
	t_map	*map;
	int		set_side;
	int		got_size;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (1);
	set_side = set_sides(map);
	got_size = get_size(&(map->length), &(map->width));
	map->iteration = 0;
	map->field = NULL;
	if (set_side != FAILURE_CODE && got_size != FAILURE_CODE)
		map->field = new_field(map->length, map->width);
	if (map->field)
		while (execute_algorithm(map) > 0);
	free_map(&map);
	return (1);
}
