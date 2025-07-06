/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorel <gamorel@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:00 by gamorel           #+#    #+#             */
/*   Updated: 2025/07/05 16:00:00 by gamorel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 9

/************************ AFFICHAGE ************************/

void	ft_putchar(char c)
{
	// Affiche un caractère sur la sortie standard
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	// Affiche une chaîne de caractères
	while (*s)
		write(1, s++, 1);
}

void	ft_putnbr(int nb)
{
	// Affiche un nombre entier en base 10
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

/******************* PARSING & VALIDATION ******************/

int	ft_count_numbers(char *str)
{
	// Compte le nombre total de chiffres entre 1 et 9 dans la chaîne
	int	count = 0;
	while (*str)
	{
		if ((*str >= '1' && *str <= '9') &&
			(*(str + 1) == ' ' || *(str + 1) == '\0'))
			count++;
		str++;
	}
	return (count);
}

int	ft_parse_args(char *str, int *out, int n)
{
	// Convertit la chaîne d'entrée en tableau d'entiers si valide
	int	i = 0;
	while (*str)
	{
		if (*str >= '1' && *str <= '0' + n)
		{
			out[i++] = *str - '0';
			if (*(str + 1) != ' ' && *(str + 1) != '\0')
				return (0);
		}
		else if (*str != ' ')
			return (0);
		str++;
	}
	return (i == n * 4);
}

/*************** VALIDATION DE GRILLE *****************/

int	ft_check_valid(int *line, int n)
{
	// Vérifie que chaque ligne/colonne contient des valeurs uniques
	int	*check = malloc(sizeof(int) * n);
	int	i = 0;

	if (!check)
		return (0);
	while (i < n)
		check[i++] = 0;
	i = 0;
	while (i < n)
	{
		if (line[i] < 1 || line[i] > n || check[line[i] - 1]++)
			return (free(check), 0);
		i++;
	}
	free(check);
	return (1);
}

int	ft_visible_count(int *line, int n)
{
	// Calcule combien de caisses sont visibles depuis un côté
	int	max = 0;
	int	count = 0;
	int	i = 0;

	while (i < n)
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

int	ft_verify_colrow(int *line, int expected, int n)
{
	// Vérifie si le nombre de caisses visibles correspond à la contrainte
	return (ft_visible_count(line, n) == expected);
}

int	ft_verify_all(int *args, int **grid, int n)
{
	// Vérifie toutes les contraintes de visibilité du sujet
	int	i = 0, j;
	int	*line = malloc(sizeof(int) * n);

	if (!line)
		return (0);
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			line[j] = grid[j][i];
			j++;
		}
		if (!ft_verify_colrow(line, args[i], n))
			return (free(line), 0);
		j = 0;
		while (j < n)
		{
			line[j] = grid[n - 1 - j][i];
			j++;
		}
		if (!ft_verify_colrow(line, args[n + i], n))
			return (free(line), 0);
		j = 0;
		while (j < n)
		{
			line[j] = grid[i][j];
			j++;
		}
		if (!ft_verify_colrow(line, args[2 * n + i], n))
			return (free(line), 0);
		j = 0;
		while (j < n)
		{
			line[j] = grid[i][n - 1 - j];
			j++;
		}
		if (!ft_verify_colrow(line, args[3 * n + i], n))
			return (free(line), 0);
		i++;
	}
	free(line);
	return (1);
}

int	ft_is_valid_grid(int **grid, int n)
{
	// Vérifie qu'aucune caisse n'est répétée par ligne ou colonne
	int	i = 0, j;
	int	*col = malloc(sizeof(int) * n);

	if (!col)
		return (0);
	while (i < n)
	{
		if (!ft_check_valid(grid[i], n))
			return (free(col), 0);
		j = 0;
		while (j < n)
		{
			col[j] = grid[j][i];
			j++;
		}
		if (!ft_check_valid(col, n))
			return (free(col), 0);
		i++;
	}
	free(col);
	return (1);
}

/********************* RESOLUTION & AFFICHAGE *******************/

void	ft_put_solution(int **grid, int n)
{
	// Affiche la grille solution au format demandé
	int	i = 0, j;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			ft_putnbr(grid[i][j]);
			if (j < n - 1)
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	ft_copy_line(int *dst, int *src, int n)
{
	// Copie une ligne entière
	int	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

void	ft_generate_perms(int **perms, int *temp, int *used, int depth, int n, int *count)
{
	// Génère récursivement toutes les permutations possibles pour une ligne
	int	i = 0;
	while (i < n)
	{
		if (!used[i])
		{
			used[i] = 1;
			temp[depth] = i + 1;
			if (depth + 1 == n)
				ft_copy_line(perms[*count], temp, n), (*count)++;
			else
				ft_generate_perms(perms, temp, used, depth + 1, n, count);
			used[i] = 0;
		}
		i++;
	}
}

void	ft_init_grid(int **grid, int n)
{
	// Alloue de la mémoire pour chaque ligne de la grille
	int	i = 0;
	while (i < n)
	{
		grid[i] = malloc(sizeof(int) * n);
		i++;
	}
}

void	ft_copy_grid(int **dst, int **src, int n)
{
	// Copie la grille entière
	int	i = 0, j;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	ft_solve(int *args, int **grid, int n, int row, int **perms, int pcount)
{
	// Résout la grille récursivement en plaçant une ligne après l'autre
	int	i = 0, j;
	int	**new_grid = malloc(sizeof(int *) * n);

	ft_init_grid(new_grid, n);
	while (i < pcount)
	{
		ft_copy_grid(new_grid, grid, n);
		j = 0;
		while (j < n)
		{
			new_grid[row][j] = perms[i][j];
			j++;
		}
		if (row + 1 == n && ft_is_valid_grid(new_grid, n)
			&& ft_verify_all(args, new_grid, n))
		{
			ft_put_solution(new_grid, n);
			exit(0);
		}
		ft_solve(args, new_grid, n, row + 1, perms, pcount);
		i++;
	}
	while (--i >= 0)
		free(new_grid[i]);
	free(new_grid);
}

/******************************* MAIN *******************************/

int	main(int argc, char **argv)
{
	int	n, nb_args, perm_count = 1, i = 2;
	int	*args, **grid, **perms, *temp, *used;

	if (argc != 2)
		return (ft_putstr("Error\n"), 1);
	nb_args = ft_count_numbers(argv[1]);
	if (nb_args % 4 != 0 || nb_args / 4 > MAX_SIZE)
		return (ft_putstr("Error\n"), 1);
	n = nb_args / 4;
	args = malloc(sizeof(int) * 4 * n);
	if (!ft_parse_args(argv[1], args, n))
		return (ft_putstr("Error\n"), 1);
	grid = malloc(sizeof(int *) * n);
	ft_init_grid(grid, n);
	while (i <= n)
		perm_count *= i++;
	perms = malloc(sizeof(int *) * perm_count);
	i = 0;
	while (i < perm_count)
		perms[i++] = malloc(sizeof(int) * n);
	temp = malloc(sizeof(int) * n);
	used = malloc(sizeof(int) * n);
	i = 0;
	while (i < n)
		used[i++] = 0;
	i = 0;
	ft_generate_perms(perms, temp, used, 0, n, &i);
	ft_solve(args, grid, n, 0, perms, i);
	ft_putstr("Error\n");
	return (1);
}
