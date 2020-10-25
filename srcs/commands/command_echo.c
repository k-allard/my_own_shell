/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:29:37 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 17:30:43 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		command_echo(char **argv)
{
	size_t	i;
	int		new_line;

	i = 1;
	new_line = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0) //если -n то нам не надо печатать перенос строки
	{
		new_line = 0;
		i++;
	} //а еще таких аргументов может быть несколько типа echo -n -n -n meow и напечатается тогда только meow
	i--;
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], 1); 
		if (argv[i + 1] != 0)
			ft_putstr_fd(" ", 1); 
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
}