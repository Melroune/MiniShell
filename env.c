/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 05:45:45 by akerkeb           #+#    #+#             */
/*   Updated: 2015/01/07 05:45:50 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_env(t_env *e)
{
	ft_putab(e->env);
}

void	ft_putab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
}

void	setvar(t_env *e, char *var, char *value)
{
	int		i;

	i = 0;
	while (e->env[i])
	{
		if (!ft_strncmp(e->env[i], var, ft_strlen(var)))
			e->env[i] = ft_strjoin(var, ft_strjoin("=", value));
		i++;
	}
}

char	*getvar(t_env *e, char *var)
{
	int		i;

	i = 0;
	while (e->env[i])
	{
		if (!ft_strncmp(e->env[i], var, ft_strlen(var)))
		{
			return (ft_strchr(e->env[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}

void	get_path(t_env *e)
{
	int		i;

	i = 0;
	e->path = NULL;
	while (e->env[i])
	{
		if (!ft_strncmp(e->env[i], "PATH", 4))
			e->path = ft_strsplit(ft_strchr(e->env[i], '=') + 1, ':');
		i++;
	}
}
