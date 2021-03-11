/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:32:44 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/11 19:33:05 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		check_argv2(char *av)
{
	int i;

	i = -1;
	if (av[i + 1] && av[++i] == '-')
		if (av[i + 1] && av[++i] == '-')
			if (av[i + 1] && av[++i] == 's')
				if (av[i + 1] && av[++i] == 'a')
					if (av[i + 1] && av[++i] == 'v')
						if (av[i + 1] && av[++i] == 'e')
							if (!av[i + 1])
								return (1);
	return (0);
}

int		check_argv1(char *av)
{
	int		i;
	int		z;

	i = -1;
	z = -1;
	while (av[++i])
		if (av[i] == '.')
		 	z = i;
	if (z != -1)
		if(av[z + 1] && av[++z] == 'c')
			if(av[z + 1] && av[++z] == 'u')
				if(av[z + 1] && av[++z] == 'b')
					if(!av[z + 1])
						return (1);
	return (0);
}

int		check_args(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Error\nNo map file \"*.cub\" passed by 1st argument\n");
		return (0);
	}
	if (ac == 2 || ac == 3)
	{
		if (!check_argv1(av[1]))
		{
			printf("Error\nBad extension name of the map file\nOnly accept \"*.cub\"\n");
			return(0);
		}
		if (ac == 3)
		{
			if(!check_argv2(av[2]))
				{
					printf("Error\nBad target arg2\nOnly accept \"--save\"\n");
					return (0);
				}
			else
				return (2);
		}
	}
	return (1);
}
