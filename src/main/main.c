/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:21 by maroy             #+#    #+#             */
/*   Updated: 2024/08/27 01:14:25 by maroy            ###   ########.fr       */
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

int main(int ac, char **av) {
	Command *cmd = init_cmd(ac, av);

	if (fatal_error(cmd)) {
		free_command(cmd);
		return 2;
	}

	for (int i = 0; i < cmd->nb_file; i++) {
		ft_ls(cmd, cmd->file_system[i]);
	}

	if (cmd->flags & time_modif)
		sort(cmd->file_system, cmd->nb_file, compare_time);
	else
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