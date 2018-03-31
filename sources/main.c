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

// #include <fcntl.h>
// static void	put_map(t_map *map)
// {
// 	int		i;
// 	int		j;
// 	char	*str;
// 	int		fd;

// 	fd = open("debug", O_RDWR | O_APPEND);
// 	i = 0;
// 	while (i < map->length)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			str = ft_itoa(map->field[i][j]);
// 			write(fd, str, ft_strlen(str));
// 			write(fd, "\t", 1);
// 			j++;
// 		}
// 		write(fd, "\n", 1);
// 		i++;
// 	}
// 	write(fd, "\n", 1);
// 	close(fd);
// }

// static void	put_piece(t_piece *piece)
// {
// 	int		i;
// 	int		j;
// 	char	*str;
// 	int		fd;

// 	fd = open("debug", O_RDWR | O_APPEND);
// 	i = 0;
// 	while (i < piece->length)
// 	{
// 		j = 0;
// 		while (j < piece->width)
// 		{
// 			str = ft_itoa(piece->field[i][j]);
// 			write(fd, str, ft_strlen(str));
// 			write(fd, "\t", 1);
// 			j++;
// 		}
// 		write(fd, "\n", 1);
// 		i++;
// 	}
// 	write(fd, "\n", 1);
// 	close(fd);
// }

int			execute_algorithm(t_map *map)
{
	t_piece *piece;
	t_pos	*position;
	int		updates;

	updates = update_map(map);
	if (updates == FAILURE_CODE)
		return (FAILURE_CODE);
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	position = place_piece(map, piece);
	if (position)
		ft_printf("%d %d\n", position->length, position->width);
	free_piece(&piece);
	if (!position)
		return (FAILURE_CODE);
	free(position);
	map->iteration++;
	return (1);
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
