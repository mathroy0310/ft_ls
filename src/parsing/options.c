/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:16 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 14:20:03 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *long_options[]  = {"recursive",  "reverse",   "all",        "help",
                         "quote-name", "directory", "almost-all", NULL};
char  short_options[] = "lRartmQgdA";

int ambiguous_option(Arg *arg) {
	arg->error = true;
	fprintf(stderr, ERAMBIGUOUS, arg->content);
	ft_putstr_err(" possibilites: ");
	for (int i = 0; long_options[i]; i++) {
		if (!ft_strncmp(arg->content, long_options[i], ft_strlen(arg->content)))
			fprintf(stderr, " '--%s'", long_options[i]);
	}
	return 1;
}

int invalid_option(Arg *arg, int index) {
	arg->error = true;
	if (index == -1)
		fprintf(stderr, ERNOOPT, arg->content);
	else
		fprintf(stderr, ERNOOPT, &arg->content[index]);
	return 1;
}

void put_flag(Command *cmd, char flag) {
	if (flag == 'l' && !(cmd->flags & commas))
		cmd->flags |= long_display;
	else if (flag == 'R')
		cmd->flags |= recursive;
	else if (flag == 'a') {
		cmd->flags |= all;
		cmd->flags |= dotfiles;
	} else if (flag == 'r')
		cmd->flags |= reverse;
	else if (flag == 't')
		cmd->flags |= time_modif;
	else if (flag == 'h')
		cmd->flags |= help;
	else if (flag == 'm') {
		cmd->flags |= commas;
		cmd->flags &= ~long_display;
	} else if (flag == 'Q')
		cmd->flags |= quotes;
	else if (flag == 'g') {
		cmd->flags |= long_display;
		cmd->flags |= no_owner;
	} else if (flag == 'd')
		cmd->flags |= dir_only;
	else if (flag == 'A')
		cmd->flags |= dotfiles;
}

int check_long_option(Command *cmd, Arg *arg) {
	int index = -1;

	for (int i = 0; long_options[i]; i++) {
		if (!ft_strncmp(arg->content, long_options[i], ft_strlen(arg->content))) {
			if (index != -1) return ambiguous_option(arg);

			switch (i) {
			case 0:
				put_flag(cmd, 'R');
				break;
			case 1:
				put_flag(cmd, 'r');
				break;
			case 2:
				put_flag(cmd, 'a');
				break;
			case 3:
				put_flag(cmd, 'h');
				break;
			case 4:
				put_flag(cmd, 'Q');
				break;
			case 5:
				put_flag(cmd, 'd');
				break;
			case 6:
				put_flag(cmd, 'A');
				break;
			}
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