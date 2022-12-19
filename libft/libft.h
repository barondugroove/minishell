/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:42:41 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/19 15:54:07 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_strlen(const char *s);
int		ft_strlcpy(char *dst, const char *src, int size);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strlcat(char *dst, const char *src, int size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strnstr(const char *big, const char *little, int len);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
int		ft_strspn(char *s, const char *accepts);
int		ft_strcspn(char *s, const char *accepts);
char	*ft_strtok(char *str, char *token);
void	*ft_memset(void *s, int c, int n);
void	ft_bzero(void *s, int n);
void	*ft_memcpy(void *dest, const void *src, int n);
void	*ft_memmove(void *dest, const void *src, int n);
void	*ft_calloc(int nmemb, int size);
void	*ft_memchr(const void *s, int c, int n);
int		ft_memcmp(const void *s1, const void *s2, int n);

int		ft_toupper(int c);
int		ft_tolower(int c);

int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void	*content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*** get_next_line ***/
char	*get_next_line(int fd);
char	*ft_read(char *str, int fd);
int		ft_has_n(char *s, int param);
char	*ft_substr_gnl(char *s, int start, int len);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlcat_gnl(char *dst, char *src, int size);
int		ft_strlcpy_gnl(char *dst, char *src, int size);

/*** ft_printf ***/
int		ft_printf(const char *s, ...);
int		ft_find_params(char s, va_list params);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putptr(unsigned long long ptr);
int		ft_putnbr_base(unsigned long long n, char *base);
int		ft_putnbr_u(unsigned int n);
int		ft_putstr(char *s);

#endif
