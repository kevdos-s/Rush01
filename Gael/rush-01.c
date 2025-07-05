/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevdos-s <kevdos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:00 by gael              #+#    #+#             */
/*   Updated: 2025/07/05 21:05:48 by kevdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

/* ****************** Affichage ****************** */

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	ft_putnbr(int nb)
{
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}

/* Affiche la grille solution formatée */
void	ft_print_solution(int grid[4][4])
{
	int	row;
	int	col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			ft_putnbr(grid[row][col]);
			if (col < 3)
				ft_putchar(' ');
			col++;
		}
		ft_putchar('\n');
		row++;
	}
}

/* ****************** Parsing ****************** */

/* Parse la chaîne d'arguments en 16 int et valide le format */
int	ft_parse_args(char *str, int *out)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str >= '1' && *str <= '4')
		{
			out[i++] = *str - '0';
			if (*(str + 1) != ' ' && *(str + 1) != '\0')
				return (0);
		}
		else if (*str != ' ')
			return (0);
		str++;
	}
	return (i == 16);
}

/* ****************** Validation Grille ****************** */

/* Vérifie qu'une ligne/colonne contient chaque valeur 1-4 exactement une fois */
int	ft_check_valid(int *line)
{
	int	count[4] = {0, 0, 0, 0};
	int	i;

	i = 0;
	while (i < 4)
	{
		if (line[i] < 1 || line[i] > 4)
			return (0);
		if (count[line[i] - 1])
			return (0);
		count[line[i] - 1] = 1;
		i++;
	}
	return (1);
}

/* Compte le nombre de caisses visibles dans une ligne/colonne depuis la gauche */
int	ft_visible_count(int *line)
{
	int	i;
	int	max;
	int	count;

	max = 0;
	count = 0;
	i = 0;
	while (i < 4)
	{
		if (line[i] > max)
		{
			max = line[i];
			count++;
		}
		i++;
	}
	return (count);
}

/* Vérifie qu’une ligne/colonne correspond au nombre visible attendu */
int	ft_verify_colrow(int *line, int expected)
{
	return (ft_visible_count(line) == expected);
}

/* Vérifie toutes les contraintes de visibilité sur la grille */
int	ft_verify_all(int *args, int grid[4][4])
{
	int	i;
	int	col[4];

	i = 0;
	while (i < 4)
	{
		// Colonne de haut en bas
		col[0] = grid[0][i];
		col[1] = grid[1][i];
		col[2] = grid[2][i];
		col[3] = grid[3][i];
		if (!ft_verify_colrow(col, args[i]))
			return (0);

		// Colonne de bas en haut
		col[0] = grid[3][i];
		col[1] = grid[2][i];
		col[2] = grid[1][i];
		col[3] = grid[0][i];
		if (!ft_verify_colrow(col, args[i + 4]))
			return (0);

		// Ligne de gauche à droite
		col[0] = grid[i][0];
		col[1] = grid[i][1];
		col[2] = grid[i][2];
		col[3] = grid[i][3];
		if (!ft_verify_colrow(col, args[i + 8]))
			return (0);

		// Ligne de droite à gauche
		col[0] = grid[i][3];
		col[1] = grid[i][2];
		col[2] = grid[i][1];
		col[3] = grid[i][0];
		if (!ft_verify_colrow(col, args[i + 12]))
			return (0);

		i++;
	}
	return (1);
}

/* Vérifie que toutes les lignes et colonnes ont des valeurs valides et uniques */
int	ft_is_valid_grid(int grid[4][4])
{
	int	i;
	int	col[4];

	i = 0;
	while (i < 4)
	{
		// Vérifie ligne i
		if (!ft_check_valid(grid[i]))
			return (0);

		// Prépare colonne i
		col[0] = grid[0][i];
		col[1] = grid[1][i];
		col[2] = grid[2][i];
		col[3] = grid[3][i];

		// Vérifie colonne i
		if (!ft_check_valid(col))
			return (0);

		i++;
	}
	return (1);
}

/* Copie une grille source dans une grille destination */
void	ft_copy_grid(int dest[4][4], int src[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

/* ****************** Résolution par backtracking ****************** */

/*
** Toutes les permutations possibles de [1,2,3,4]
** Il y a 24 permutations, stockées dans perm[][] pour essayer chaque ligne.
*/
void	ft_solve_grid(int args[16], int grid[4][4], int row)
{
	int	perm[24][4] = {
		{1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
		{2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,1,3},{2,4,3,1},
		{3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},
		{4,1,2,3},{4,1,3,2},{4,2,1,3},{4,2,3,1},{4,3,1,2},{4,3,2,1}};
	int	new_grid[4][4];
	int	i;

	if (row == 4)
	{
		if (ft_is_valid_grid(grid) && ft_verify_all(args, grid))
		{
			ft_print_solution(grid);
			exit(0);
		}
		return;
	}
	i = 0;
	while (i < 24)
	{
		ft_copy_grid(new_grid, grid);
		new_grid[row][0] = perm[i][0];
		new_grid[row][1] = perm[i][1];
		new_grid[row][2] = perm[i][2];
		new_grid[row][3] = perm[i][3];
		ft_solve_grid(args, new_grid, row + 1);
		i++;
	}
}

/* ****************** main ****************** */

int	main(int argc, char **argv)
{
	int	args[16];
	int	grid[4][4] = {{0}};

	// Vérifie arguments et parse
	if (argc != 2 || !ft_parse_args(argv[1], args))
	{
		ft_putstr("Error\n");
		return (1);
	}

	// Lance la résolution
	ft_solve_grid(args, grid, 0);

	// Si aucune solution trouvée
	ft_putstr("Error\n");
	return (1);
}
