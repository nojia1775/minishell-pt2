/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_and_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:42:56 by codespace         #+#    #+#             */
/*   Updated: 2024/07/24 14:20:54 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_vars
{
    int     files;
    int     redir;
    int     pipe;
    t_token *cur;
}               t_vars;


static int  is_redir(char *str)
{
    if (!ft_strcmp(str, "<") || !ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
        return (1);
    return (0);
}

static int  count_redir_files(t_token *list)
{
    t_token *cur;
    int     count;
    
    count = 0;
    cur = list;
    while (cur)
    {
        if (!ft_strcmp(cur->content, ">") || !ft_strcmp(cur->content, ">>")
            || !ft_strcmp(cur->content, "<"))
            count++;
        cur = cur->next;
    }
    return (count);
}

static char **create_tab(int nbr)
{
    char    **tab;

    tab = (char **)malloc(sizeof(char *) * (nbr + 1));
    if (!tab)
        return (NULL);
    tab[nbr] = NULL;
    return (tab);
}

static int  add_files_redir(t_token *token, int index, char *content, int redir)
{
    t_token *cur;

    cur = token;
    while (cur->prev)
        cur = cur->prev;
    if (redir)
    {
        cur->redir[index] = ft_strdup(content);
        if (!cur->redir[index])
            return (0);
    }
    else
    {
        cur->files[index] = ft_strdup(content);
        if (!cur->files[index])
            return (0);
    }
    return (1);
}

int files_and_redir(t_token **tokens)
{
    t_vars  var;
    
    ft_memset(&var, 0, sizeof(var));
    while (tokens[var.pipe])
    {
        var.cur = tokens[var.pipe];
	var.redir = 0;
	var.files = 0;
        if (count_redir_files(var.cur))
        {
            var.cur->redir = create_tab(count_redir_files(var.cur));
            var.cur->files = create_tab(count_redir_files(var.cur));
            if (!var.cur->redir || !var.cur->files)
                return (0);
            while (var.cur)
            {
                if (is_redir(var.cur->content))
                {
                    if (!add_files_redir(var.cur, var.redir++, var.cur->content, 1))
                        return (0);
                }
                else if (var.cur->prev && is_redir(var.cur->prev->content))
                {
                    if (!add_files_redir(var.cur, var.files++, var.cur->content, 0))
                        return (0);
                }
                var.cur = var.cur->next;
            }
        }
        var.pipe++;
    }
    return (1);
}
