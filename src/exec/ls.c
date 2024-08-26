/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:00:33 by maroy             #+#    #+#             */
/*   Updated: 2024/08/26 14:11:21 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_ls(Command *cmd, File *parent) {
	DIR           *dir;
	struct dirent *entry;

	if (!(dir = opendir(parent->path))) {
		if (!ft_strcmp(strerror(errno), "Permission denied"))
			parent->error = ft_strdup("ERNOPERM");
		else {
			fprintf(stderr, ERNOAC, parent->path);
			perror("");
			parent->error = ft_strdup("ERNOSUCHFILE");
		}
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