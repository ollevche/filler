
void	put_map(t_map *map)
{
	int		i;
	int		j;
	char	*str;
	int		fd;

	fd = open("debug", O_RDWR | O_APPEND);
	i = 0;
	while (i < map->length)
	{
		j = 0;
		while (j < map->width)
		{
			str = ft_itoa(map->field[i][j]);
			write(fd, str, ft_strlen(str));
			write(fd, "\t", 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

void	put_piece(t_piece *piece)
{
	int		i;
	int		j;
	char	*str;
	int		fd;

	fd = open("debug", O_RDWR | O_APPEND);
	i = 0;
	while (i < piece->length)
	{
		j = 0;
		while (j < piece->width)
		{
			str = ft_itoa(piece->field[i][j]);
			write(fd, str, ft_strlen(str));
			write(fd, "\t", 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

void	put_field(char **field)
{
	int		i;
	int		fd;

	fd = open("debug", O_RDWR | O_APPEND);
	i = 0;
	while (field[i])
	{
		ft_putstr_fd(field[i], fd);
		write(fd, "\n", 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}
