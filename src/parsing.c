/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:41:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/20 18:06:48 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_cub_file2(t_game *game, int fd);

int	parsing(t_game *game, int argc, char **argv)
{
	if (argc < 2)
		return (ft_dprintf(2, "Error\nUse program with one map.\n"), 1);
	return (read_cub_file(argv[1], game));
}

int	readable_file(char *file_path)
{
	int	fd;

	fd = -1;
	if (!file_path || !*file_path)
		return (ft_dprintf (2, "Error\nnull path\n"), fd);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf (2, "Error\nopen file: %s \n", file_path), fd);
	return (fd);
}

int	read_cub_file(char *cub_path, t_game *game)
{
	int		fd;
	int		lines_read;
	char	*buff;

	fd = readable_file(cub_path);
	if (fd == -1)
		return (1);
	lines_read = 0;
	while (lines_read < 6)
	{
		buff = get_next_line(fd);
		if (!ft_wstrlen(buff))
		{
			free(buff);
			continue ;
		}
		if (identify(buff, game))
			return (free(buff), close(fd), 1);
		else
			lines_read++;
		free(buff);
	}
	return (read_cub_file2(game, fd));
}

static int	read_cub_file2(t_game *game, int fd)
{
	char	*buff;
	char	*trim;
	char	**map;

	map = ft_calloc(1, sizeof(char *));
	buff = NULL;
	while (!ft_wstrlen(buff))
	{
		if (buff)
			free(buff);
		buff = get_next_line(fd);
	}
	while (ft_wstrlen(buff))
	{
		if (buff[ft_strlen(buff) - 1] == '\n')
		{
			trim = ft_substr(buff, 0, ft_strlen(buff) - 1);
			if (!trim)
				return (free(buff), close(fd), 1);
			free(buff);
		}
		else
			trim = buff;
		map = ft_array_add_row(map, trim);
		if (!map)
			return (free(buff), free(trim), close(fd), 1);
		free(buff);
		buff = get_next_line(fd);
	}
	free(buff);
	return (close(fd), identify_map(map, game));
}
