
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
	int		is_placed;
	int		x;
	int		y;

	set_field(map);
	if (map->iteration && skip_lines(1) == FAILURE_CODE)
		return (FAILURE_CODE);
	if (update_map(map) == FAILURE_CODE)
		return (FAILURE_CODE);
	piece = get_piece();
	if (!piece)
		return (FAILURE_CODE);
	*x = -1;
	*y = -1;
	is_placed = place_piece(map, piece, &x, &y);
	free_piece(&piece);
	ft_printf("%d %d\n", x, y);
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
