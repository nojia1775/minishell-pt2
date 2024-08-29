/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_and_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:42:56 by codespace         #+#    #+#             */
/*   Updated: 2024/08/28 21:20:17 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_vars
{
	int		files;
	int		redir;
	int		nbr_files;
	int		nbr_redir;
	t_token	*cur;
}		t_vars;

static int	is_redir(t_token *cur)
{
	if (cur->type != HEREDOC && cur->type != INREDIR
		&& cur->type != OUTREDIR && cur->type != INREDIRAPP)
		return (0);
	if (!ft_strcmp(cur->content, "<") || !ft_strcmp(cur->content, ">")
		|| !ft_strcmp(cur->content, ">>")
		|| !ft_strcmp(cur->content, "<<"))
		return (1);
	return (0);
}

static void	count_redir_files(t_token *list, int *redir, int *files)
{
	t_token	*cur;

	cur = list;
	while (cur)
	{
		if (is_redir(cur))
			(*redir)++;
		cur = cur->next;
	}
	cur = list;
	while (cur)
	{
		if (cur->prev && is_redir(cur->prev))
			(*files)++;
		cur = cur->next;
	}
}

static char	**create_tab(int nbr)
{
	char	**tab;

	if (nbr == 0)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!tab)
		return (NULL);
	tab[nbr] = NULL;
	return (tab);
}

static int	add_files_redir(t_token *token, int index, char *content, int redir)
{
	t_token	*cur;

	cur = token;
	while (cur->prev)
		cur = cur->prev;
	if (redir)
	{
		cur->redir[index] = ft_strdup(content);
		if (!cur->redir[index])
			return (perror("content redir\n"), 0);
	}
	else
	{
		cur->files[index] = ft_strdup(content);
		if (!cur->files[index])
			return (perror("content files\n"), 0);
	}
	return (1);
}

int	files_and_redir(t_token **tokens, int *flag)
{
	t_vars	var;
	int		i;

	i = 0;
	while (tokens[i])
	{
		ft_memset(&var, 0, sizeof(var));
		var.cur = tokens[i];
		count_redir_files(var.cur, &var.nbr_redir, &var.nbr_files);
		if (var.nbr_redir || var.nbr_files)
		{
			var.cur->redir = create_tab(var.nbr_redir);
			var.cur->files = create_tab(var.nbr_files);
			if (!var.cur->redir || !var.cur->files)
				return (change_flag(flag), printf("malloc\n"), 0);
			while (var.cur)
			{
				if (is_redir(var.cur))
				{
					if (!add_files_redir(var.cur,
							var.redir++, var.cur->content, 1))
						return (change_flag(flag), perror("add redir\n"), 0);
				}
				else if (var.cur->prev && is_redir(var.cur->prev))
				{
					if (!add_files_redir(var.cur,
							var.files++, var.cur->content, 0))
						return (change_flag(flag), perror("add files\n"), 0);
				}
				var.cur = var.cur->next;
			}
		}
		i++;
	}
	return (1);
}
