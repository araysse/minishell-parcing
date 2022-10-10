/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_main1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:57:43 by araysse           #+#    #+#             */
/*   Updated: 2022/10/10 11:13:42 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_after_pipe1(t_lexer *lexer, t_token *token, char **env)
{
	t_token	*tok3;
	t_lexer	*lexer3;

	lexer3 = init_lexer(lexer->contents);
	tok3 = lexer_next(lexer3, env);
	if (token)
		return (help_parce(&tok3, lexer3));
	free(tok3->value);
	free(tok3);
	free(lexer3);
	return (0);
}

int	help_parce(t_token **tok3, t_lexer *lexer3)
{
	if ((*tok3)->e_type == token_pipe)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		g_glob[0] = 1;
		g_glob[1] = 258;
		free((*tok3)->value);
		free((*tok3));
		free(lexer3);
		return (1);
	}
	free((*tok3)->value);
	free((*tok3));
	free(lexer3);
	return (0);
}

void	ft_after_pipe(t_lexer *lexer, t_token *token, char **env)
{
	t_token	*tok2;
	t_lexer	*lexer2;
	int		i;

	i = 0;
	if (ft_after_pipe1(lexer, token, env) == 1)
		return ;
	lexer2 = init_lexer(lexer->contents);
	while (lexer2->i < lexer->i)
	{
		tok2 = lexer_next(lexer2, env);
		free(tok2->value);
		free (tok2);
	}
	if (token != NULL)
		after_pipe(&tok2, lexer2, token, env);
	free (lexer2);
}

void	after_pipe(t_token **tok2, t_lexer *lexer2, t_token *token, char **env)
{
	(*tok2) = lexer_next(lexer2, env);
	if ((token->e_type == token_pipe && !(*tok2))
		|| (*tok2)->e_type == token_pipe)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		g_glob[0] = 1;
		g_glob[1] = 258;
	}
	if (*tok2)
		free((*tok2)->value);
	free(*tok2);
}

void	ft_free2(t_redir **redir)
{
	int		i;

	i = 0;
	while (*redir)
	{
		free((*redir)->type);
		free((*redir)->value);
		(*redir) = (*redir)->next;
	}
	free ((*redir));
}
