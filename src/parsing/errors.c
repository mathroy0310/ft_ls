/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:18 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 14:03:22 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool fatal_error(Command *cmd) {
	bool fatal_error = false;
	for (int i = 0; i < cmd->size; i++) {
		if (cmd->args[i].error) fatal_error = true;
	}
	if (!fatal_error) return false;
	for (int i = 0; i < cmd->nb_file; i++) {
		free_file(cmd->file_system[i], cmd->flags & long_display);
	}
	free_command(cmd);
	return true;
}