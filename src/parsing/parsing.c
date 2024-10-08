/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:13 by maroy             #+#    #+#             */
/*   Updated: 2024/09/10 22:12:04 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void get_arg(Arg *curr, char *str) {
	if (str[0] == '-') {
		curr->type = OPTION;
		if (str[1] == '-') {
			curr->type |= LONG_OPTION;
			curr->content = ft_strdup(str + 2);
		} else
			curr->content = ft_strdup(str + 1);
	} else {
		curr->type    = ARG;
		curr->content = ft_strdup(str);
	}
}

Arg *parse_args(int ac, char **av) {
	Arg *result;

	result = ft_calloc((ac - 1), sizeof(Arg));
	for (int i = 1; i < ac; i++) {
		get_arg(&result[i - 1], av[i]);
	}
	return result;
}

static int get_cols() {
	struct winsize w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) return -1;
	return w.ws_col;
}

Command *init_cmd(int ac, char **av) {
	Command *result = ft_calloc(1, sizeof(Command));

	result->args = parse_args(ac, av);
	result->size = ac - 1;
	get_flags(result);

	for (int i = 0; i < result->size; i++) {
		if (result->args[i].type & ARG) result->nb_file++;
	}

	if (result->nb_file > 1 || result->flags & recursive)
		result->flags |= basic_display;

	result->cols = get_cols();

	if (result->nb_file == 0) {
		result->file_system          = malloc(sizeof(File *));
		result->file_system[0]       = ft_calloc(1, sizeof(File));
		result->file_system[0]->name = ft_strdup(".");
		result->file_system[0]->path = ft_strdup(".");
		analyze_file(result->file_system[0], result->flags & long_display);
		result->nb_file = 1;
		return result;
	}

	result->file_system = malloc(result->nb_file * sizeof(File *));

	for (int i = 0, j = 0; i < result->size; i++) {
		if (result->args[i].type & ARG) {
			result->file_system[j]       = ft_calloc(1, sizeof(File));
			result->file_system[j]->name = ft_strdup(result->args[i].content);
			result->file_system[j]->path = ft_strdup(result->args[i].content);
			analyze_file(result->file_system[j++], result->flags & long_display);
		}
	}

	return result;
}