/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <	almichel@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:00:54 by almichel          #+#    #+#             */
/*   Updated: 2024/05/08 13:57:40 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_logname(t_data *data)
{
	int	i;
	int	j;
	int	temp;
	int	len;

	len = 0;
	j = 0;
	i = 0;
	if (!data->envp)
		return (NULL);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "USER=", 5) == 0)
			break;
		i++;
	}
	if (data->envp[i] == NULL)
		return (NULL);
	while (data->envp[i][j] && data->envp[i][j] != '=')
		j++;
	j++;
	temp = j;
	while (data->envp[i][j] && data->envp[i][j] != '\n')
	{
		len++;
		j++;
	}
	j = temp;
	data->logname = malloc(((len + 1) * sizeof(char)));
	if (!data->logname)
		return (NULL);
	temp = 0;
	while (data->envp[i][j])
	{
		data->logname[temp] = data->envp[i][j];
		j++;
		temp++;
	}	
	data->logname[temp] = '\0';
	return (data->logname);
}

void	add_minishell(t_data *data)
{
	int	len;

	len = ft_strlen(data->logname);
	data->mini_logname = malloc ((len + 11) * sizeof(char));
	if (!data->mini_logname)
		return;
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
		return;
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
		return;
	data->total_setup = ft_str3cat(data->mini_logname, data->extract_pwd, " \u27a4 ");
}

void	init_lobby(t_data *data)
{
	data->logname = find_logname(data);
	if (!data->logname)
	{
		data->logname = malloc((5 * sizeof(char)));
		if (!data->logname)
			return;
		ft_strlcpy(data->logname, "user", 5);
	}
	add_minishell(data);
	add_pwd(data);
	get_total_setup(data);
}
