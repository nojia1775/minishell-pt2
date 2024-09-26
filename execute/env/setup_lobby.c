/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_lobby.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:00:54 by almichel          #+#    #+#             */
/*   Updated: 2024/09/26 09:10:02 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*init_lobby_r(t_data *data)
{
	data->logname = find_logname(data);
	if (!data->logname)
	{
		data->logname = malloc((16 * sizeof(char)));
		if (!data->logname)
			return (NULL);
		ft_strlcpy(data->logname, "user", 5);
	}
	add_minishell(data);
	add_pwd(data);
	data->total_setup = NULL;
	data->total_setup = get_total_setup(data);
	return (data->total_setup);
}

// Tout cette page permet de print le menu de lancement, pas
// besoin de parser je crois
char	*find_logname(t_data *data)
{
	int	i;
	int	j;
	int	temp;

	j = 0;
	i = 0;
	if (!data->envp)
		return (NULL);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "USER=", 5) == 0)
			break ;
		i++;
	}
	if (data->envp[i] == NULL)
	{
		return (NULL);
	}
	while (data->envp[i][j] && data->envp[i][j] != '=')
		j++;
	j++;
	temp = j;
	find_logname2(data, i, j, temp);
	return (data->logname);
}

void	find_logname2(t_data *data, int i, int j, int temp)
{
	int	len;

	len = 0;
	while (data->envp[i][j] && data->envp[i][j] != '\n')
	{
		len++;
		j++;
	}
	j = temp;
	data->logname = malloc(((len + 12) * sizeof(char)));
	if (!data->logname)
		return ;
	temp = 0;
	while (data->envp[i][j])
	{
		data->logname[temp] = data->envp[i][j];
		j++;
		temp++;
	}
	data->logname[temp] = '\0';
}

void	add_minishell(t_data *data)
{
	data->mini = ft_strdup("@minishell ");
	ft_strcat(data->logname, data->mini);
	free(data->mini);
}

void	add_pwd(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (data->pwd == NULL)
	{
		data->extract_pwd = NULL;
		return ;
	}
	while (data->pwd[i + 1])
		i++;
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
		data->extract_pwd[j++] = data->pwd[i++];
	data->extract_pwd[j] = '\0';
}
