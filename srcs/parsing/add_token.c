/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:57:55 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/24 17:57:55 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pipe_error(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|')
        {
            *str = ERROR_CHAR;
            return (1);
        }
        i++;
    }
    return (0);
}

void    clean_token(t_tok **tok_head, char *str)
{
    char quote;
    int i;
    int len;

    quote = '\0';
    len = ft_strlen(str);
    i = 0;
    while (i < len)
    {
        if ((str[i] == '"' || str[i] == '\'') && quote == '\0')
        {
            quote = str[i];
            ft_memmove(str + i, str + i + 1, len - i);
            len--;
        }
        else if (str[i] == quote && quote != '\0')
        {
            quote = '\0';
            ft_memmove(str + i, str + i + 1, len - i);
            len--;
        }
        else if  ((str[i] == '|' || str[i] == '<' || str[i] == '>') && quote == '\0')
        {
            newtoken_back(tok_head, ft_substr(str, 0, i), ft_strdup(K_ARG));
            newtoken_back(tok_head, c_to_str(str[i]), c_to_str(str[i]));
            ft_memmove(str, str + i + 1, len - i);
            i = 0;
            len = ft_strlen(str);
        }
        else
            i++;
    }
}






















void replace_var_env(t_tok *env, t_tok *tok)
{
	char *avant;
	char *apres;
	char *buf;

	if (tok->value[0] == '$' && tok->value[1] == '?')
	{
		free(tok->value);
		tok->value = ft_strdup(ft_itoa(exit_code));
		return ;
	}
	avant = ft_strtok(tok->value, "$");
	apres = ft_strtok(NULL, "\0");
	if (!apres)
	{
		buf = ft_getenv(env, avant);
		free(tok->value);
		tok->value = ft_strdup(buf);
	}
	else
	{
		apres = ft_getenv(env, apres);
		buf = ft_strjoin(avant, apres);
		free(tok->value);
		tok->value = ft_strdup(buf);
		free(buf);
	}
}











void    clean_token_envSAVEEEEE(t_tok *env, char *str)
{
    char quote;
    int i;
    int len;
    char *avant;
    char *apres;
    char *buf;

    quote = '\0';
    len = ft_strlen(str);
    i = 0;
    while (i < len)
    {

        if (str[i] == '$' && (quote == '\0' || quote == '"'))
        {
            printf("VAR D'ENV\n");
            avant = ft_strtok(str, "$");
            apres = ft_strtok(NULL, "\"");
            
            printf("Avant : %s\n", avant);
            printf("Apres : %s\n", apres);

            if (!apres)
            {
                printf("1\n");
                buf = ft_getenv(env, avant);
                printf("final : %s\n", buf);
            }
            else
            {
                printf("2\n");
                apres = ft_getenv(env, apres);
                buf = ft_strjoin(avant, apres);
                printf("final : %s\n", buf);
            }
        }

        if ((str[i] == '"' || str[i] == '\'') && quote == '\0')
            quote = str[i];
        else if (str[i] == quote && quote != '\0')
            quote = '\0';
        i++;
    }
}











/* LES PROBLEMES :

🐚 Minishell echo user
user
🐚 Minishell echo $user
VAR : $user
[1]    14279 segmentation fault  ./minishell
🩹 minishell git:(test)📌 ./minishell
🐚 Minishell echo $USER
VAR : $USER
��ˌUromil
🐚 Minishell echo "$USER"
VAR : $USER
�ˌUromil
🐚 Minishell echo '$USER'
VAR : $USER'
[1]    14294 segmentation fault  ./minishell
🩹 minishell git:(test)📌 ./minishell
🐚 Minishell echo "super$USER"
VAR : $USER
superromil
🐚 Minishell echo "$USER super"
VAR : $USER
��iUromil super
🐚 Minishell echo "$USER"super
VAR : $USER
��iUromilsuper
🐚 Minishell
*/



void    clean_token_env(t_tok *env, char *str)
{
    char *newStr;
    char *ptr;
    char *end;
    char *var;
    char *value;
    char    quote;
    int i;
    // Recherche de la variable d'environnement



        quote = '\0';
        ptr = str;
        while (*ptr)
        {
            if (*ptr == '$' && (quote == '\0' || quote == '"'))
            {
                end = ptr;
                i = 0;
                while (*end != '"' && *end != ' ' && *end != '\0')
                {
                    i++;
                    end++;
                }
                var = malloc(sizeof(char ) * (i + 1));
                ft_strlcpy(var, end - i, i + 1);

                // Get la var + malloc
                value = ft_getenv(env, var + 1);
                free(var);

                // Si la var existe pas, on se casse
                if (!value)
                    return;

                newStr = malloc(sizeof(char) * (ft_strlen(value) + ft_strlen(end)));

                // Copie de la partie de la chaîne avant la variable
                ft_strlcpy(newStr, str, ptr - str + 1);

                /*
                printf("VAR : %s\n", var);
                printf("newStr : %s\n", newStr);
                printf("str : %s\n", str);
                printf("ptr : %s\n", ptr);
                */

                // Cat la var
                strcat(newStr, value);

                // Cat du reste apres la var
                strcat(newStr, end);

                // str = newstr
                strcpy(str, newStr);

            }

            if ((*ptr == '"' || *ptr == '\'') && quote == '\0')
                quote = *ptr;
            else if (*ptr == quote && quote != '\0')
                quote = '\0';
            ptr++;
        }

}




void    clean_token_envSUPER(t_tok *env, char *str)
{
    char quote;
    int i;
    int y;
    int len;
    char *avant = "";
    char *apres;
    char *buf;

    quote = '\0';
    len = ft_strlen(str);
    i = 0;
    while (i < len)
    {

        if (str[i] == '$' && (quote == '\0' || quote == '"'))
        {
            y = i;
            printf("VAR D'ENV\n");

            while (ft_isalpha(str[y]))
            {
                y++;
            }

            if (!apres)
            {
                printf("1\n");
                buf = ft_getenv(env, avant);
                printf("final : %s\n", buf);
            }
            else
            {
                printf("2\n");
                apres = ft_getenv(env, apres);
                buf = ft_strjoin(avant, apres);
                printf("final : %s\n", buf);
            }
        }

        if ((str[i] == '"' || str[i] == '\'') && quote == '\0')
            quote = str[i];
        else if (str[i] == quote && quote != '\0')
            quote = '\0';
        i++;
    }
}

void    add_token(t_tok *env, t_tok **tok_head, char *str)
{
    clean_token_env(env, str);
    if (ft_strchr(str, '"') || ft_strchr(str, '\'') || ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
    {
        if (pipe_error(str))
            return ;
        while (str[0] == '|' || str[0] == '<' || str[0] == '>')
        {
            newtoken_back(tok_head, c_to_str(str[0]), c_to_str(str[0]));
            ft_memmove(str, str + 1, ft_strlen(str));
        }
        clean_token(tok_head, str);
    }
    if (*str)
        newtoken_back(tok_head, ft_strdup(str), ft_strdup(K_ARG));
}
