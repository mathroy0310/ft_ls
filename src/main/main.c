/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:21 by maroy             #+#    #+#             */
/*   Updated: 2024/08/26 14:07:50 by maroy            ###   ########.fr       */
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
	if (node->error && !ft_strcmp(node->error, "ERNOSUCHFILE"))
		return;
	else if (node->error && node->level && !ft_strcmp(node->error, "ERNOPERM")) {
		fprintf(stderr, ERNOPERM, node->path);
		return;
	}
	if (cmd->flags & basic_display) ft_printf("%s:\n", node->path);
	for (int i = 0; i < node->nb_childs; i++) {
		ft_printf("%s ", node->childs[i]->name);
	}
	ft_printf("\n");
	if (!(cmd->flags & recursive)) return;
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
		ft_ls(cmd, cmd->file_system[i]);
	}

	for (int i = 0; i < cmd->nb_file; i++) {
		ls_display(cmd, cmd->file_system[i]);
	}

	for (int i = 0; i < cmd->nb_file; i++) {
		if (cmd->file_system[i]->error && !ft_strcmp(cmd->file_system[i]->error, "ERNOPERM"))
			fprintf(stderr, ERNOPERM, cmd->file_system[i]->path);
	}
	free_command(cmd);

	return 0;
}