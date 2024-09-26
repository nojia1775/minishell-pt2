/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:13:34 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/26 14:30:27 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft42/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int	g_sigint_received;

typedef enum e_type
{
	ARG,
	INREDIR,
	INREDIRAPP,
	OUTREDIR,
	HEREDOC,
	CMD,
	LIM,
	OPT
}		t_type;

typedef struct s_data
{
	t_list		*env;
	t_list		*exp_var;
	char		**envv;
	char		**envp;
	char		**export;
	char		*logname;
	char		*mini;
	char		*pwd;
	char		*path;
	char		*extract_pwd;
	char		*total_setup;
	char		*str;
	long long	code;
	char		buf[1024];
	int			exit_code;
}				t_data;

typedef struct s_pipes
{
	pid_t	child1;
	pid_t	child2;
	int		fd1;
	int		fd2;
	int		flag1;
	char	*cmd1;
	char	*cmd2;
	char	**splited_cmd1;
	char	**splited_cmd2;
	char	*good_line_envp;
	char	**good_path;
	char	*good_cmd;
	int		*status;
}			t_pipes;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	int				type;
	int				nbr_pipe;
	int				code;
	int				flag;
	char			*content;
	char			**cmd_pipex;
	char			**files;
	char			**redir;
	char			*here_file;
	int				fd;
	int				fd_out;
}			t_token;

typedef struct s_global
{
	t_token	**tokens;
	t_data	*data;
	t_token	*cur;
	t_pipes	*pipes;
}		t_global;

/*-------Structures de varibales---------*/

typedef struct s_vars_1
{
	char	*good_line_envp;
	char	**good_path;
	char	*good_cmd;
}	t_vars_1;

typedef struct s_vars_2
{
	int	len;
	int	redir_flag;
	int	sv;
}	t_vars_2;

typedef struct s_vars_3
{
	char	*new_str;
	char	*nbr;
	int		i;
	int		flag;
	int		fd_temp;
}	t_vars_3;

typedef struct s_vars_4
{
	int	i;
	int	count;
	int	status;
	int	fd;
	int	nbr;
}	t_vars_4;

typedef struct s_vars_5
{
	int		files;
	int		redir;
	int		nbr_files;
	int		nbr_redir;
	t_token	*cur;
}	t_vars_5;

typedef struct s_vars_6
{
	char		buffer[1000000];
	char		*value;
	int			i;
	int			ibuf;
	int			in_single;
	int			in_double;
	long long	*code;
}	t_vars_6;

typedef struct s_vars_7
{
	char	buffer[1000000];
	int		in_double;
	int		in_single;
	int		ibuf;
	int		pipe;
	int		i;
}	t_vars_7;

typedef struct s_vars_8
{
	char	*var;
	char	*value;
	char	*result;
	char	*tmp;
	char	*ques;
	int		len;
}	t_vars_8;

/*-------Init Lobby-------*/
void			init_lobby(t_data *data);
char			*init_lobby_r(t_data *data);
void			add_minishell(t_data *data);
char			*find_logname(t_data *data);
void			find_logname2(t_data *data, int i, int j, int temp);
void			add_pwd(t_data *data);

/*-------Export-------*/
void			ft_export(t_list **env, t_list **exp_var);
void			update_env(t_list **env);
void			export_variable(t_list **env, t_list **exp_var, char *var,
					t_data *data);
void			export_variable2(t_list *current, t_list **list,
					int *flag, char *var);
void			trie_export(char **export, int i);			
void			add_declare_x(char **export, t_list *current,
					t_list **list, int *i);
void			print_export(char **export);

/*-------Env-------*/
void			stock_env(char **env, t_list **envp);
void			print_env(t_list **envp, t_list **exp_var, t_data *data);
void			update_oldpwd(t_list **env);
char			*get_actualpwd(t_list **env);
int				print_pwd(char *str, t_data *data);
void			add_back_oldpwd(int flag, char *cwd, t_list **env);
void			find_pwd(int *flag, t_list **env);

/*-------Cd-------*/
void			ft_cd(t_token *cur, t_global *global);
void			ft_cd2(int flag, t_global *global);
void			ft_cd_home(t_global *global);
void			get_home_path(t_data *data, t_list **env);

/*-------Unset-------*/
void			ft_unset(t_list **env, t_list **exp_var, char *var,
					t_data *data);
void			ft_unset2(int flag, t_list **exp_var, char *var);
/*-------Exit-------*/
int				ft_exit(t_token *cur, t_global *global);
int				ft_exit2(t_global *global, char **exit);
int				ft_no_exit(void);
int				many_arg(t_token *cur);

/*-------Ctrls-------*/
void			signal_handler(int signum);
char			*get_total_setup(t_data *data);
int				ft_count_words(const char *s, char c);

/*-------echo------*/
void			ft_echo(t_token *cur, int *fd, t_data *data, int redir_flag);

/*-------Cmds-------*/
int				setup_exe_simple_cmd(t_token *cur, t_global *global);
void			check_and_exe_cmd(t_token *cur, t_global *global, int fd);
void			ft_relative_path(char **splitted_cmd1, char **envp,
					char *cmd1, t_global *global);
