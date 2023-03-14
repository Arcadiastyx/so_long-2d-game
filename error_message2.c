/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:56:40 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/02 13:27:44 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_msg_abs_path(t_engine_game *game)
{
	if (!check_path(game))
	{
		perror("ERROR : absolut path non valide\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	error_msg_on_ac(int ac)
{
	if (ac != 2)
	{
		perror("ERROR: sur le nombre d'argument, ac == 2\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
