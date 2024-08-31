/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:00:33 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 14:43:26 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_ls(Command *cmd, File *parent) {
	DIR           *dir;
	struct dirent *entry;

	if (parent->type == REGULAR_FILE) return;

	if (!(dir = opendir(parent->path))) {
		if (cmd->level)
			fprintf(stderr, ERNOPERM, parent->path);
		else
			fprintf(stderr, ERNOAC, parent->path);
		perror("");
		cmd->return_status = 1;
		return;
	}

	!cmd->displayed ? cmd->displayed = true : ft_printf("\n");
	announce_path(cmd, parent);

	while ((entry = readdir(dir))) {
		if (!(cmd->flags & all)
		    && (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, "..")))
			continue;
		if (!(cmd->flags & dotfiles) && entry->d_name[0] == '.') continue;
		add_to_file_system(parent, entry, cmd->flags & long_display);
	}

	closedir(dir);

	if (!(cmd->flags & dir_only)) ls_display(cmd, parent);
	if (cmd->flags & recursive) {
		for (int i = 0; i < parent->nb_childs; i++) {
			if (parent->childs[i]->type == DIRECTORY
			    && ft_strcmp(parent->childs[i]->name, ".")
			    && ft_strcmp(parent->childs[i]->name, "..")) {
				cmd->level++;
				ft_ls(cmd, parent->childs[i]);
			}
		}
	}
	free_childs(parent, cmd->flags & long_display);
}