/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 12:09:38 by ollevche          #+#    #+#             */
/*   Updated: 2018/03/22 12:09:39 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ollevche_filler.h"

int		get_size(int *length, int *width)
{
	char	*input;
	char	**props;

	if (!(input = safe_gnl(0)))
		return (FAILURE_CODE);
	props = ft_strsplit(input, ' ');
	free(input);
	if (!props)
		return (FAILURE_CODE);
	if (length)
		*length = ft_atoi(props[1]);
	if (width)
		*width = ft_atoi(props[2]);
	ft_free_strarr(&props);
	return (1);
}

void	free_map(t_map **map)
{
	int i;

	i = 0;
	while ((*map)->field[i] && i < (*map)->length)
	{
		free((*map)->field[i]);
		i++;
	}
	free((*map)->field);
	free(*map);
	*map = NULL;
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

char	*safe_gnl(int fd)
{
	char	*line;
	int		ret_value;

	line = NULL;
	ret_value = get_next_line(fd, &line);
	if (ret_value == -1)
		ft_memdel((void**)&line);
	return (line);
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
