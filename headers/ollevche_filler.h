/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ollevche_filler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 12:18:01 by ollevche          #+#    #+#             */
/*   Updated: 2018/03/21 12:18:02 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OLLEVCHE_FILLER_H
# define OLLEVCHE_FILLER_H

# include "libftprintf.h"

# define CHECK_FOR_NULL (X) (if (!X) return (NULL);) //is it useful?

/*
**	0 < map->field[x][y] >> it's an empty cell
**	map->field[x][y] == 0 >> it's a friendly cell
**	map->field[x][[y] == -1 >> it's an enemy cell
*/

typedef struct	s_map
{
	int	**field;
	int	length;
	int	width;
	int	enemy;
	int	me;
}				t_map;

typedef struct	s_piece
{
	int	**field;
	int	length;
	int	width;
}				t_piece;

/*
**	main.c
*/

void			set_sides(t_map *map);
void			set_default_field(t_map *map);

/*
**	update_map.c
*/

void			update_map(t_map *map);

/*
**	get_piece.c
*/

t_piece			*get_piece(void);

/*
**	util.c
*/

int				get_size(int *length, int *width);
void			free_map(t_map **map);
void			free_piece(t_piece **map);

#endif
