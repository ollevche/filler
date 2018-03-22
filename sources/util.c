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

	get_next_line(0, &input); //error can be here
	props = ft_strsplit(input, ' '); //error can be here
	free(input);
	if (length)
		*length = ft_atoi(props[1]); //error can be here
	if (width)
		*width = ft_atoi(props[2]); //error can be here
	ft_free_strarr(&props);
	return (1); // 0 - error
}

void	free_map(t_map **map)
{
	int i;

	i = 0;
	while (i < (*map)->length)
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
	while (i < (*piece)->length)
	{
		free((*piece)->field[i]);
		i++;
	}
	free((*piece)->field);
	free(*piece);
	*piece = NULL;
}