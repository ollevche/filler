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

# define FAILURE_CODE -1
# define ENEMY_ID 0
# define ALLY_ID -1

typedef struct	s_map
{
	int	**field;
	int	length;
	int	width;
	int	enemy;
	int	ally;
}				t_map;

typedef struct	s_piece
{
	int	**field;
	int	length;
	int	width;
}				t_piece;

typedef struct	s_pos
{
	int	length;
	int	width;
	int	sum;
}				t_pos;

/*
**	main.c
*/

int				execute_algorithm(t_map *map);

/*
**	setters.c
*/

int				set_default_field(t_map *map);
int				set_sides(t_map *map);

/*
**	update_map.c
*/

int				update_map(t_map *map);

/*
**	get_piece.c
*/

t_piece			*get_piece(void);

/*
**	place_piece.c
**/

t_pos			*place_piece(t_map *map, t_piece *piece);

/*
**	util.c
*/

int				get_size(int *length, int *width);
void			free_map(t_map **map);
void			free_piece(t_piece **map);
char			*safe_gnl(int fd);

#endif
