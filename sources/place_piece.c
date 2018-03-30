
#include "ollevche_filler.h"

static t_pos	*new_position(void)
{
	t_pos	*position;

	position = (t_pos*)malloc(sizeof(t_pos));
	if (!position)
		return (NULL);
	position->sum = -1;
	position->length = -1;
	position->width = -1;
	return (position);
}

static int		get_sum(t_map *map, t_piece *piece, int mi, int mj)
{
	int	ally_col;
	int	sum;
	int	pi;
	int	pj;

	ally_col = 0;
	sum = 0;
	pi = 0;
	while (pi < piece->length && pi + mi < map->length)
	{
		pj = 0;
		while (pj < piece->width && pj + mj < map->width)
		{
			if (piece->field[pi][pj])
			{
				if (map->field[mi + pi][mj + pj] == ALLY_ID)
					ally_col++;
				else if (map->field[mi + pi][mj + pj] == ALLY_ID)
					return (-1);
				else
					sum += map->field[mi + pi][mj + pj];
			}
			pj++;
		}
		pi++;
	}
	if (ally_col != 1 || pi != piece->length || pj != piece->width) //it wouldn't works with empty cells outside of map borders
		return (-1);
	else
		return (sum);
}

t_pos			*place_piece(t_map *map, t_piece *piece)
{
	t_pos	*position;
	int		i;
	int		j;
	int		cur_sum;

	if (!(position = new_position()))
		return (NULL);
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			cur_sum = get_sum(map, piece, i, j);
			if (cur_sum > position->sum)
			{
				position->length = i;
				position->width = j;
				position->sum = cur_sum;
			}
			j++;
		}
		i++;
	}
	return (position);
}