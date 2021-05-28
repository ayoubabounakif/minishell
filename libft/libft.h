/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:58:09 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/28 17:21:48 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *str);
size_t			ft_strnlen(const char *s, size_t maxlen);
int				tab_len(char **tab);
int				ft_isalpha(int c);
int				ft_isdigit(int i);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			ft_exit(char *msg);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *d, const char *s, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			**ft_split_first_sep(char const *s, char c);
void			*ft_malloc(size_t n);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			print_list(t_list *head);
/*
**	stupid one usage version implementation of realloc
*/
void			*ft_mem_grow(void *addr, size_t old_size, size_t new_size);
/*
**	a resizable string that can be appended to its end
**	(a char * on steroids)
*/
typedef struct s_rstr *t_rstr;

struct			s_rstr
{
	char		*data;
	int			alloc;
	int			len;
};
/*
**	rstr constructor
*/
t_rstr			rstr_create (int alloc);
/*
**	rstr destructor
*/
void			rstr_destroy (void *rs);
/*
**	rstr setter
*/
void			rstr_set (t_rstr rs, size_t index, char value);
/*
**	appending to the end of the rstr
*/
void			rstr_add (t_rstr rs, char value);
/*
**	clear rstr
*/
void			rstr_clear(t_rstr rs);

/*
**	convert str to c string
*/

char			*rstr_to_cstr(t_rstr rs);
char    		rstr_get(t_rstr rs, int index);
t_rstr			cstr_to_rstr(char *cstr);
/*
**	copy a c string to a resizble string without making
** a new resizble string in memory
*/
void			cstr_to_rstr_without_n_rs(char *src, t_rstr dst);

/*
** make a clone of a resizble string
*/
t_rstr			rstr_clone(t_rstr src);


char 			*ft_strjoin_c(char *str, char c);
char			*ft_strjoin_c_beggining(char *s, char c);

#endif
