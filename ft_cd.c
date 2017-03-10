/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 13:24:20 by akerkeb           #+#    #+#             */
/*   Updated: 2014/12/31 13:24:24 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_all(char **splitline)
{
	struct stat		st;

	lstat(splitline[1], &st);
	if (access(splitline[1], F_OK) != 0)
	{
		ft_putstr_fd("cd : no such file or directory :", 2);
		ft_putendl_fd(splitline[1], 2);
		return (0);
	}
	else if (!S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("cd : not a directory :", 2);
		ft_putendl_fd(splitline[1], 2);
	}
	else if (access(splitline[1], X_OK) != 0)
	{
		ft_putstr_fd("cd : permission denied :", 2);
		ft_putendl_fd(splitline[1], 2);
		return (0);
	}
	else
		ft_putendl_fd("ta le seum", 2);
	return (1);
}

char	*ft_cd_move(t_env *e, char **splitline)
{
	if (chdir(splitline[1]) == 0)
	{
		setvar(e, "OLDPWD", getvar(e, "PWD"));
		setvar(e, "PWD", getcwd(NULL, 0));
	}
	else
		check_all(splitline);
	return (0);
}

char	*ft_cd_home(t_env *e, char **splitline)
{
	char	*home;

	home = getvar(e, "HOME");
	if (chdir(home) == 0)
	{
		setvar(e, "OLDPWD", getvar(e, "PWD"));
		setvar(e, "PWD", getcwd(NULL, 0));
	}
	else
		check_all(splitline);
	return (0);
}

char	*ft_cd_back(t_env *e, char **splitline)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (chdir(getvar(e, "OLDPWD")) == 0)
	{
		setvar(e, "OLDPWD", pwd);
		setvar(e, "PWD", getcwd(NULL, 0));
	}
	else
		check_all(splitline);
	return (0);
}

void	ft_cd(t_env *e, char **splitline)
{
	if (ft_verifargv(e, splitline))
		;
	else if (splitline[2] == NULL)
		ft_cd_move(e, splitline);
	else if (splitline[3] == NULL)
		cd_swap(e, getvar(e, "PWD"), splitline[1], splitline[2]);
	else
		ft_putendl("Too much arguments");
}
