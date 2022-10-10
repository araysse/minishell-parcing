/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:08:22 by araysse           #+#    #+#             */
/*   Updated: 2022/10/10 11:03:47 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token	*lxr_ad_tok(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_collect_id(t_lexer *lexer, char **env)
{
	char	*v;
	char	*s;

	v = ft_calloc(1, sizeof(char));
	v[0] = '\0';
	while (valid_char(lexer))
	{
		if (lexer->c != '"' && lexer->c != '\'')
			s = find_in_env2(lexer, env);
		if (lexer->c == '"')
			s = lexer_collect_string(lexer, env);
		if (lexer->c == '\'')
			s = lexer_collect_single_quot(lexer);
		v = realloc(v, (ft_tstrlen(v) + ft_tstrlen(s) + 1) * sizeof(char));
		ft_strcat(v, s);
		if (s)
			free(s);
		lexer_advance(lexer);
	}
	return (init_tok(token_word, v));
}

char	*lxr_as_str(t_lexer	*lexer)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_infile(t_lexer *lexer)
{
	char	*value;

	if (lexer->contents[lexer->i + 1] == '<')
	{
		value = malloc(3 * sizeof(char));
		value[0] = lexer->c;
		value[1] = lexer->contents[lexer->i + 1];
		value[2] = '\0';
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_tok(token_herdoc, value));
	}
	return (lxr_ad_tok(lexer, init_tok(token_infile, lxr_as_str(lexer))));
}

t_token	*lexer_outfile(t_lexer *lexer)
{
	char	*value;

	if (lexer->contents[lexer->i + 1] == '>')
	{
		value = malloc(3 * sizeof(char));
		value[0] = lexer->c;
		value[1] = lexer->contents[lexer->i + 1];
		value[2] = '\0';
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_tok (token_apend, value));
	}
	return (lxr_ad_tok(lexer, init_tok(token_outfile, lxr_as_str(lexer))));
}
