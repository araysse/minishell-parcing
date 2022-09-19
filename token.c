/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:44:46 by araysse           #+#    #+#             */
/*   Updated: 2022/09/18 11:36:35 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

token_t	*init_token(int type, char* value)
{
	token_t *token = calloc(1, sizeof(struct token_struct));
	token->type = type;
	token->value = value;

	return (token);
}