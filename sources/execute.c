
#include "ollevche_filler.h"

static void		set_field(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			map->field[i][j] = INITIAL_ID;
			j++;
		}
		i++;
	}
}

int				execute_algorithm(t_map *map)
{
	t_piece *piece;
	t_pos	*position;
	int		is_placed;

	set_field(map);
	if (map->iteration && skip_lines(1) == FAILURE_CODE)
		return (FAILURE_CODE);
	if (update_map(map) == FAILURE_CODE)
		return (FAILURE_CODE);
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	position = place_piece(map, piece);
	free_piece(&piece);
	if (!position)
		return (FAILURE_CODE);
	ft_printf("%d %d\n", position->length, position->width);
	is_placed = 1;
	if (position->length < 0 || position->width < 0)
		is_placed = 0;
	free(position);
	map->iteration++;
	return (is_placed);
}

void	free_piece(t_piece **piece)
{
	int i;

	i = 0;
	while ((*piece)->field[i] && i < (*piece)->length)
	{
		free((*piece)->field[i]);
		i++;
	}
	free((*piece)->field);
	free(*piece);
	*piece = NULL;
}

int		skip_lines(int amount)
{
	int		i;
	char	*line;

	i = 0;
	while (i < amount)
	{
		line = safe_gnl(0);
		if (!line)
			return (FAILURE_CODE);
		free(line);
		i++;
	}
	return (1);
}
