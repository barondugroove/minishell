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


void    clean_token_env(t_tok *env, char *str)
{
    char newStr[100];
    char *ptr;
    char *end;
    char var[20];
    char *value;
    int i;
    // Recherche de la variable d'environnement
    ptr = strstr(str, "$");
    while (ptr != NULL) {
        //on récupère le nom de la variable
        end = ptr;
        i = 0;
        while (*end != '"' && *end != ' ' && *end != '\0') {
            var[i++] = *end;
            end++;
        }
        var[i] = '\0';

        printf("VAR : %s\n", var);
        //on récupère sa valeur
        value = ft_getenv(env, var+1);

        printf("newStr : %s\n", newStr);
        // Copie de la partie de la chaîne avant la variable
        strncpy(newStr, str, ptr - str);

        // Ajout de la valeur de la variable
        strcat(newStr, value);

        // Ajout de la partie de la chaîne après la variable
        strcat(newStr, end);

        // Remplacement de la chaîne originale par la nouvelle chaîne
        strcpy(str, newStr);
        ptr = strstr(str, "$");
    }
    printf("%s\n", str);
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
