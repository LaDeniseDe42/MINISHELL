/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:03:13 by akastler          #+#    #+#             */
/*   Updated: 2023/07/10 15:16:16 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdarg.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

# define MAX_INT 2147483647
# define MIN_INT -2147483648

# ifndef GOAT
#  define GOAT "\
       ⠠⠴⠶⠾⠿⠿⠿⢶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢿⣿⣆⠐⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⠿⠆⠹⠦⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⣤⣤⣀⠐⣶⣶⣶⣶⣶⣶⡀⢀⣀⣀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⢿⣿⡆⢹⡿⠻⢿⣿⣿⣷⠈⠿⠛⠁⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣴⣾⣷⣤⣉⣠⣾⣷⣦⣼⣿⣿⣿⣧⠀⠀⠀⠀⠀\n\
⠀⣶⣶⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀⠀\n\
⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀\n\
⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣛⠻⢧⣘⡷⠀⠀⠀\n\
⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⣉⠛⠿⣷⣦⣌⠁⠀⠀⠀\n\
⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣠⠘⠀⠀⢹⣿⣶⣶⠀⠀⠀⠀⠀⠀\n\
⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⢺⣿⠀⠀⠀⠘⣿⣿⡟⠀⠀⠀⠀⠀⠀\n\
⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠁⠀⠀⠀⠀⠻⡟⠃⠀⠀⠀⠀⠀⠀\n\
⠀⠛⠛⠛⠛⠛⠛⠛⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
"
# endif

# ifndef MINIGOAT
#  define MINIGOAT "\
\n\
(_(\n\
/_/'_____/)\n\
\"  |      |\n\
   |\"\"\"\"\"\"|\n\
"
# endif

typedef struct s_readed
{
	char			*readed;
	char			***parsed;
	char			***new_parsed;
	int				its_ok;
	char			**env;
	char			**export;
	int				flag;
	int				p_flag;
	int				err_code;
	struct s_redir	**re;
	struct termios	attr;
	int				term;
}		t_readed;

typedef struct s_index
{
	int	a;
	int	b;
	int	c;
	int	i;
	int	j;
}		t_index;

typedef struct s_pars
{
	char	***parsed;
	char	*for_set;
	int		flag;
	int		prev_flag;
	t_index	index;
}			t_pars;

typedef struct s_correct_path
{
	char	*path;
	char	**all_path;
	char	*cmd_path;
	char	*cmd_slash;
	int		line;
}			t_correct_path;

typedef struct s_add_export_to_env
{
	int		i;
	int		j;
	int		k;
	int		flag;
	int		ret;
	char	**buff;
}			t_add_export_to_env;

typedef struct s_un_chevron
{
	int	s_d;
	int	s_g;
	int	d_d;
	int	d_g;
	int	total;
}		t_un_chevron;

typedef struct s_pipe
{
	int		nb_cmd;
	int		pipe_fd[2];
	int		prev_pipe_read;
	pid_t	child_pid;
	int		i;
	pid_t	*pids;
}			t_pipe;

typedef struct s_core
{
	int	in_exec;
	int	err_code;
	int	history_fd;
}		t_core;

typedef struct s_redir
{
	char	*redir;
	char	*output;
}			t_redir;

typedef struct s_treat_redir
{
	char	**tb_cpy;
	int		i;
	int		z;
	int		flag;
	char	*temp;
}			t_treat_redir;

typedef struct s_treat_temp
{
	int		i;
	char	c;
	int		pirate_flag;
	char	*new;
}			t_tt;

extern t_core	g_core;

//main
void	start_minishell(t_readed *r, char **env, int argc, char **argv);
void	shlvl(t_readed *r);
void	process(t_readed *r);
void	minigoat_process_on_fire(t_readed *r);
int		continue_or_not(t_readed *r);
void	p(t_readed *r);

//init_struct
void	init_index(t_index *index);
void	init_pars(t_pars *pars);
void	init_readed(t_readed *r);
void	init_correct_path(t_correct_path *cp);
void	init_add_export_struct(t_add_export_to_env *a);

//init_struct2
void	init_ttt(t_tt *t);
void	init_treat_redir(t_treat_redir *tr, char **tb);
void	init_pipe_struct(t_pipe *p);
void	init_t_un_chevron(t_un_chevron *c);

//Parsing
char	***parsing(char *for_parse);
void	parsing_part2(t_readed *r);
void	process_char2(t_readed *r, t_index *i);

//Parsing2
t_redir	process_redir(t_readed *r, char *for_parse, t_pars *pars);
int		redir_pars(t_readed *r, int ret);
int		verif_triple_or_more(char *arg);
int		found_redir(char **line);
int		ft_count_redir(char *s);

//Parsing3
void	treat_redir(char **tb, t_readed *r, t_pars *pars);
int		anything_after_redir(char *str, int i);
void	print_redir_tb(t_redir **re);
void	reduce_ad_redir(char *tb, int *j, t_un_chevron *c, int flag);
void	ad_redir(char *tb, t_un_chevron *c);

//Parsing4
void	shit_bag(t_treat_redir *tr, t_redir *for_set);
void	while_treat_temp2(t_pars *pars, t_treat_redir *tr,
			t_redir *for_set, t_readed *r);
void	while_treat_temp(t_pars *pars, t_tt *t,
			t_redir *for_set, t_readed *r);
void	rm_quotes_redir(t_readed *r);
void	help_while_treat_temp2(t_pars *pars, t_treat_redir *tr,
			t_tt *t, t_readed *r);

//Parsing5
int		treat_temp(t_readed *r, t_pars *pars, t_treat_redir *tr, t_tt *t);
int		reduce_treat_temp(t_pars *pars, t_redir *for_set, t_readed *r, t_tt *t);
void	reduce_treat_temp2(t_treat_redir *tr, t_redir *for_set, t_tt *t);
void	reduce_treat_temp3(t_treat_redir *tr, t_tt *t);
int		reduce_else_of_if(t_redir *for_set, t_readed *r,
			t_pars *pars, t_treat_redir *tr);

//Parsing 6
void	rm_quotes_redir(t_readed *r);
char	*process_output(t_readed *r, t_index *ah);
void	process_char_redir(t_readed *r, t_index *ah, int ret, char **temp_out);
void	dol_error_redir(t_readed *r, char **temp_out, t_index *ah);
void	process_char_redir2(t_readed *r, t_index *i, char **temp_out);

//Parsing7
void	help_treat_temp2(t_tt *t, t_redir *for_set);
void	parsing_dollar(t_readed *r);
void	eternal_reduce_lines_dol(t_readed *r, t_index *i, char **str);

//CMD
void	try_this_command(t_readed *r);
void	exec_solo(t_readed *r);
int		not_fork_for_this(t_readed *r, int cmd_nb);
void	error_handler(t_readed *r, char *cmd, int error_code);
void	exec_slash(t_readed *r, int cmd_nb);

//CMD2
void	ft_exec_this(t_readed *r, int command_number);
int		ft_strncmp_pipex(const char *s1, const char *s2, size_t n);
int		redistri_jobs(t_readed *r, t_index *i, int cmd_nb);
int		set_double_input(t_readed *r, int cmd_nb, t_index *i, int fd);
int		ft_strncmp_pipex(const char *s1, const char *s2, size_t n);

//CMD3
int		exec_redir(t_readed *r, int cmd_nb, int (*base_fds)[2]);
void	i_am_not_a_normer(t_readed *r, int cmd_nbr);
void	first_while_exec_redir(t_readed *r, int cmd_nb);

//CHECK_BULTIN
int		check_builtin(t_readed *r, int cmd_nbr);
int		check_build_two(char **temp, t_readed *r, char *min);
void	help_export(t_readed *r, char **temp);

//EXIT
void	exit_the_goat(t_readed *r, int idk);
void	help_exit(t_readed *r, char **temp, long long int idk);

//PWD
int		pwd(void);

//ECHO
int		help_echo(char **temp, t_readed *r);
void	my_echo(char **args, t_readed *mini);
int		n_or_other(char *args);
char	*prep_echo(char *line);
char	*prep_echo_2(char *line);
void	help_echo_line(char **args, int i);

//EXPORT
void	export_my_goat(t_readed *r, char **temp);
void	treat_equal(t_readed *r, char *temp);
void	treat_plus_equal(t_readed *r, char *temp, int i);
void	add_export_to_env(t_readed *r, char **temp);
void	print_export(char **str, int i, int j);
void	modify_one_line(char **old_tb, int search_return, char *temp);
char	*rmquote_again(char *shit);
char	*remove_plus(char *str);
void	help_export_whith_plus(t_readed *r, char **temp,
			t_add_export_to_env *a, char *temp2);
void	add_back_line(t_readed *r, int pos, char *str, int id);
int		pos_of_first_char(char *str, char c);

//UNSET
void	help_unset(t_readed *r, char **temp);
void	unset_my_goat(t_readed *mini, char **temp);
int		check_unset_param(char **cmd_tb, int i);
void	unset_to_tb_export(t_readed *mini, char **temp, int i);
void	help_unset_tb_export(t_readed *mini, char *buf, int j);

//CD
int		help_cd(t_readed *r, char **temp);
int		sub_cd(char *path, t_readed *mini);
void	modif_cd(t_readed *mini, char **pwds);
void	cd(char *path, t_readed *mini, int flag);
void	reduce_cd(t_readed *mini, char **pwds, int flag);

//ENV
void	help_env(t_readed *r, char **temp);
void	ft_env(char **temp, t_readed *mini);
void	ft_change_env(char **replace_by, char *this);
void	ft_change_env_sub(char **replace_by, char *this);

//PIPE
int		ft_verif_pipe(t_readed *r);
void	help_verif_pipe(char *new, t_readed *r);
int		ft_start_with_pipe(char *str);
int		ft_end_with_pipe(char *str);
int		ft_flux(char *str);

//PIPE
void	do_the_pipe(t_readed *r);
void	help_pipe(t_pipe *p);
void	help_pipe_2(t_pipe *p, t_readed *r);

//Utils
int		count_quotes(char *line);
int		find_second_quote(char *line, int i, int *nb_q, int quotes);
int		char_in_quotes(char *str, int i, int flag, char c);
void	print_3d_tb(char ***tb);
void	free_3d_tb(char ***tb);

//Utils2
int		find_nb_commands(char *str, int cmd_nb, int i, int flag);
void	flag_state(char *str, int *flag, int i);
char	*add_char(char add_this, char *to_this);
int		ft_words(char *s);
void	add_args(char *str, char ***parsed, int pos);

//Utils3
char	**ft_sort_tb_alpha(char **tb);
int		ft_count_tb(char **tb);
int		ft_tb_sorted(char **tb);
char	**ft_copy_tb(char **tb);
int		ft_strcmp(const char *s1, const char *s2);

//Utils4
char	**add_quotes(char **export);
void	add_quotes_helper(int i, char **buf, char **export, char *str);
void	free_tb(char **paths);
void	ft_print_tb(char **str);
int		count_3_tb(char ***tb);

//Utils5
int		verif_after_dol(char *line, int i);
int		ft_search_env(char *str, t_readed *mini, int id);
char	*add_str(char *add_this, char *to_this);
void	rm_startnend_quotes(char **commands, int i);
char	*rm_startnend_quotes_solo(char *command);

//utils6
void	print_tb_withoutnl(char **tb);
int		ft_isnum(char *str);
char	*ft_strlow(char *str);
int		good_cara(char **temp);
char	**add_one_line(char **old_tb, char *new_line_to_add);

//Utils7
void	print_without_char(char *str, char c, char d, t_readed *mini);
int		between_char(char *nathan, int guillaume, char adrien);
int		check_3d_null(char ***tb, t_readed *r);
int		is_empty(char *str);
void	dol_error(t_readed *r, t_index *i, int id);

//Utils8
void	realign_tb_if_needed(t_readed *r);
void	is_needed(t_readed *r);
int		nb_line_not_empty(char **parsed);
int		ct_struct_redir(t_redir *re);
int		ct_struct_tb_redir(t_redir **re);

//Utils9
char	*help_gcp(t_correct_path *cp);
void	free_redirs_tb(t_redir **redir);
void	reset_fds(int base_fds[2]);
char	*give_correct_path(char *cmd, char **env);
char	*ft_give_path(char **env);

//Utils10
void	check_old_pwd(t_readed *r);
void	mini_help_error(t_readed *r, t_index *i, int cmd_nb);
void	reduce_help_exit(void);
void	error_on_redir(t_readed *r, int cmd_nb, t_index *i);
void	shlvl(t_readed *r);

//UTILS11
int		ft_putchar(int c);
int		is_space(int c);
int		char_in_quotes_whitespace(char *str, int i, int flag);

//History
void	recover_history(void);
void	history(char *line);

//SIGNAUX
void	sigint_handle(int signum);
void	sigquit_handle(int signum);
void	what_signals(void);
void	fonction_nulle(int sign);

//REDIRECTION
int		exec_single_input(t_readed *r, int cmd_nb, t_index *i);
int		exec_single_output(t_readed *r, int cmd_nb, t_index *i);
int		exec_double_output(t_readed *r, int cmd_nb, t_index *i);
int		exec_double_input(t_readed *r, int cmd_nb, t_index *i, int fd);
void	while_of_heredoc(t_readed *r, int cmd_nb, t_index *i, int fd);

//REDIRECTION2
void	help_parsing_heredoc(char *str, t_index *i, t_readed *r, char **new);
void	parsing_heredoc(char *str, int fd, t_readed *r);

#endif