/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:16 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 15:45:52 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *long_options[]  = {"recursive", "reverse", "all", "help", NULL};
char  short_options[] = "lRart";

int ambiguous_option(Arg *arg) {
	arg->error.importance = 3;
	fprintf(stderr, ERAMBIGUOUS, arg->content);
	ft_putstr_err(" possibilites: ");
	for (int i = 0; long_options[i]; i++) {
		if (!ft_strncmp(arg->content, long_options[i], ft_strlen(arg->content)))
			fprintf(stderr, " '--%s'", long_options[i]);
	}
	return 1;
}

int invalid_option(Arg *arg, int index) {
	arg->error.importance = 3;
	if (index == -1)
		fprintf(stderr, ERNOOPT, arg->content);
	else
		fprintf(stderr, ERNOOPT, &arg->content[index]);
	return 1;
}

void put_flag(Command *cmd, char flag) {
	if (flag == 'l')
		cmd->flags |= list;
	else if (flag == 'R')
		cmd->flags |= recursive;
	else if (flag == 'a')
		cmd->flags |= all;
	else if (flag == 'r')
		cmd->flags |= reverse;
	else if (flag == 't')
		cmd->flags |= time;
	else if (flag == 'h')
		cmd->flags |= help;
}

int check_long_option(Command *cmd, Arg *arg) {
	int index = -1;

	for (int i = 0; long_options[i]; i++) {
		if (!ft_strncmp(arg->content, long_options[i], ft_strlen(arg->content))) {
			if (index != -1) return ambiguous_option(arg);

			if (i == 0)
				put_flag(cmd, 'R');
			else if (i == 1)
				put_flag(cmd, 'r');
			else if (i == 2)
				put_flag(cmd, 'a');
			else if (i == 3)
				put_flag(cmd, 'h');

			index = i;
		}
	}
	if (index == -1) return invalid_option(arg, index);
	return 0;
}

int check_short_option(Command *cmd, Arg *arg) {
	for (int i = 0; arg->content[i]; i++) {
		if (!ft_strchr(short_options, arg->content[i]))
			return invalid_option(arg, i);
		put_flag(cmd, arg->content[i]);
	}
	return 0;
}

void get_flags(Command *cmd) {
	for (int i = 0; i < cmd->size; i++) {
		if (!(cmd->args[i].type & OPTION)) continue;
		if (cmd->args[i].type & LONG_OPTION) {
			if (check_long_option(cmd, &cmd->args[i])) return;
		} else if (check_short_option(cmd, &cmd->args[i]))
			return;
	}
}