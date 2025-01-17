/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:46:08 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/01 14:33:54 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	moveup(t_game *game, t_player *player)
{
	if (game->map[player->y - 1][player->x] != '1' && player->state == 'P')
	{
		if (game->map[player->y - 1][player->x] == 'C')
			player->coins++;
		else if (game->map[player->y - 1][player->x] == 'E')
			return (end(player, game, player->x, player->y - 1));
		if (game->map[player->y][player->x] == 'E')
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->images[3], player->x * 32, player->y * 32);
		}
		player->state = 'U';
		player->moves++;
		dislay_numbers(*game, player->coins);
	}
}

void	movedown(t_game *game, t_player *player)
{
	if (game->map[player->y + 1][player->x] != '1' && player->state == 'P')
	{
		if (game->map[player->y + 1][player->x] == 'C')
			player->coins++;
		else if (game->map[player->y + 1][player->x] == 'E')
			return (end(player, game, player->x, player->y + 1));
		if (game->map[player->y][player->x] == 'E')
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->images[3], player->x * 32, player->y * 32);
		}
		player->state = 'D';
		player->moves++;
		dislay_numbers(*game, player->coins);
	}
}

void	moveright(t_game *game, t_player *player)
{
	if (game->map[player->y][player->x + 1] != '1' && player->state == 'P')
	{
		if (game->map[player->y][player->x + 1] == 'C')
			player->coins++;
		else if (game->map[player->y][player->x + 1] == 'E')
			return (end(player, game, player->x + 1, player->y));
		if (game->map[player->y][player->x] == 'E')
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->images[3], player->x * 32, player->y * 32);
		}
		player->state = 'R';
		player->moves++;
		dislay_numbers(*game, player->coins);
	}
}

void	moveleft(t_game *game, t_player *player)
{
	if (game->map[player->y][player->x - 1] != '1' && player->state == 'P')
	{
		if (game->map[player->y][player->x - 1] == 'C')
			player->coins++;
		else if (game->map[player->y][player->x - 1] == 'E')
			return (end(player, game, player->x - 1, player->y));
		if (game->map[player->y][player->x] == 'E')
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->images[3], player->x * 32, player->y * 32);
		}
		player->state = 'L';
		player->moves++;
		dislay_numbers(*game, player->coins);
	}
}
 