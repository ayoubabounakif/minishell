#include "includes/minishell.h"
#include "repl_loop.h"

#define KEY_U -73
#define KEY_D -72
#define KEY_REMOVE 127

void rstr_remove_char(t_rstr rs)
{
	rs->len--;
}

int ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int get_char()
{
	char c;
	int total;
	struct termios term, init;
	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0)
		;
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);
}

void print_repl_prompt(void)
{
	ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", 1);
	ft_putstr_fd("\x1B[32m", 1);
	ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", 1);
}

void print_rstr(int fd, t_rstr rs)
{
	int i;
	char c;

	i = 0;
	c = 0;
	while (i < rs->len)
	{
		c = rstr_get(rs, i);
		write(fd, &c, 1);
		i++;
	}
}

void termcap_remove_n_ch(int n_of_chars)
{
	int i;

	i = 0;
	while (i < n_of_chars)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);

		i++;
	}
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
}


void backspace_event_handler(t_rstr rs)
{
	if (rs->len)
	{
		rstr_remove_char(rs);
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
}

void return_key_handler(t_dlist history_list, t_rstr rs)
{
	dlist_move_cursor_to_tail(history_list);
	if (rs->len)
	{
		dlist_insert_before_cursor(history_list, rstr_clone(rs));
		rstr_clear(rs);
	}	
	rstr_clear(rs);
}

void repl_handle_keys(t_rstr *rs, t_rstr rs_tmp, char c, t_dlist dl
, t_repl_loop_data repl_data)
{
	t_rstr rs_;

	rs_ = *rs;
	if (c == KEY_D)
	{
		dlist_move_cursor_to_next(dl);
		if (dl->cursor_n != dl->sentinel)
		{
			print_rstr(1, cstr_to_rstr("random string1"));
			*rs = dl->cursor_n->value;
		}
		else
			*rs = rs_tmp;
	}
	else if (c == KEY_U)
	{
		dlist_move_cursor_to_previous(dl);
		if (dl->cursor_n != dl->sentinel)
			*rs = dl->cursor_n->value;
	}
	else if (c == KEY_REMOVE)
		backspace_event_handler(rs_);
	else if (ft_isprint(c) && c != 10)
		rstr_add(rs_, (char)c);
	else if (c == 10 && rs_->len > 0)
	{
		if (repl_data.parser_func && repl_data.exec_func)
		{
			write(1, "\n", 1);
			repl_data.exec_func(repl_data.parser_func(rstr_to_cstr(*rs)), repl_data.envp);
		}
		return_key_handler(dl, *rs);
	}
}

void repl(t_repl_loop_data repl_data)
{
	t_dlist dl;
	t_rstr rs;
	t_rstr rs_tmp;
	char c;

	tgetent(getenv("TERM"), NULL);
	dl = dlist_empty_create(rstr_destroy, NULL, NULL);
	rs = rstr_create(0);
	rs_tmp = rs;
	c = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	print_repl_prompt();
	/* while (1)
	{ */
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		while ((c = get_char()))
		{
			repl_handle_keys(&rs, rs_tmp, c, dl, repl_data);
			tputs(tgetstr("dl", NULL), 1, ft_putchar);
			print_repl_prompt();
			print_rstr(1, rs);
			c = 0;
		}
	//}
	dlist_destroy(dl);
	rstr_destroy(rs);
	rstr_destroy(rs_tmp);
}

int main(int ac, char **av, char **envp)
{
	t_repl_loop_data rld;
	rld.envp = envp;
	rld.exec_func = execute_parsed_line;
	rld.parser_func = cmd_tables_list;
	repl(rld);
	//repl(NULL, NULL, envp);
	return 0;
}