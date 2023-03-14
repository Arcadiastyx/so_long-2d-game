/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:05:19 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/02 13:33:36 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*but fermer la fenetre toute en liberant la memoire*/
int	close_window_event(void *param)
{
	t_engine_game	*game;

	game = (t_engine_game *) param;
	mlx_clear_window(game->mlx_start, game->window_param);
	mlx_destroy_window(game->mlx_start, game->window_param);
	free(game->mlx_start);
	if (game->map.map)
		ft_free(game->map.map);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_engine_game	game;

	error_msg_on_ac(ac);
	{
		if (check_arg (av[1]) == 1)
		{
			perror("ERROR: l'arguement fournis ne correspond pas a un .ber\n");
			exit(EXIT_FAILURE);
		}
		map_setup(av[1], &game);
		init_map(&game);
		check_if_mapdata_is_ok(&game);
		init_window(&game);
		init_img(&game);
		init_player(&game);
		create_map_base_on_data(&game);
		error_msg_abs_path(&game);
		mlx_key_hook(game.window_param, press_key_code_action, &game);
		mlx_hook(game.window_param, 17, 0, close_window_event, &game);
		mlx_loop(game.mlx_start);
		free(game.mlx_start);
		if (game.map.map)
			ft_free(game.map.map);
	}
	return (0);
}
