/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/01 19:22:01 by akerkeb           #+#    #+#             */
/*   Updated: 2015/01/01 19:22:03 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_verifargv(t_env *e, char **splitline)
{
	if (!splitline[1])
	{
		ft_cd_home(e, splitline);
		return (1);
	}
	else if (ft_strcmp(splitline[1], "--") == 0)
	{
		ft_cd_home(e, splitline);
		return (1);
	}
	else if (ft_strcmp(splitline[1], "~") == 0)
	{
		ft_cd_home(e, splitline);
		return (1);
	}
	else if (ft_strcmp(splitline[1], "-") == 0)
	{
		ft_cd_back(e, splitline);
		return (1);
	}
	return (0);
}

void	cd_swap3(char *tmp, char *pwd, t_env *e, int i)
{
	tmp[i] = '\0';
	pwd = tmp;
	if (chdir(tmp) == 0)
	{
		setvar(e, "PWD", pwd);
		setvar(e, "OLDPWD", getvar(e, "PWD"));
	}
	else
	{
		if (access(pwd, F_OK) != 0)
		{
			ft_putstr_fd("cd : no such file or directory :", 2);
			ft_putendl_fd(pwd, 2);
		}
	}
}

void	cd_swap2(char *s2, char *tmp, int *i)
{
	int j;

	j = 0;
	while (s2[j] != '\0')
	{
		tmp[*i] = s2[j];
		(*i)++;
		j++;
	}
}

void	cd_swap4(char *fin, char *tmp, int *i)
{
	int		j;

	j = 0;
	while (fin[j] != '\0')
	{
		tmp[*i] = fin[j];
		(*i)++;
		j++;
	}
}

void	cd_swap(t_env *e, char *pwd, char *s1, char *s2)
{
	int		i;
	char	*tmp;
	char	*fin;

	if (ft_strstr(getvar(e, "PWD"), s1) != NULL)
	{
		tmp = (char *)malloc(sizeof(char) *
			(ft_strlen(pwd) - ft_strlen(s1)) + ft_strlen(s2));
		fin = ft_strstr(pwd, s1);
		tmp = ft_strcpy(tmp, ft_strsub(pwd, 0, ft_strstr(pwd, s1) - pwd));
		i = ft_strlen(tmp);
		fin += ft_strlen(s1);
		cd_swap2(s2, tmp, &i);
		cd_swap4(fin, tmp, &i);
		cd_swap3(tmp, pwd, e, i);
	}
	else
		cd_swap5(s1, e);
}
