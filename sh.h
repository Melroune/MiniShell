/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 02:28:30 by akerkeb           #+#    #+#             */
/*   Updated: 2015/01/08 02:28:34 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "libft.h"
# include <unistd.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include "get_next_line.h"

typedef struct	s_env
{
	char		**path;
	char		**env;
	int			i;
}				t_env;

void			ft_env(t_env *e);
int				ft_change(char **splitline, t_env *e);
void			ft_addsetenv(char **splitline, t_env *e);
int				is_chekenv(t_env *e, char **splitline);
int				error_setenv(char **splitline);
int				ft_setenv(char **splitline, t_env *e);
int				ft_erase(char **splitline, t_env *e);
int				error_unsetenv(char **splitline);
int				ft_unsetenv(t_env *e, char **splitline);
void			setvar(t_env *e, char *var, char *value);
char			*getvar(t_env *e, char *var);
void			ft_putab(char **tab);
int				check_all(char **splitline);
char			*ft_cd_move(t_env *e, char **splitline);
char			*ft_cd_back(t_env *e, char **splitline);
void			ft_cd(t_env *e, char **splitline);
void			get_path(t_env *e);
char			*jointadd(char *road, char *command);
void			ft_execve(char **splitline, t_env *e);
int				tchek_sp_tab(char c);
int				is_builtins(char **splitline, t_env *e);
void			ft_ps(char **splitline, t_env *e);
int				ft_verifargv(t_env *e, char **splitline);
void			cd_swap(t_env *e, char *pwd, char *s1, char *s2);
int				ft_flnmain(char **splitline, t_env *e);
void			cd_swap3(char *tmp, char *pwd, t_env *e, int i);
void			cd_swap4(char *fin, char *tmp, int *i);
void			cd_swap(t_env *e, char *pwd, char *s1, char *s2);
void			cd_swap5(char *s1, t_env *e);
char			*ft_cd_home(t_env *e, char **splitline);
void			signal_handler(int sig);

#endif
