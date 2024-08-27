/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:00:33 by maroy             #+#    #+#             */
/*   Updated: 2024/08/27 01:19:41 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_ls(Command *cmd, File *parent) {
	DIR           *dir;
	struct dirent *entry;

	if (parent->type == REGULAR_FILE) return 0;

	if (!(dir = opendir(parent->path))) {
		if (!ft_strcmp(strerror(errno), "Permission denied"))
			parent->error = ft_strdup("ERNOPERM");
		else {
			fprintf(stderr, ERNOAC, parent->path);
			perror("");
			parent->error = ft_strdup("ERNOSUCHFILE");
		}
		cmd->return_status = 1;
		return 2;
	}

	while ((entry = readdir(dir))) {
		if (!(cmd->flags & all) && entry->d_name[0] == '.') continue;
		add_to_file_system(parent, entry);
	}

	closedir(dir);

	if (!(cmd->flags & recursive)) return 0;
	for (int i = 0; i < parent->nb_childs; i++) {
		if (parent->childs[i]->type == DIRECTORY && ft_strcmp(parent->childs[i]->name, ".")
		    && ft_strcmp(parent->childs[i]->name, "..")) {
			ft_ls(cmd, parent->childs[i]);
		}
	}
	return 0;
}