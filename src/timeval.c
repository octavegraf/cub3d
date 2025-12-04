/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:02:21 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/03 16:21:14 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long	get_time_tv(struct timeval *tv)
{
	return (((long long)(tv->tv_sec)) * 1000 + ((long long)(tv->tv_usec)) / 1000);
}

int	diff_time_tv(struct timeval *tv1, struct timeval *tv2)
{
	if (get_time_tv(tv2) - get_time_tv(tv1) < FREQ_UPDATE)
		return (0);
	return (1);
}

void	update_time_tv(struct timeval *tv, long long sec, long long usec)
{
	tv->tv_sec += sec;
	tv->tv_usec += usec;
}

# define UPDATE_TEXTURE(sec) (sec % TEXTURE_UPDATE_FREQ) == 0
# define TIME_TV(tv) 
# define DIFF_TV(tv1, tv2) (TIME_TV(tv2) - TIME_TV(tv1) < TEXTURE_UPDATE_FREQ)
# define UPDATE_TV(tv, TEXTURE_UPDATE_FREQ)
