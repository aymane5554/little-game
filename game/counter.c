/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:07:47 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 11:11:26 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*image_name(char n)
{
	char	*filename;
	char	*template;
	int		i;

	i = 0;
	template = "textures/numbers/0.xpm";
	filename = malloc(23 * sizeof(char));
	while (template[i])
	{
		if (template[i] == '0')
			filename[i] = n;
		else
			filename[i] = template[i];
		i++;
	}
	filename[i] = '\0';
	return (filename);
}

void	dislay_numbers(t_game game, int moves)
{
	int		i;
	int		x;
	char	*num;
	void	*img;
	char	*filename;

	num = ft_itoa(moves);
	i = 0;
	while (num[i])
	{
		filename = image_name(num[i]);
		img = mlx_xpm_file_to_image(
				game.mlx, filename, &x, &x);
		mlx_put_image_to_window(game.mlx, game.win,
			img, i * 22, (game.width_height[1] - 1) * 32);
		free(filename);
		mlx_destroy_image(game.mlx, img);
		i++;
	}
	free(num);
}
