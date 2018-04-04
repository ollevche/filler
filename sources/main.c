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

#include <fcntl.h>
static void	put_map(t_map *map)
{
	int		i;
	int		j;
	char	*str;
	int		fd;

	fd = open("debug", O_RDWR | O_APPEND);
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			str = ft_itoa(map->field[i][j]);
			write(fd, str, ft_strlen(str));
			write(fd, "\t", 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

static void	put_piece(t_piece *piece)
{
	int		i;
	int		j;
	char	*str;
	int		fd;

	fd = open("debug", O_RDWR | O_APPEND);
	i = 0;
	while (i < piece->length)
	{
		j = 0;
		while (j < piece->width)
		{
			str = ft_itoa(piece->field[i][j]);
			write(fd, str, ft_strlen(str));
			write(fd, "\t", 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

static void	clear(void)
{
	int fd;

	fd = open("debug", O_RDWR | O_TRUNC);
	close(fd);
}

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	t_pos	*position;
	int		updates;
	int		iter_result;

	updates = update_map(map);
	if (updates == FAILURE_CODE)
		return (FAILURE_CODE);
	put_map(map);//DEL
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	put_piece(piece);//DEL
	position = place_piece(map, piece);
	free_piece(&piece);
	if (!position)
		return (FAILURE_CODE);
	ft_printf("%d %d\n", position->length, position->width);
	iter_result = 1;
	if (position->length < 0 && position->width < 0)
		iter_result = 0;
	free(position);
	map->iteration++;
	return (updates || iter_result);
}

int			main(void)
{
	t_map	*map;
	int		iter_result;

	clear(); //DEL
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
		iter_result = execute_algorithm(map);
	free_map(&map);
	return (iter_result > -1 ? 1 : FAILURE_CODE);
}
