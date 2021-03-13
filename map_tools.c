/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:07:07 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/13 13:19:05 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		build_map(char *line, sett_data *settings)
{
	void(line);

	if (if_empty_line_and_slide_spaces(line) == -1)
	{
		if (!(*settings->map))
			return (1);
		else
			return (0);
	}
	printf("\nCOSTRUZIONE MAPPA\n");
	return (1);
}
