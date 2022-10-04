
while ((token = lexer_next(lexer, shell->env )) != NULL)
			{
				while (token->type != token_pipe)
				{
					if (is_redirection(token))
					{
						ft_lstadd_bak(&redir, struct_redir(token, lexer, shell->env));
					}
					else
						str = struct_cmd(lexer, token, str, shell->env);
					if ((token = lexer_next(lexer, shell->env)) == NULL)
						break;
				}
				// printf("tokennnn : %s\n", token->value);
				ft_after_pipe(lexer, token, env);
				ft_lstnew(&new, redir, str);
				new->next = NULL;
				ft_lstadd_back(&cmd, new);
				redir = NULL;
				str = NULL;
			}

add_history(inpt);
			redir = NULL;
			lexer = init_lexer(inpt);
			ft_help_main(&cmd, &redir, lexer, shell->env);
			// if (g_glob[0] == 0)
			// 	ft_get_exec(shell, cmd);
			pr_struct(cmd);
			ft_free_struct(&cmd);