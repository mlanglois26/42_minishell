# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 12:56:23 by malanglo          #+#    #+#              #
#    Updated: 2024/09/19 12:57:02 by malanglo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

SRCS = 		minishell.c\
			utils/split.c\
			utils/ft.c\
			utils/ft_2.c\
			utils/free_and_clean.c\
			utils/get_next_line_utils.c\
			utils/get_next_line.c\
			utils/printf_error.c\
			parsing/1-line/get_clean_line.c\
			parsing/1-line/utils_operators.c\
			parsing/1-line/verif_operators.c\
			parsing/2-tokenize/count_tokens.c\
			parsing/2-tokenize/get_tokens.c\
			parsing/2-tokenize/quotes_count.c\
			parsing/3-expend/expend_var.c\
			parsing/3-expend/found.c\
			parsing/3-expend/lens.c\
			parsing/3-expend/utils_expend.c\
			parsing/3-expend/exp_var_helper1.c\
			parsing/3-expend/exp_var_helper2.c\
			parsing/4-del_quotes/get_clean_tokens.c\
			parsing/4-del_quotes/quote_utils.c\
			parsing/5-parse.c\
			parsing/init_env.c\
			exec/exec_cmd.c\
			exec/exec.c\
			exec/exec_helper.c\
			exec/exec_utils.c\
			exec/parent_child1.c\
			exec/parent_child2.c\
			exec/get_cmds.c\
			exec/redirection.c\
			exec/here_doc.c\
			builtins/builtins_filter1.c\
			builtins/builtins_filter2.c\
			builtins/echo.c\
			builtins/cd.c\
			builtins/pwd.c\
			builtins/export.c\
			builtins/export_helper1.c\
			builtins/export_helper2.c\
			builtins/unset.c\
			builtins/env.c\
			builtins/exit.c\
			signals/sig.c\
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     			
OBJS =		$(SRCS:.c=.o)

all: $(NAME)

$(NAME):		${OBJS}
		$(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(LDFLAGS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
