/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_and_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:42:56 by codespace         #+#    #+#             */
/*   Updated: 2024/07/22 11:13:48 by codespace        ###   ########.fr       */
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

int files_and_redir(t_token **tokens)
{
    t_vars  var;
    
    ft_bzero(&var, sizeof(var));
    while (tokens[var.pipe])
    {
        var.cur = tokens[var.pipe];
        if (count_redir_files(var.cur))
        {
            var.cur->redir = create_tab(count_redir_files(var.cur));
            var.cur->files = create_tab(count_redir_files(var.cur));
            if (!var.cur->redir || !var.cur->files)
                retunr (0);
            while (var.cur)
            {
                if (is_redir(var.cur->content))
                    var.cur->redir[var.redir++] = ft_strdup(var.cur->content);
                if (is_redir(var.cur->prev->content))
                    var.cur->files[var.files++] = ft_strdup(var.cur->content);
                var.cur = var.cur->next;
            }
        }
        var.pipe++;
    }
}
