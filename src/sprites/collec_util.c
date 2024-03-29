/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collec_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:22:57 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/15 19:45:45 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "parse.h"
#include "cub3d.h"

void	collec_init(t_vars *vars, t_sprite *collec, t_vect2 pos)
{
	uint8_t	i;

	collec->pix_arr[0] = mlx_load_xpm42("assets/crystal.xpm42");
	collec->pix_arr[1] = mlx_load_xpm42("assets/crystal22.5.xpm42");
	collec->pix_arr[2] = mlx_load_xpm42("assets/crystal45.xpm42");
	collec->pix_arr[3] = mlx_load_xpm42("assets/crystal67.5.xpm42");
	collec->pix_arr[4] = mlx_load_xpm42("assets/crystal-67.5.xpm42");
	collec->pix_arr[5] = mlx_load_xpm42("assets/crystal-45.xpm42");
	collec->pix_arr[6] = mlx_load_xpm42("assets/crystal-22.5.xpm42");
	i = 0;
	while (i < 7)
	{
		if (collec->pix_arr[i] == NULL)
			exit_strerr(MALLOC_ERR);
		i++;
	}
	collec->pos.x = (double)(pos.x + 0.5);
	collec->pos.y = (double)(pos.y + 0.5);
	collec->frame = 0;
	collec->tex = mlx_texture_to_image(vars->mlx, &collec->pix_arr[0]->texture);
	if (collec->tex == NULL)
		exit_strerr(MALLOC_ERR);
	free(collec->tex->pixels);
	collec->tex->pixels = collec->pix_arr[0]->texture.pixels;
}

void	collec_update_frame(t_sprite *collec, double t_delta)
{
	if (!collec->is_animated)
		return ;
	collec->t_delta += t_delta;
	if (collec->t_delta > ANIM_FR)
	{
		collec->t_delta = 0;
		collec->frame++;
	}
	if (collec->frame == 7)
		collec->frame = 0;
	collec->tex->pixels = collec->pix_arr[collec->frame]->texture.pixels;
}
