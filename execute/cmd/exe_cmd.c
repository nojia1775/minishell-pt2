/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:07 by almichel          #+#    #+#             */
/*   Updated: 2024/08/08 14:10:49 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Fonction principale executent une commande simple du genre ls -l par exemple
int 	setup_exe_simple_cmd(t_token *cur, t_list **env, t_list **exp_var, t_data *data)
{
	int status;

	status = 0;
	pid_t	pid;
	int		fd;
	fd = STDOUT_FILENO;
	if (set_exec_signals(data) == -1)
		return(0);
	if (is_a_builtin(get_cmd(cur)) == 1)
	{
		if (check_redirection(cur, &fd, data) == 0)
			return (exec_builtin(cur, env, exp_var, data, fd));
	}
	pid = fork();
	if (pid == 0)
	{
		data->code = 0;
		if (check_redirection(cur ,&fd, data) == 0)
			check_and_exe_cmd(cur, env, exp_var, fd, data);
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->code = WEXITSTATUS(status);
	}
	else
		perror("fork");
	return (0);
}

// fonction qui tente l'absolut path et s' il ne s'execute pas il test le relative path(fonction en dessous)
void	check_and_exe_cmd(t_token *cur, t_list **envp, t_list **exp_var, int fd, t_data *data)
{
	char	**total_env;
	int 	len;

	len = 0;
	len = ft_strlen_double_tab(cur->redir);
	if (len != 0)
	{
		len--;
		if (ft_strcmp(cur->redir[len], ">") == 0 || ft_strcmp(cur->redir[len], ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(cur->redir[len], "<") == 0)
		{
			if(dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		close(fd);
	}
	total_env = stock_total_env(envp, exp_var);
	execve(get_cmd(cur), get_cmd_pipex(cur), total_env);
	ft_relative_path(get_cmd_pipex(cur), total_env, get_cmd(cur));
	free_double_tabs(total_env);
	data->code = 127;
	return;
}

// Fonction qui execute le relative path en testant tous les binaires de l'env
void	ft_relative_path(char **cmd_pipex, char **envp, char *cmd)
{
	char	*good_line_envp;
	char	**good_path;
	char	*good_cmd;
	int		i;

	i = 0;
	good_path = NULL;
	good_line_envp = NULL;
	good_cmd = NULL;
	if (envp != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH=", envp[i], 5) == 0)
				good_line_envp = envp[i];
			i++;
		}
		if (good_line_envp != NULL)
		{
			good_path = ft_split(good_line_envp, ':');
			i = -1;
			while (good_path[++i])
			{
				good_cmd = ft_strjoin_cmd(good_path[i], cmd);
				execve(good_cmd, cmd_pipex, envp);
				free(good_cmd);
			}
		}
	}
	if (good_line_envp != NULL)
		free_double_tabs(good_path);
	ft_putstr_msg(": command not found\n", 2, cmd);
}

//Check la redirection et agit agit en consequences
int	check_redirection(t_token *cur, int *fd, t_data *data)
{
	int	i_redir;
	int	i_files;

	i_redir = 0;
	i_files = 0;
	if (cur->redir)
	{
		while (cur->redir[i_redir])
		{
			if (ft_strcmp(">>", cur->redir[i_redir]) == 0)
			{
				*fd = open(cur->files[i_files], O_WRONLY | O_APPEND, 0644);
				if (access(cur->files[i_files], W_OK) == -1 && access(cur->files[i_files], F_OK) == 0)
				{
					ft_putstr_msg(": Permission denied\n", 2, cur->files[i_files]);
					data->code = 1;
					return (-1);
				}
				else 
				{
					*fd = open(cur->files[i_files], O_WRONLY | O_CREAT | O_APPEND, 0777);
					if (access(cur->files[i_files], R_OK) != 0)
					{
						ft_putstr_msg(": Permission denied\n", 2, cur->files[i_files]);
						data->code = 1;
					}
					data->code = 0;
				}
				i_files++;
			}
			else if (ft_strcmp(">", cur->redir[i_redir]) == 0)
			{
				*fd = open(cur->files[i_files], O_WRONLY | O_TRUNC, 0644);
				if (access(cur->files[i_files], W_OK) == -1 && access(cur->files[i_files], F_OK) == 0)
				{
					ft_putstr_msg(": Permission denied\n", 2, cur->files[i_files]);
					data->code = 1;
					return (-1);
				}
				else
				{
					*fd = open(cur->files[i_files], O_WRONLY | O_CREAT | O_TRUNC, 0777);
					if (access(cur->files[i_files], R_OK) != 0)
					{
						data->code = 1;
						ft_putstr_msg(": Permission denied\n", 2, cur->files[i_files]);
					}
					data->code = 0;
				}
				i_files++;
			}
			else if (ft_strcmp("<", cur->redir[i_redir]) == 0)
			{
				if (access(cur->files[i_files], F_OK) != 0)
				{
					ft_putstr_msg(": No such file or directory\n", 2, cur->files[i_files]);
					data->code = 1;
					return (-1);
				}
				else
				{
					*fd = open(cur->files[i_files], O_RDONLY);
					if (access(cur->files[i_files], R_OK) != 0)
					{
						ft_putstr_msg(": Permission denied\n", 2, cur->files[i_files]);
						data->code = 1;
						return (-1);
					}
					data->code = 0;
				}
				i_files++;
			}
			i_redir++;
		}
	}
	return (0);
}

// Rassemble l'env dans un double tab car execve prends comme argument un double tab (l'env)
char	**stock_total_env(t_list **envp, t_list **exp_var)
{
	int		len;
	int		i;
	t_list	*head;
	t_list	*current;
	char	**total_env;

	i = 0;
	head = *envp;
	current = *exp_var;
	len = ft_lstlen(envp) + ft_lstlen(exp_var) + 1;
	total_env = malloc(len * sizeof(char *));
	if (!total_env)
		return (NULL);
	if (envp && *envp)
	{
		while (head)
		{
			total_env[i] = ft_strdup(head->content);
			i++;
			head = head->next;
		}
	}
	if (exp_var && *exp_var)
	{
		while (current)
		{
			total_env[i] = ft_strdup(current->content);
			i++;
			current = current->next;
		}
	}
	total_env[i] = NULL;
	return (total_env);
}
