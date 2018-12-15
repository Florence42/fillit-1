/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:16:36 by vlaroque          #+#    #+#             */
/*   Updated: 2018/12/15 15:00:07 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			g_mat[20][20];
t_piece		g_tetris[26];

static int		determine_square_min(int nb_pieces)
{
	int	val;
	int	i;
	int	tmp;

	tmp = nb_pieces * 4;
	val = ft_sqrt(tmp);
	if (!val)
	{
		i = 1;
		while (!val)
		{
			val = ft_sqrt(tmp + i);
			i++;
		}
	}
	return (val);
}

/*void			print_strtab(t_piece **pieces)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (pieces[++i] != NULL)
	{
		y = 0;
		while (y < 4)
		{
			x = 0;
			while (x < 4)
			{
				if (pieces[i]->tab[y][x] == 0)
					ft_putchar('.');
				else
					ft_putchar(pieces[i]->tab[y][x]);
				ft_putchar(' ');
				x++;
			}
			ft_putchar('\n');
			y++;
		}
		ft_putchar('\n');
	}
}*/

int				rempli_structure(t_piece *pieces)
{
	int ind;
	int i;
	int j;

	ind = 0;
	while (pieces[ind].letter != 0)
	{
		g_tetris[ind].letter = pieces[ind].letter;
		i = 0;
		while (i < 4)
		{
			j = 0;
			while (j < 4)
			{
				g_tetris[ind].tab[i][j] = pieces[ind].tab[i][j];
				j++;
			}
			i++;
		}
		ind++;
	}
	return (ind);
}

int				main(int ac, char **av)
{
	int		fd;
	int		nb_pieces;
	t_piece	*res;

	if (ac != 2)
		ft_putstr("usage: fillit [filename]\n");
	fd = open(av[1], O_RDONLY);
	if (fd <= 0 || !(res = file_analyser(fd, &nb_pieces)))
	{
		ft_putstr("error\n");
		return (0);
	}
	rempli_structure(res);
	initialize_matrice();
	if (!i_check_solution(nb_pieces, determine_square_min(nb_pieces)))
	{
		ft_putstr("error\n");
		return (0);
	}
	close(fd);
	return (0);
}
