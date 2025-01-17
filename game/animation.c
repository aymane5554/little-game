/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:16:30 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 11:19:36 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	*animate_r(t_game game, t_player player)
{
	static int	m;

	if (game.map[player.y][player.x] == 'E')
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[3], player.x * 32, player.y * 32);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[2], player.x * 32, player.y * 32);
	}
	if (m == 32)
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.img, (player.x * 32) + m, player.y * 32);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.animations[m / 4], (player.x * 32) + m, player.y * 32);
	}
	m += 4;
	return (&m);
}

int	*animate_l(t_game game, t_player player)
{
	static int	m;

	if (game.map[player.y][player.x] == 'E')
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[3], player.x * 32, player.y * 32);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[2], player.x * 32, player.y * 32);
	}
	if (m == 32)
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.left_img, (player.x * 32) - m, player.y * 32);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.rev_animations[m / 4], (player.x * 32) - m, player.y * 32);
	}
	m += 4;
	return (&m);
}

int	*animate_u(t_game game, t_player player)
{
	static int	m;

	if (game.map[player.y][player.x] == 'E')
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[3], player.x * 32, player.y * 32);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[2], player.x * 32, player.y * 32);
	}
	if (m == 32)
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.img, player.x * 32, (player.y * 32) - m);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.animations[m / 4], player.x * 32, (player.y * 32) - m);
	}
	m += 4;
	return (&m);
}

int	*animate_d(t_game game, t_player player)
{
	static int	m;

	if (game.map[player.y][player.x] == 'E')
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[3], player.x * 32, player.y * 32);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			game.images[2], player.x * 32, player.y * 32);
	}
	if (m == 32)
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.img, (player.x * 32), (player.y * 32) + m);
	}
	else
	{
		mlx_put_image_to_window(game.mlx, game.win,
			player.animations[m / 4], player.x * 32, (player.y * 32) + m);
	}
	m += 4;
	return (&m);
}
