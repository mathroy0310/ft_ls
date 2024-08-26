/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:00:33 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 16:13:18 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void pre_treatment(File *file, Command *cmd) {
	DIR *dir;

	if (!(dir = opendir(file->path))) {
		if (!ft_strcmp(strerror(errno), "Permission denied")) {
			cmd->perm_errors = clean_join(cmd->perm_errors, "ft_ls : cannot access '");
			cmd->perm_errors = clean_join(cmd->perm_errors, file->path);
			cmd->perm_errors = clean_join(cmd->perm_errors, "': Permission denied");
			cmd->perm_errors = clean_join(cmd->perm_errors, "\n");
		} else {
			fprintf(stderr, ERNOAC, file->path);
			perror("");
		}
		file->error = ft_strdup("No access");
	}
}

int ft_ls(Command *cmd, File *parent) {
	DIR           *dir;
	struct dirent *entry;

	if (!(dir = opendir(parent->path))) {
		fprintf(stderr, ERNOAC, parent->path);
		perror("");
		cmd->subdir_error = true;
		return 2;
	}

	while ((entry = readdir(dir))) {
		if (!(cmd->flags & all) && (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, "..")))
			continue;
		add_to_file_system(parent, entry);
	}

	closedir(dir);

	if (!(cmd->flags & recursive)) return 0;
	for (int i = 0; i < parent->nb_childs; i++) {
		if (parent->childs[i]->type == DIRECTORY) ft_ls(cmd, parent->childs[i]);
	}
	return 0;
}