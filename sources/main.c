
#include "ollevche_filler.h"

#define INPUT 1

//TODO: error handling
//TODO: ft_strsplit review

static int	get_player_id(void)
{
	char	*player_exec;
	int		id;

	get_next_line(INPUT, &player_exec); //error can be here
	if (ft_strstr(player_exec, "p1"))
		id = 1;
	else
		id = 2;
	free(player_exec);
	return (id);
}

static int	*get_line(int width)
{
	int *line;
	int	i;

	line = (int*)malloc(sizeof(int) * width); //error can be here
	i = 0;
	while (i < width)
	{
		line[i] = 1;
		i++;
	}
	return (line);
}

static int	**get_default_map(int *width)
{
	int		**map;
	char	*input;
	char	**props;
	int		length;

	get_next_line(INPUT, &input); //error can be here
	props = ft_strsplit(input, ' '); //error can be here
	length = ft_atoi(props[1]); //error can be here
	*width = ft_atoi(props[2]); //error can be here
	map = (int**)malloc(sizeof(int*) * (length + 1)) //error can be here
	map[length] = NULL;
	while (lentgh > -1)
	{
		length--;
		map[length] = get_line(*width); //error can be here
	}
	return (map);
}

int 		main(void)
{
	int		player_id;
	int		**main_map;
	int		**piece;
	int		coordinates[2];

	player_id = get_player_id(); //error can be here
	main_map = get_default_map(&map_width); //error can be here
	while (1)
	{
		update_map(main_map, player_id); //TODO: implement it
		piece = get_piece(); //TODO: implement it
		coordinates = place_piece(main_map, player_id, piece); //TODO: implement it
		ft_printf("%d %d\n", coordinates[0], coordinates[1]);
		free(piece);
		//visualise_map(main_map);
	}
	return (0);
}
