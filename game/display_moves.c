/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:47:31 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 11:39:25 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	change_coordinates(t_arg *arg)
{
	if (arg->player.state == 'R')
		arg->player.x++;
	else if (arg->player.state == 'L')
		arg->player.x--;
	else if (arg->player.state == 'D')
		arg->player.y++;
	else if (arg->player.state == 'U')
		arg->player.y--;
}

int	draw_movement(t_arg *arg)
{
	int	*mm;

	mm = NULL;
	if (arg->player.state == 'R')
		mm = animate_r(arg->game, arg->player);
	else if (arg->player.state == 'L')
		mm = animate_l(arg->game, arg->player);
	else if (arg->player.state == 'D')
		mm = animate_d(arg->game, arg->player);
	else if (arg->player.state == 'U')
		mm = animate_u(arg->game, arg->player);
	if (*mm > 32)
	{
		*mm = 0;
		change_coordinates(arg);
		if (arg->game.map[arg->player.y][arg->player.x] == 'C')
		{
			arg->game.map[arg->player.y][arg->player.x] = '0';
		}
		arg->player.state = 'P';
	}
	return (0);
}

void	touched_enemy(t_arg *arg)
{
	int		i;

	i = 0;
	while (i < arg->game.number_of_enemies)
	{
		if (sqrt(pow(((arg->player.x * 32) + 16)
					- (arg->game.enemies[i].x + 16), 2)
				+ pow(((arg->player.y * 32) + 16)
					- (arg->game.enemies[i].y + 16), 2)) <= 16)
		{
			mlx_put_image_to_window(arg->game.mlx,
				arg->game.win, arg->game.limg,
				((arg->game.width_height[0] * 32) / 2) - 64,
				((arg->game.width_height[1] * 32) / 2) - 32);
			arg->player.state = 'F';
			mlx_put_image_to_window(arg->game.mlx, arg->game.win,
				arg->game.images[2], arg->player.x * 32, arg->player.y * 32);
		}
		i++;
	}
}

int	display_moves(t_arg *arg)
{
	struct timespec	request;
	struct timespec	remaining;

	request.tv_sec = 0;
	request.tv_nsec = 14444444;
	if (arg->player.state == 'R' || arg->player.state == 'L'
		|| arg->player.state == 'U' || arg->player.state == 'D')
		draw_movement(arg);
	if (arg->player.state != 'F')
	{
		touched_enemy(arg);
		move_enemies(&(arg->game));
	}
	nanosleep(&request, &remaining);
	return (1);
}
