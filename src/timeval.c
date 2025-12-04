/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:02:21 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/04 12:22:07 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static long long	get_time_tv(long long sec, long long usec)
{
	return (sec * 1000 + usec / 1000);
}

int	diff_time_tv(struct timeval *tv1, struct timeval *tv2)
{
	if (get_time_tv(tv2->tv_sec, tv2->tv_usec)
		- get_time_tv(tv1->tv_sec, tv1->tv_usec)
		< get_time_tv(FREQ_SEC, FREQ_USEC))
		return (0);
	return (1);
}

void	update_time_tv(struct timeval *tv, long long sec, long long usec)
{
	tv->tv_sec += sec;
	tv->tv_usec += usec;
}
