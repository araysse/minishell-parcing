/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:06:52 by araysse           #+#    #+#             */
/*   Updated: 2022/10/12 15:35:09 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*lexer_collect_single_quot(t_lexer *lexer)
{
	char	*v;
	char	*s;

	v = ft_calloc(1, sizeof(char));
	lexer_advance(lexer);
	v[0] = '\0';
	if (lexer->c)
	{
		while (lexer->c != '\'')
		{
			if (lexer->contents[lexer->i + 1] == '\0')
				return (ft_eror(v, 1));
			s = lxr_as_str(lexer);
			free(v);
			v = malloc((ft_tstrlen(v) + ft_tstrlen(s) + 1) * sizeof(char));
			strcat(v, s);
			free (s);
			lexer_advance(lexer);
		}
	}
	else
		return (ft_eror(v, 1));
	return (v);
}

char	*ft_eror(char *s, int i)
{
	free(s);
	(void)s;
	if (i == 1)
	{
		printf("unclosed quots\n");
		g_glob[0] = 1;
		return (NULL);
	}
	if (i == 2)
	{
		printf("unispected token\n");
		return (NULL);
	}
	return (0);
}

int	valid_char(t_lexer *lexer)
{
	if (lexer->c != ' ' && lexer->c && lexer->c != '<'
		&& lexer->c != '>' && lexer->c != '|')
		return (1);
	return (0);
}

t_token	*lexer_next(t_lexer *lexer, char **env)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_skip_whitespace(lexer);
		if (lexer->c == '<')
			return (lexer_infile(lexer));
		if (lexer->c == '>')
			return (lexer_outfile(lexer));
		if (lexer->c == '|')
			return (lxr_ad_tok(lexer, init_tok(token_pipe, lxr_as_str(lexer))));
		return (lexer_collect_id(lexer, env));
	}
	return (NULL);
}
