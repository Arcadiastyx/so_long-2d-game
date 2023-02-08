/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:59:02 by inaranjo          #+#    #+#             */
/*   Updated: 2023/02/08 15:03:34 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include "libft/get_next_line.h" 
# include <fcntl.h>


/*resolution de l image*/
# define IMG_SIZE 64
# define IMG_W 64
# define IMG_H 64

/* touche pour movements*/
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2

/*macro pour sprite*/
# define GROUND "textures/background.xpm"
# define WALL "textures/wall.xpm"
# define EXIT "textures/exit.xpm"
# define ITEM "textures/collectable.xpm"
# define PLAYER "textures/ship_right.xpm"


/* Stock mes données via des varibles prédéfinies.
- ici je vais allouer de l espace pour ma map.ber qui contien :
	- la longeur de la map qui sera de 10 (pour commencer)
	- la hauteur de l map qui sera de 5 (pour commencer)
	- la variable axe_x sera utilisé comme un index pour bouger sur les lignes
	- la variable axe_y sera utilisé comme un index pour bouger sur les colones
	- un espace dédié au player
	- un espace dédié au collectible
	- un espace dédié à la sortie
ainsi toute ces variables vont pouvoir être exploitées dans notre code via t_map_data.
*/
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

}				t_map_data;

/*ici mes variables de type void vont pointer chaqu une sur une sprite qui seront appelé
	pour remplacer les valeurs de la map.ber */
typedef struct s_img_data
{
	int		img_h;
	int		img_l;
	void	*img;
	void	*wall;
	void	*floor;
	void	*player;
	void	*items;
	void	*exit;

}				t_img_data;


typedef struct s_engine_game
{
	t_map_data		map;
	t_img_data		img;
	t_img_data		**img_data;
	void		*mlx_start;
	void		*window_param;
	int  window_largeur;
	int  window_hauteur;
	int			x;
	int			y;
	int			pos_x;
	int			pos_y;
	void		*mlx_end;
	int			moves;

}				t_engine_game;

void ft_free(char **tab);
int get_nbr_lines(char  *map_file);
void memset_map_row_line(int row,int column, int i,t_engine_game *game);
void map_setup(char *map_file,t_engine_game *game);
void init_map(t_engine_game *game);
void init_img(t_engine_game *game);
void put_img_to_win(t_engine_game *game, int width,int y,int x);
int init_window(t_engine_game *game);
int create_map(t_engine_game *game);
int check_arg(char *map_file);


#endif