char			**stock_total_env(t_list **envp, t_list **exp_var);
char			*ft_strjoin_cmd(char const *s1, char const *s2);
int				check_redirection(t_token *cur, int *fd, t_data *data);
char			*get_cmd(t_token *token);

/*-------Exec Builtins-------*/
int				is_a_builtin(char *cmd);
int				exec_builtin(t_token *cur, t_global *global, int *fd, int sv);
void			exec_redirection(char *redir, int fd, int *flag);

/*-------Pipes-------*/
void			main_pipes(t_global *global);
void			init_struct(char *argv[], int i, int argc, t_pipes *pipes);
int				pipex(t_token *cur, t_global *global, int sv);
void			init_fd1(char **argv, t_pipes *pipes);
void			init_fd2(char **argv, t_pipes *pipes, int argc);
void			child_pipes_process1(t_token *cur, t_pipes *pipes,
					char *envp[], int fd);
void			child_pipes_process2(t_token *cur, t_global *global,
					int sv, int fd);
void			ft_relative_path1(char **cmd_pipex, char **envp,
					char *cmd, t_pipes *pipes);
void			ft_relative_path2(char **cmd_pipex, char **envp,
					char *cmd, t_pipes *pipes);
int				ft_dup2_one(t_pipes *pipes, int *end);
void			init_fd2(char **argv, t_pipes *pipes, int argc);
void			ft_close_all(t_pipes *pipes);

/*-------here_doc-------*/
int				here_doc(char *limit_word, char **here_file);
int				create_temp_file(char *str, char **here_file);
char			*change_str(char *str, int i, char *new_str);
void			parse_line(int fd, char *line);
int				open_heredoc(t_token *cur, t_global *global, int sv, int i);

/*-------parsing global-------*/
int				nbr_quotes(char *str);
int				word_len(char *str);
char			*get_env_value(char *str, t_list **env,
					t_list **exp_var, long long code);
int				total_len_str(char *str, int *index_of_var,
					t_list **env, t_list **exp_var);
void			rm_space(char *str);
char			*find_var(char *str, t_list **env, t_list **exp_var);
int				conform_pipe(char *str);
int				count_pipe(char *str);
t_token			**parsing_pt2(char *input, t_global *global, int *error_flag);
t_token			**tokenisation(char *str, t_global *global, int *error_flag);
void			expand(t_token **tokens, t_global *global);
void			type_token(t_token **tokens);
void			quotes(t_token **tokens);
void			is_in_quote(int *in_single, int *in_double, char c);
void			free_tokens(t_token **tokens);
int				add_token(t_token **tokens, char *content, int nbr_pipe);
void			create_cmd_pipex(t_token **tokens);
char			**get_cmd_pipex(t_token *line);
int				files_and_redir(t_token **tokens, int *flag);
void			supp_token(t_token **tokens);
void			print_error(int error);

/*-------export parsing-------*/
void			pars_export(t_token *cur, t_global *global);
int				pars_exp_var(char *str);
int				checking_if_alpha(char *str);

/*-------Unset  parsing-------*/

void			pars_unset(t_token *cur, t_global *global);

/*-------Utils-------*/
char			*ft_strcat(char *dest, char *src);
char			*ft_str3cat(char *dest, char *src1, char *src2,
					char *get_total_setup);
char			*ft_return_strcat(char *dest, char *src, char *result);
int				ft_lstlen(t_list **lst);
void			ft_strcpy_wn(char *dest, char *src, int size);
int				ft_len_equal(char *str);
int				ft_check_equal(char *str);
void			ft_lists(t_list **env, t_list **exp_var);
void			ft_putstr_msg(char *s, int fd, char *str);
void			free_double_tabs(char **str);
char			*ft_strjoin_error(char const *s1, char const *s2);
int				ft_strlen_space(const char *str);
int				ft_strcmp(char *s1, char *s2);
int				ft_is_digit(char *str);
int				ft_check_long(char *str);
long long		ft_atoi_long(const char *nptr);
int				check_nbr(char *str, char *cmpr);
void			ft_putendl_fd(char *s, int fd);
int				check_file(char *str);
void			ft_putstr_fd_pipes(char *s, int fd, char *str);
int				ft_strlen_egal(const char *str);
int				set_interactive_signals(void);
int				set_exec_signals(t_data *data);
void			sig_exec_handler(int signum);
void			ft_simple_err(char *s, int fd);
int				ft_strlen_double_tab(char **str);
char			*get_lim(t_token *cur);
char			*question_mark(char *str, long long code);
void			supp_pipe(t_token **tokens, int len);
int				len_tokens(t_token **tokens);
int				there_is_cmd(t_token *list);
void			change_flag(int *error);
void			free_all(t_global *global);
void			free_reset_global(t_global *global);
void			ft_free_lists(t_list *env, t_list *exp_var);
int				is_redir(t_token *cur);
void			rm_token(t_token *cur);
int				loop_confirm_redir(char *input, char redir,
					char opp, int *i);
int				thereis_heredoc(t_token *token);
void			child_process_pipex(int *end, int *fd, t_global *global,
					t_token *cur);

int				set_interactive_signals_hd(void);
void			signal_handler_hd(int sig);
void			dup_infile(t_token *cur, int len, int flag);

#endif