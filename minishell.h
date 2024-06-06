#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
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

typedef enum	e_type
{
	WORD,
	INREDIR,
	OUTREDIR,
	CMD,
	PIPE,
	HEREDOC
}		t_type;

typedef struct s_data
{
	char		**envp;
	char		**export;
	char		*logname;
	char		*mini;
	char		*pwd;
	char		*path;
	char		*extract_pwd;
	char		*total_setup;
	char		*str;
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

typedef struct scode
{
	long long	code;

}				t_code;

typedef struct s_input
{
	char	*intput_brut;
	char	*cmd;
	char	*cmd_opt;
	char	**args;
}	t_input;

typedef struct	s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	t_type	type;
	char	*content;
}		t_token;

/*-------Init Lobby-------*/
char			*init_lobby(t_data *data);
void			add_minishell(t_data *data);
char			*find_logname(t_data *data);
void			find_logname2(t_data *data, int i, int j, int temp);
void			add_pwd(t_data *data);

/*-------Export-------*/
void			ft_export(t_data *data, t_list **env, t_list **exp_var);
void			update_env(t_list **env);
void			export_variable(t_list **env, t_list **exp_var, char *var,
					t_code *code);
void			export_variable2(t_list *current, t_list **list, int *flag, char *var);	
void			trie_export(t_data *data, int i);			
void			add_declare_x(t_data *data, t_list *current, t_list **list, int *i);
void			print_export(t_data *data);

/*-------Env-------*/
void			stock_env(char **env, t_list **envp);
void			print_env(t_list **envp, t_list **exp_var);
void			update_oldpwd(t_list **env);
char			*get_actualpwd(t_list **env);
int				print_pwd(char *str, t_code *code);
void			add_back_oldpwd(int flag, char *cwd, t_list **env);
void			find_pwd(int *flag, t_list **env);

/*-------Cd-------*/
void			ft_cd(t_data *data, t_list **env, t_list **exp_var,
					t_code *code);
void			ft_cd2(t_code *code, int flag, t_list **env, t_data *data);
void			ft_cd_home(t_data *data, t_list **env);
void			get_home_path(t_data *data, t_list **env);
int				find_var_cd(char *path, t_list **env, t_list **exp_var);
char			*put_path_cd(char *path, t_list **env, t_list **exp_var);

/*-------Unset-------*/
void			ft_unset(t_list **env, t_list **exp_var, char *var, t_code *code);
void			ft_unset2(int flag, t_list **exp_var, char *var);
/*-------Exit-------*/
void			ft_exit(char *str, t_list **env, t_list **exp_var,
					t_code *code);
void			ft_exit2(t_code *code, char **exit);

/*-------Ctrls-------*/
void			signalHandler(int signum);
char			*get_total_setup(t_data *data);
int				ft_count_words(const char *s, char c);

/*-------echo------*/
void	ft_echo(char *str, int n_option, t_list **env, t_list **exp_var,
			int *fd, t_code *code, int flag_redir);
char			*find_echo_var(char *str, t_list **env, t_list **exp_var,
					int *flag);

/*-------Cmds-------*/
void			setup_exe_simple_cmd(char *cmd, t_list **env, t_list **exp_var,
					char *file, char *redir, t_code *code);
void			check_and_exe_cmd(char *cmd, t_list **envp, t_list **exp_var,
					int fd, char *redir,
					t_code *rl_filename_completion_desired);
void			ft_relative_path(char **splitted_cmd1, char **envp, char *cmd1);
char			**stock_total_env(t_list **envp, t_list **exp_var);
char			*ft_strjoin_cmd(char const *s1, char const *s2);
void			check_redirection(char *str, char *file, int *fd);

/*-------Pipes-------*/
void			main_pipes(int argc, char *argv[], char **envp, t_code *code, char *data_str);
void			init_struct(char *argv[], int i, int argc, t_pipes *pipes);
void			pipex(t_pipes *pipes, char **envp, t_code *code, int count);
void			init_fd1(char **argv, t_pipes *pipes);
void			init_fd2(char **argv, t_pipes *pipes, int argc);
void			child_pipes_process1(t_pipes *pipes, char *envp[]);
void			child_pipes_process2(t_pipes *pipes, char *envp[]);
void			ft_relative_path1(t_pipes *pipes, char **envp, int i);
void			ft_relative_path2(t_pipes *pipes, char **envp, int i);
int				ft_dup2_one(t_pipes *pipes, int *end);
void			init_fd2(char **argv, t_pipes *pipes, int argc);
void			ft_close_all(t_pipes *pipes);

/*-------parsing-------*/
int		parsing(char **input, t_list **env, t_list **exp_var);
char	*quotes(char *str, t_list **env, t_list **exp_var, t_token **tokens);
int		nbr_quotes(char *str);
char	*interpretation(char *str, int *index_of_var, t_list **env, t_list **exp_var);
int		*init_index_of_var(char *str);
int		word_len(char *str);
char	*get_env_value(char *str, t_list **env, t_list **exp_var);
int		total_len_str(char *str, int *index_of_var, t_list **env, t_list **exp_var);
void	rm_space(char *str);
char	*find_var(char *str, t_list **env, t_list **exp_var);
int		conform_pipe(char *str);
int		count_pipe(char *str);
int		conform_redir(char *str);
//int		add_token(t_token *list, t_type type, char *content);
//void	free_token(t_token **tokens);

//tmp parsing
t_token	**parsing_pt2(char *input, t_list **env, t_list **exp_var);
t_token	**tokenisation(char *str, t_list **env, t_list **exp_var);
void	free_tokens(t_token **tokens);
int		add_token(t_token **tokens, char *content);

/*-------Utils-------*/
char			*ft_strcat(char *dest, char *src);
char			*ft_str3cat(char *dest, char *src1, char *src2,
					char *get_total_setup);
char			*ft_return_strcat(char *dest, char *src, char *result);
int				ft_lstlen(t_list **lst);
void			ft_strcpy_wn(char *dest, char *src, int size);
int				ft_len_equal(char *str);
int				ft_check_equal(char *str);
void			ft_free_lists(t_list **env, t_list **exp_var);
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
int 			check_file(char *str);
void			print_export(t_data *data);
void			ft_putstr_fd_pipes(char *s, int fd, char *str);
int			ft_strlen_egal(const char *str);
void	is_in_quote(int *in_single, int *in_double, char c);

#endif