/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:41:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/25 15:05:55 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_cub_file2(t_game *game, int fd);
static int	read_cub_file3(t_game *game, char *buff, int fd);

int	readable_file(char *file_path)
{
	int	fd;

	fd = -1;
	if (!file_path || !*file_path)
		return (ft_dprintf (2, ERR_NULL_PATH), fd);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf (2, ERR_OPEN_FILE, file_path), fd);
	if (read(fd, NULL, 0) < 0)
		return (ft_dprintf(2, ERR_OPEN_FILE, file_path), close(fd), -1);
	return (fd);
}

int	read_cub_file(char *cub_path, t_game *game)
{
	int		fd;
	int		lines_read;
	char	*buff;

	if (ft_strncmp(cub_path + ft_strlen(cub_path) - 4, ".cub", 4))
		return (ft_dprintf(2, ERR_CUB_EXTENSION), 1);
	fd = readable_file(cub_path);
	if (fd == -1)
		return (1);
	lines_read = -1;
	while (++lines_read < 6)
	{
		buff = get_next_line(fd);
		if (!buff)
			return (close(fd), ft_dprintf(2, ERR_WRONG_LINE), 1);
		if (!ft_wstrlen(buff) && lines_read--)
		{
			free(buff);
			continue ;
		}
		if (identify(buff, game))
			return (free(buff), close(fd), 1);
		free(buff);
	}
	return (read_cub_file2(game, fd));
}

static int	read_cub_file2(t_game *game, int fd)
{
	char	*buff;

	buff = get_next_line(fd);
	while (buff && !ft_wstrlen(buff))
	{
		free(buff);
		buff = get_next_line(fd);
	}
	if (!buff)
		return (close(fd), ft_dprintf(2, ERR_WRONG_LINE), 1);
	return (read_cub_file3(game, buff, fd));
}

static int	read_cub_file3(t_game *game, char *buff, int fd)
{
	char	**map;
	char	*temp;

	map = NULL;
	while (ft_wstrlen(buff))
	{
		if (buff[ft_strlen(buff) - 1] == '\n')
		{
			temp = ft_substr(buff, 0, ft_strlen(buff) - 1);
			if (!temp)
				return (double_free(map), free(buff), close(fd), 1);
			free(buff);
			buff = temp;
		}
		map = ft_array_add_row(map, buff);
		if (!map)
			return (free(buff), close(fd), 1);
		free(buff);
		buff = get_next_line(fd);
	}
	return (free(buff), close(fd), identify_map(map, game));
}
