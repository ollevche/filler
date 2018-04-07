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
# include <limits.h>

# define FAILURE_CODE -1
# define ENEMY_ID 0
# define ALLY_ID -1
# define INITIAL_ID -2

typedef struct	s_map
{
	int	**field;
	int	length;
	int	width;
	int	enemy;
	int	ally;
	int	iteration;
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

int				get_size(int *length, int *width);

/*
**	execute.c
*/

int				execute_algorithm(t_map *map);
void			free_piece(t_piece **piece);
int				skip_lines(int amount); //move it

/*
**	get_n_place.c
*/

t_piece			*get_piece(void);
int				place_piece(t_map *map, t_piece *piece, int *x, int *y);

/*
**	update_map.c
*/

int				update_map(t_map *map);

#endif
