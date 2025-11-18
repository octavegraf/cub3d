/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:41:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/18 16:29:20 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_game *game, int argc, char **argv)
{
	if (argc < 2)
		return (ft_dprintf(2, "Error\nUse program with one map.\n"), 1);
	read_map(argv[1]);
}

int	readable_file(char *file_path)
{
	int	fd;

	if (!file_path || !*file_path)
		return (ft_dprintf (2, "Error\n null path\n"), 1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf (2, "Error\n open file\n"), 1);
	return (fd);
}

int	identify(char *line, t_game *game)
{
	int size;
	
	size = ft_wstrlen(line);
	if (!size)
		return (0);
	if ()
}

int	read_map(char *map_path, t_game *game)
{
	int	fd;
	int	i;

	fd = readable_file(map_path);
	if (fd == -1)
		return (1);
	get_next_line(fd)
}
