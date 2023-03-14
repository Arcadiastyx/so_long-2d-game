/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:55:04 by inaranjo          #+#    #+#             */
/*   Updated: 2023/02/28 17:32:21 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_if_mapdata_is_ok(t_engine_game *game)
{
	int		y;
	size_t	x;

	y = 0;
	x = 0;
	while (game->map.map[y])
	{
		while (x < ft_strlen(game->map.map[y]) - 1)
		{
			if (ft_strchr("01CEP", game->map.map[y][x]) == NULL)
			{
				perror("ERROR : il y un problem avec un char(01CEP)\n");
				exit(EXIT_FAILURE);
			}
			x++;
		}
		x = 0;
		y++;
	}
	error_on_char(game);
	error_on_map_if_not_rec(game);
	error_on_walls(game);
	error_on_player(game);
	return (0);
}

void	error_on_char(t_engine_game *game)
{
	if (check_nbr_of_char(game) == 1)
	{
		perror("ERROR : 'P'= 1 ,'E' = 1, 'C' = 3 (nombre_autorisé)\n");
		exit(EXIT_FAILURE);
	}
}

void	error_on_map_if_not_rec(t_engine_game *game)
{
	if (check_if_map_is_rec(game) == 1)
	{
		perror("ERROR : attention la map n est pas rectangle\n");
		exit(EXIT_FAILURE);
	}
}

void	error_on_walls(t_engine_game *game)
{
	if (check_walls_left_right(game->map.nbr_lines - 1, game->map.map) == 1)
	{
		perror("ERROR : attention les murs ne sont pas valides, mur = 1\n");
		exit(EXIT_FAILURE);
	}
}

void	error_on_player(t_engine_game *game)
{
	if (game->map.nbr_player > 1)
	{
		perror("ERROR : c'est un jeux solo, un seul 'P' est autorisé\n");
		exit(EXIT_FAILURE);
	}
}
