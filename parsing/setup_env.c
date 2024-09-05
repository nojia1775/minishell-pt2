/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:00:54 by almichel          #+#    #+#             */
/*   Updated: 2024/08/29 12:45:23 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_logname_size(int *j, int *tmp, t_data *data)
{
	int	i;
	int	lem;

	len = 0;
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "USER=", 5))
			break ;
		i++;
	}
	if (data->envp[i] == NULL)
		return (-1);
	while (data->envp[i][*j] && data->envp[i][*j] != '=')
		*j += 1;
	*j += 1;
	*tmp = *j;
	while (data->envp[i][*j] && data->envp[i][*j] != '\n')
	{
		*j += 1;
		len++;
	}
	*j = *tmp;
	return (len);
}

char	*find_logname(t_data *data)
{
	int	j;
	int	temp;
	int	len;

	len = 0;
	j = 0;
	if (!data->envp)
		return (NULL);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "USER=", 5) == 0)
			break ;
		i++;
	}
	len = get_logname_size(&j, &temp, data);
	if (len == -1)
		return (NULL);
	data->logname = malloc(((len + 1) * sizeof(char)));
	if (!data->logname)
		return (NULL);
	temp = 0;
	ft_strlcpy(data->logname, data->envp[i]);
	data->logname[temp] = '\0';
	return (data->logname);
}

void	add_minishell(t_data *data)
{
	int	len;

	len = ft_strlen(data->logname);
	data->mini_logname = malloc ((len + 11) * sizeof(char));
	if (!data->mini_logname)
		return ;
	data->mini = ft_strdup("@minishell ");
	data->mini_logname = ft_strcat(data->logname, data->mini);
}

void	add_pwd(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (data->pwd[i])
		i++;
	i--;
	while (i >= 0 && data->pwd[i] != '/')
		i--;
	i++;
	len = i;
	while (data->pwd[len])
		len++;
	data->extract_pwd = malloc((len + 1) * sizeof(char));
	if (!data->extract_pwd)
		return ;
	while (data->pwd[i])
	{
		data->extract_pwd[j] = data->pwd[i];
		j++;
		i++;
	}
	data->extract_pwd[j] = '\0';
}

void	get_total_setup(t_data *data)
{
	int	len;

	len = ft_strlen(data->mini_logname) + ft_strlen(data->extract_pwd);
	len = len + ft_strlen(" \u27a4 ") + 1;
	data->total_setup = malloc ((len) * sizeof(char));
	if (!data->total_setup)
		return ;
	data->total_setup = ft_str3cat(data->mini_logname,
			data->extract_pwd, " \u27a4 ");
}
