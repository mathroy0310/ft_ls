/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:21 by maroy             #+#    #+#             */
/*   Updated: 2024/08/30 14:38:57 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "help.h"

static void check_return_status(Command *cmd) {
	for (int i = 0; i < cmd->nb_file; i++) {
		if (cmd->file_system[i]->error) cmd->return_status = 2;
	}
}

static void create_file_system(Command *cmd) {
	for (int i = 0; i < cmd->nb_file; i++) {
		ft_ls(cmd, cmd->file_system[i]);
	}
	check_return_status(cmd);
	sort(cmd->file_system, cmd->nb_file, cmd->flags & time_modif ? compare_time : compare_name);
}

static void list_regular_file(Command *cmd) {
	int regular_files = 0;
	for (int i = 0; i < cmd->nb_file; i++) {
		if (cmd->file_system[i]->type == REGULAR_FILE) {
			ls_display_file(cmd, cmd->file_system[i], true);
			regular_files++;
		}
	}
	if (regular_files && cmd->nb_file != regular_files) ft_printf("\n");
}

int main(int ac, char **av) {
	setlocale(LC_ALL, "");
	Command *cmd = init_cmd(ac, av);

	if (cmd->size == 1 && cmd->flags & help) {
		ft_printf(HELP_MSG);
		return 0;
	}
	if (fatal_error(cmd)) {
		ft_printf(TRY_HELP);
		return 2;
	}

	create_file_system(cmd);
	list_regular_file(cmd);

	for (int i = 0; i < cmd->nb_file; i++) {
		if (cmd->flags & dir_only)
			ls_display_file(cmd, cmd->file_system[i], i == cmd->nb_file - 1);
		else
			ls_display(cmd, cmd->file_system[i]);
	}

	return free_command(cmd);
}