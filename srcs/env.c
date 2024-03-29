/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:38:07 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 19:38:12 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*get_envs(char **envp)
{
	int		name_end;
	t_env	*env;
	t_list	*envs;

	envs = NULL;
	while (*envp)
	{
		env = (t_env *)malloc(sizeof(t_env));
		name_end = ft_strchr(*envp, '=') - *envp;
		env->key = ft_substr(*envp, 0, name_end);
		env->value = ft_substr(*envp, name_end + 1,
		ft_strlen(*envp) - name_end - 1);
		ft_lstadd_back(&envs, ft_lstnew(env));
		envp++;
	}
	return (envs);
}
