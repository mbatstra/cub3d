/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:31:14 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/03/20 17:04:27 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int8_t	mapindex(t_map *map, int32_t x, int32_t y)
{
	return (map->grid[x + y * map->size.x]);
}

int32_t	main(int argc, char **argv)
{
	t_vars	vars;
	bool	error;

	error = false;
	vars.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!vars.mlx)
		return (EXIT_FAILURE);
	parse(argc, argv, &vars);
	render2d_init(&vars);
	sprites_init(&vars);
	vars.canvas = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (vars.canvas == NULL)
		return (EXIT_FAILURE);
	mlx_image_to_window(vars.mlx, vars.canvas, 0, 0);
	vars.canvas->instances[0].z = Z_LVL_CANVAS;
	error |= !mlx_loop_hook(vars.mlx, &player_hook, &vars);
	error |= !mlx_loop_hook(vars.mlx, &render, &vars);
	error |= !mlx_loop_hook(vars.mlx, &render2d_minimap, &vars);
	error |= !mlx_loop_hook(vars.mlx, &enemy_hook, &vars);
	error |= !mlx_loop_hook(vars.mlx, &game_hook, &vars);
	if (error)
		return (EXIT_FAILURE);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
