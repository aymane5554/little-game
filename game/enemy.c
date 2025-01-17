/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:20:08 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 11:41:31 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_enemies(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map[i][j] == 'A')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	move_enemy_right(t_game *game, int i)
{
	if (game->map[game->enemies[i].y / 32]
		[(game->enemies[i].x + 32) / 32] != '0'
		&& game->map[game->enemies[i].y / 32]
		[(game->enemies[i].x + 32) / 32] != 'A')
		game->enemies[i].velocity *= -1;
	game->enemies[i].x += game->enemies[i].velocity * 2;
	mlx_put_image_to_window(game->mlx,
		game->win, game->e_img_r, game->enemies[i].x, game->enemies[i].y);
}

void	move_enemy_left(t_game *game, int i)
{
	if (game->map[game->enemies[i].y / 32]
		[(game->enemies[i].x - 2) / 32] != '0'
		&& game->map[game->enemies[i].y / 32]
		[(game->enemies[i].x - 2) / 32] != 'A')
		game->enemies[i].velocity *= -1;
	game->enemies[i].x += game->enemies[i].velocity * 2;
	mlx_put_image_to_window(game->mlx,
		game->win, game->e_img_l, game->enemies[i].x, game->enemies[i].y);
}

void	move_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->number_of_enemies)
	{
		mlx_put_image_to_window(game->mlx,
			game->win, game->images[2], game->enemies[i].x, game->enemies[i].y);
		if (game->enemies[i].velocity > 0)
			move_enemy_right(game, i);
		else if (game->enemies[i].velocity <= 0)
			move_enemy_left(game, i);
		i++;
	}
}
