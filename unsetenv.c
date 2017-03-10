/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 01:56:23 by akerkeb           #+#    #+#             */
/*   Updated: 2014/12/31 01:56:41 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_strlen_max(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int		ft_erase(char **splitline, t_env *e)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	k = 0;
	tmp = (char **)malloc(sizeof(char *) * ft_strlen_max(e->env));
	if (tmp == NULL)
		return (0);
	while (e->env[i] != NULL)
	{
		if (ft_strncmp(e->env[i], splitline[1], ft_strlen(splitline[1])) != 0)
			tmp[k++] = ft_strdup(e->env[i]);
		i++;
	}
	e->env = tmp;
	return (0);
}

int		error_unsetenv(char **splitline)
{
	int i;

	i = 0;
	while (splitline[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("Too much arguments", 2);
		return (0);
	}
	else if (i < 2)
	{
		ft_putendl_fd("Not enough arguments", 2);
		return (0);
	}
	return (1);
}

int		ft_unsetenv(t_env *e, char **splitline)
{
	if (error_unsetenv(splitline))
	{
		if (!splitline[1])
		{
			ft_putendl_fd("Not enough arguments", 2);
			return (0);
		}
		if (is_chekenv(e, splitline) == 1)
		{
			if (is_chekenv(e, splitline) == 1)
				ft_erase(splitline, e);
		}
		get_path(e);
	}
	return (0);
}
