/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_map_content.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 13:24:37 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/03/20 16:28:21 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static uint32_t	st_len_to_char(char *str, char c)
{
	uint32_t	len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

static void	st_copy_content(t_map *map, char *str)
{
	int32_t	i;
	int32_t	j;
	char	*line;

	i = 0;
	j = 0;
	line = NULL;
	while (str[i])
	{
		line = ft_substr(str, i, st_len_to_char(str + i, '\n'));
		if (line == NULL)
			exit_strerr(MALLOC_ERR);
		ft_memmove(map->grid + j, line, ft_strlen(line));
		j += map->size.x;
		i += ft_strlen(line);
		free(line);
		if (str[i] == '\0')
			break ;
		i++;
	}
}

static void	st_get_player_pos(t_vars *var)
{
	t_fvect2	*table;
	uint32_t	player_idx;
	uint32_t	len;

	table = (t_fvect2 [128]){['N'] = {0.0, -1.0}, ['S'] = {0.0, 1.0}, \
	['W'] = {-1.0, 0.0}, ['E'] = {1.0, 0.0}};
	len = var->map.size.x * var->map.size.y;
	player_idx = 0;
	while (player_idx < len)
	{
		if (var->map.grid[player_idx] == 'N' || \
		var->map.grid[player_idx] == 'S' || var->map.grid[player_idx] \
		== 'E' || var->map.grid[player_idx] == 'W')
			break ;
		player_idx++;
	}
	var->player.pos.y = (player_idx / var->map.size.x) + 0.5;
	var->player.pos.x = (player_idx % var->map.size.x) + 0.5;
	var->player.dir = vec_rot(table[(int) var->map.grid[player_idx]], 0.01);
	var->map.grid[player_idx] = START_POS;
}

static void	st_set_map_size(t_map *map, char *map_str)
{
	int32_t	x;
	int32_t	y;
	int32_t	i;
	int32_t	max_x;

	i = 0;
	x = 0;
	y = 0;
	max_x = 0;
	while (map_str[i])
	{
		x = 0;
		while (map_str[i] != '\n' && map_str[i])
		{
			x++;
			i++;
		}
		y++;
		if (x > max_x)
			max_x = x;
		if (map_str[i] == '\0')
			break ;
		i++;
	}
	map->size = (t_vect2){.x = max_x, .y = y};
}

void	set_map_content(t_vars *vars, char *str)
{
	int32_t	len;
	int32_t	i;
	uint8_t	*table;

	table = (uint8_t [128]){[' '] = UNREACH, ['H'] = ENEMY, ['C'] = \
		COLLEC, ['X'] = EXIT};
	st_set_map_size(&vars->map, str);
	len = vars->map.size.x * vars->map.size.y;
	vars->map.grid = ft_calloc(len, sizeof(int8_t));
	if (vars->map.grid == NULL)
		exit_strerr(MALLOC_ERR);
	ft_memset(vars->map.grid, ' ', len * sizeof(int8_t));
	st_copy_content(&vars->map, str);
	i = 0;
	while (i < len)
	{
		if (ft_isdigit(vars->map.grid[i]))
			vars->map.grid[i] -= '0';
		else if (!ft_strchr("NSEW", vars->map.grid[i]))
			vars->map.grid[i] = table[(int)vars->map.grid[i]];
		i++;
	}
	st_get_player_pos(vars);
}
