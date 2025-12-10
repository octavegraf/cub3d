/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:01:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/10 14:20:51 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_jump(double jump)
{
	if (jump > 1 || jump < -1)
		return (0);
	return (1);
}

int	is_available(char **map, int i, int j)
{
	if (map[i][j] == '0')
		return (1);
	return (0);
}
