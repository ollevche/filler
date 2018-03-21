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

static void	set_sides(t_map *map)
{
	char	*player_exec;

	get_next_line(0, &player_exec); //error can be here
	if (ft_strstr(player_exec, "p1"))
	{
		map->me = 'O';
		map->enemy = 'X';
	}
	else
	{
		map->me = 'X';
		map->enemy = 'O';
	}
	free(player_exec);
}

static int	*get_line(int width)
{
	int *line;
	int	i;

	line = (int*)malloc(sizeof(int) * (width + 1)); //error can be here
	i = 0;
	while (i < width)
	{
		line[i] = 1;
		i++;
	}
	line[i] = -3;
	return (line);
}

//move it to libft
static void	free_strarr(char **arr)
{
	int i;

	i = 0;
	while (*(arr + i))
	{
		free(*(arr + i));
		i++;
	}
	free(arr);
}

static void	set_default_field(t_map *map)
{
	char	*input;
	char	**props;
	int		i;

	get_next_line(0, &input); //error can be here
	props = ft_strsplit(input, ' '); //error can be here
	free(input);
	map->length = ft_atoi(props[1]); //error can be here
	map->width = ft_atoi(props[2]); //error can be here
	free_strarr(props);
	map->field = (int**)malloc(sizeof(int*) * map->length); //error can be here
	i = 0;
	while (i < map->length)
	{
		map->field[i] = get_line(map->width); //error can be here
		i++;
	}
}

// static void	put_map(t_map *map)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	while (i < map->length)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			str = ft_itoa(map->field[i][j]);
// 			write(2, str, ft_strlen(str));
// 			write(2, "\t", 1);
// 			j++;
// 		}
// 		write(2, "\n", 1);
// 		i++;
// 	}
// }

int			main(void)
{
	t_map	*map;
	// int		**piece;
	// int		*coordinates;

	map = (t_map*)malloc(sizeof(t_map)); //error can be here
	set_sides(map); //error can be here
	set_default_field(map); //error can be here
	while (1) // free_map();
	{
		update_map(map);
		piece = get_piece(); //TODO: implement it
		// coordinates = place_piece(map, piece); //TODO: implement it
		// ft_printf("%d %d\n", coordinates[0], coordinates[1]);
		// free(piece);
		// free(coordinates);
		// //visualise_map(main_map);
	}
	return (0);
}
