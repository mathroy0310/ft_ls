/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:21 by maroy             #+#    #+#             */
/*   Updated: 2024/08/26 16:41:40 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void free_command(Command *cmd) {
	for (int i = 0; i < cmd->size; i++) {
		free(cmd->args[i].content);
	}
	free(cmd->args);
	free(cmd->file_system);
	free(cmd);
}

void free_file(File *file) {
	if (file->error) free(file->error);
	free(file->name);
	free(file->path);
	free(file->childs);
	free(file);
}

static void ls_display(Command *cmd, File *node) {
	if (node->type == REGULAR_FILE) {
		free_file(node);
		return;
	} if (node->error && !ft_strcmp(node->error, "ERNOSUCHFILE")) {
		free_file(node);
		return;
	} else if (node->error && !ft_strcmp(node->error, "ERNOPERM")) {
		fprintf(stderr, ERNOPERM, node->path);
		return;
	}

	if (!cmd->displayed)
		cmd->displayed = true;
	else
		ft_printf("\n");

	if (cmd->flags & basic_display)
		ft_printf("%s:\n", node->path);

	sort(node->childs, node->nb_childs, compare_name);

	if (cmd->flags & reverse) {
		for (int i = node->nb_childs - 1; i >= 0; i--) {
			if (node->childs[i]->type == DIRECTORY)
				ft_printf(DIR_COLOR);
			ft_printf("%s%s ", node->childs[i]->name, RESET);
		}
		if (node->nb_childs)
			ft_printf("\n");
		if (cmd->flags & recursive) {
			for (int i = node->nb_childs - 1; i >= 0; i--) {
				if (node->childs[i]->type == DIRECTORY)
					ls_display(cmd, node->childs[i]);
				else
					free_file(node->childs[i]);
			}
		} else {
			for (int i = node->nb_childs - 1; i >= 0; i--) {
				free_file(node->childs[i]);
			}
		}
	} else {
		for (int i = 0; i < node->nb_childs; i++) {
			if (node->childs[i]->type == DIRECTORY)
				ft_printf(DIR_COLOR);
			ft_printf("%s%s ", node->childs[i]->name, RESET);
		}
		if (node->nb_childs)
			ft_printf("\n");
		if (cmd->flags & recursive) {
			for (int i = 0; i < node->nb_childs; i++) {
				if (node->childs[i]->type == DIRECTORY)
					ls_display(cmd, node->childs[i]);
				else
					free_file(node->childs[i]);
			}	
		} else {
			for (int i = node->nb_childs - 1; i >= 0; i--) {
				free_file(node->childs[i]);
			}
		}
	}
	free_file(node);
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

	sort(cmd->file_system, cmd->nb_file, compare_name);

	bool files_in_args = false;
	for (int i = 0; i < cmd->nb_file; i++) {
		if (files_in_args) ft_printf(" ");
		if (cmd->file_system[i]->type == REGULAR_FILE) {
			ft_printf("%s", cmd->file_system[i]->path);
			files_in_args = true;
		}
	}

	if (files_in_args) ft_printf("\n\n");

	for (int i = 0; i < cmd->nb_file; i++) {
		ls_display(cmd, cmd->file_system[i]);
	}

	free_command(cmd);

	return 0;
}