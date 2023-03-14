/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:22:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/02/28 16:32:57 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	press_key_code_esc(t_engine_game *game)
{
	mlx_destroy_window(game->mlx_start, game->window_param);
	exit(EXIT_SUCCESS);
}

int	press_key_code_w(t_engine_game *game)
{
	if (game->map.map[game->pos_y - 1][game->pos_x] != '1')
	{
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.floor,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->pos_y--;
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.player_up,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->nbr_pas++;
		printf("Nombre de pas : %d\n", game->nbr_pas);
	}
	return (0);
}

int	press_key_code_a(t_engine_game *game)
{
	if (game->map.map[game->pos_y][game->pos_x - 1] != '1')
	{
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.floor,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->pos_x--;
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.player_left,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->nbr_pas++;
		printf("Nombre de pas : %d\n", game->nbr_pas);
	}
	return (0);
}

int	press_key_code_s(t_engine_game *game)
{
	if (game->map.map[game->pos_y + 1][game->pos_x] != '1')
	{
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.floor,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->pos_y++;
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.player_down,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->nbr_pas++;
		printf("Nombre de pas : %d\n", game->nbr_pas);
	}
	return (0);
}

int	press_key_code_d(t_engine_game *game)
{
	if (game->map.map[game->pos_y][game->pos_x + 1] != '1')
	{
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.floor,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->pos_x++;
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.player_right,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->nbr_pas++;
		printf("Nombre de pas : %d\n", game->nbr_pas);
	}
	return (0);
}
