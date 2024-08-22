/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:13 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 11:01:46 by maroy            ###   ########.fr       */
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
		curr->type = ARG;
		curr->content = ft_strdup(str);
	}
}

Arg *parse_args(int ac, char **av) {
	Arg	*result;

	result = ft_calloc((ac - 1), sizeof(Arg));
	for (int i = 1; i < ac; i++) {
		get_arg(&result[i - 1], av[i]);
	}
	return result;
}

Command get_cmd(int ac, char **av) {
	Command result = {};

	result.args = parse_args(ac, av);
	result.size = ac - 1;
	result.perm_errors = ft_strdup("");
	get_flags(&result);
	for (int i = 0; i < result.size; i++) {
		if (result.args[i].type & ARG)
			result.nb_file++;
	}	
	return result;
}