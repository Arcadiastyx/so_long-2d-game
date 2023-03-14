/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:59:02 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/02 13:30:42 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include "libft/get_next_line.h" 
# include <fcntl.h>

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define IS_WALKING 0
# define IS_NOT_WALKING 1

/*resolution de l image*/
# define IMG_SIZE 32

/* touche pour movements*/
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

/*macro pour sprite*/
# define GROUND "textures/background.xpm"
# define WALL "textures/wall_01.xpm"
# define EXIT "textures/exit.xpm"
# define ITEM "textures/item.xpm"
# define PLAYER_RIGHT "textures/player_right.xpm"
# define PLAYER_UP "textures/player_up.xpm"
# define PLAYER_LEFT "textures/player_left.xpm"
# define PLAYER_DOWN "textures/player_down.xpm"

/* Stock mes données via des varibles prédéfinies.
- ici je vais allouer de l espace pour ma map.ber qui contien :
	- la longeur de la map qui sera de 10 (pour commencer)
	- la hauteur de l map qui sera de 5 (pour commencer)
	- la variable axe_x sera utilisé 
	  comme un index pour bouger sur les lignes
	- la variable axe_y sera utilisé 
	  comme un index pour bouger sur les colones
	- un espace dédié au player
	- un espace dédié au collectible
	- un espace dédié à la sortie
ainsi toute ces variables vont pouvoir être exploitées
dans notre code via t_map_data.*/

typedef struct s_map_data
{
	int		fd;
	char	*map_file;
	char	**map;
	int		nbr_lines;
	int		colones;
	int		axe_x;
	int		axe_y;
	int		player;
	int		items;
	int		exit;
	int		nbr_item_collected;
	int		nbr_player;
	int		nbr_exit;
	int		nbr_item;
	int		total_item_to_collect;
	int		you_can_exit;
	int		exit_x;
	int		exit_y;

	size_t	row_len;

}				t_map_data;

/*ici mes variables de type void vont pointer 
 * chaqu une sur une sprite qui seront appelé
 * pour remplacer les valeurs de la map.ber */

typedef struct s_img_data
{
	int		img_h;
	int		img_l;
	void	*img;
	void	*wall;
	void	*floor;
	void	*player;
	void	*player_right;
	void	*player_left;
	void	*player_up;
	void	*player_down;
	void	*items;
	void	*exit;

}				t_img_data;

typedef struct s_engine_game
{
	t_map_data		map;
	t_img_data		img;
	t_img_data		**img_data;
	void			*mlx_start;
	void			*window_param;
	int				window_largeur;
	int				window_hauteur;
	int				x;
	int				y;
	int				pos_x;
	int				pos_y;
	int				moves;
	int				nbr_pas;

}				t_engine_game;

void		ft_free(char **tab);
int			get_nbr_lines(char *map_file);
void		memset_map_row_line(int row, int column,
				int i, t_engine_game *game);
void		map_setup(char *map_file, t_engine_game *game);
void		init_map(t_engine_game *game);
void		init_img(t_engine_game *game);
void		put_img_to_win(t_engine_game *game, int width, int y, int x);
int			init_window(t_engine_game *game);
int			create_map_base_on_data(t_engine_game *game);
int			check_arg(char *map_file);
void		init_player(t_engine_game *game);
int			press_key_code_action(int key_code, t_engine_game *game);
int			check_valeur_map_for_player_moves(t_engine_game *game,
				char direction, char next_char_map);
void		move_player(t_engine_game *game, char direction);
void		exit_game(t_engine_game *game);
void		ft_move(t_engine_game *game, char pos, int dir);
void		check_direction(t_engine_game *game);
void		win_game(t_engine_game *game);
void		check_exit(t_engine_game *game);
int			check_nbr_of_char(t_engine_game *game);
int			check_if_map_is_rec(t_engine_game *game);
int			check_walls_top_bot(int row, char **map);
int			check_walls_left_right(int nbr_lines, char **map);
int			check_if_mapdata_is_ok(t_engine_game *game);
void		press_key_code_esc(t_engine_game *game);
int			press_key_code_w(t_engine_game *game);
int			press_key_code_a(t_engine_game *game);
int			press_key_code_s(t_engine_game *game);
int			press_key_code_d(t_engine_game *game);
void		win_condition(t_engine_game *game);
void		item_update(t_engine_game *game);
void		manage_exit(t_engine_game *game);
void		error_on_player(t_engine_game *game);
void		error_on_walls(t_engine_game *game);
void		error_on_map_if_not_rec(t_engine_game *game);
void		error_on_char(t_engine_game *game);
void		set_exit(t_engine_game *game, int x, int y);
int			close_window_event(void *param);
char		**copy_of_the_original_map(t_engine_game *game);
int			error_msg_abs_path(t_engine_game *game);
int			error_msg_on_ac(int ac);
void		flood_fill(t_engine_game *game, char **map, int x, int y);
int			count_collectibles(char **map);
int			check_path(t_engine_game *game);

#endif