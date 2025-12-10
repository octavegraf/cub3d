/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:13:42 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/09 16:40:41 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "cub3d.h"

void	minimap_free(char ***minimap, int n, int radius_map)
{
	int	i;

	i = 0;
	while (i < (radius_map * 2) + 1 && i < n)
	{
		free((*minimap)[i]);
		(*minimap)[i] = NULL;
		i++;
	}
	free(*minimap);
	*minimap = NULL;
}
#endif
