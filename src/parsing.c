/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:41:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/19 14:56:44 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_game *game, int argc, char **argv)
{
	if (argc < 2)
		return (ft_dprintf(2, "Error\nUse program with one map.\n"), 1);
	read_cub_file(argv[1], game);
}

int	readable_file(char *file_path)
{
	int	fd;

	if (!file_path || !*file_path)
		return (ft_dprintf (2, "Error\n null path\n"), 1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf (2, "Error\n open file: %s \n", file_path), 1);
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
		if (!wstrlen(buff))
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
	return (read_cub_file2(cub_path, game, fd));
}

int	read_cub_file(char *cub_path, t_game *game, int fd)
{
	char	*buff;
	char	**map;

	map = ft_calloc(1, sizeof(char *));
	buff = NULL;
	while (!wstrlen(buff) == 0)
	{
		if (buff)
			free(buff);
		buff = get_next_line(fd);
	}
	while (wstrlen(buff))
	{
		map = ft_array_add_row(&map, buff);
		if (!map)
			return (free(buff), close(fd), 1);
		free(buff);
		buff = get_next_line(fd);
	}
	free(buff);
	return (close(fd), identify_map(map, game));
}
