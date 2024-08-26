/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:21 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 16:09:50 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void free_command(Command *cmd) {
	for (int i = 0; i < cmd->size; i++) {
		free(cmd->args[i].content);
	}
	free(cmd->args);
	free(cmd->perm_errors);
}

static void ls_display(Command *cmd, File *node) {
	ft_printf("%s:\n", node->path);
	for (int i = 0; i < node->nb_childs; i++) {
		ft_printf("%s ", node->childs[i]->name);
	}
	ft_printf("\n\n");
	if (!(cmd->flags & recursive))
		return ;
	for (int i = 0; i < node->nb_childs; i++) {
		if (node->childs[i]->type == DIRECTORY)
			ls_display(cmd, node->childs[i]);
	}
}

int main(int ac, char **av) {
	Command *cmd = init_cmd(ac, av);

	if (fatal_error(cmd)) {
		free_command(cmd);
		return 2;
	}

	for (int i = 0; i < cmd->nb_file; i++) {
		pre_treatment(cmd->file_system[i], cmd);
	}

	for (int i = 0; i < cmd->nb_file; i++) {
		ft_ls(cmd, cmd->file_system[i]);
	}

	for (int i = 0; i < cmd->nb_file; i++) {
		ls_display(cmd, cmd->file_system[i]);
	}

	fprintf(stderr, "%s", cmd->perm_errors);
	free_command(cmd);

	return 0;
}