
#include "ollevche_filler.h"

int			set_sides(t_map *map)
{
	char	*player_exec;
	int		is_p1;

	if (!(player_exec = safe_gnl(0)))
		return (FAILURE_CODE);
	is_p1 = ft_strstr(player_exec, "p1") ? 1 : 0;
	map->ally = is_p1 ? 'o' : 'x';
	map->enemy = is_p1 ? 'x' : 'o';
	free(player_exec);
	return (1);
}

static int	*get_line(int width)
{
	int *line;
	int	i;

	line = (int*)malloc(sizeof(int) * width);
	if (!line)
		return (NULL);
	i = 0;
	while (i < width)
	{
		line[i] = 1;
		i++;
	}
	return (line);
}

int			set_default_field(t_map *map)
{
	int		i;
	int		get_size_rv;

	get_size_rv = get_size(&(map->length), &(map->width));
	if (get_size_rv == FAILURE_CODE || !map->length || !map->width)
		return (FAILURE_CODE);
	map->field = (int**)malloc(sizeof(int*) * map->length);
	if (!map->field)
		return (FAILURE_CODE);
	i = 0;
	while (i < map->length)
	{
		map->field[i] = get_line(map->width);
		if (!map->field[i])
			return (FAILURE_CODE);
		i++;
	}
	return (1);
}