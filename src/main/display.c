/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:13:41 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 14:24:11 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int handle_errors(File *node) {
	if (node->type == REGULAR_FILE) {
		return 0;
	}
	if (node->error && node->error == NOSUCHFILE) {
		return 0;
	} else if (node->error && node->error == NOPERM) {
		fprintf(stderr, ERNOPERM, node->path);
		return 0;
	}
	return 1;
}

static void put_spaces(char *str, int max_size, int current_size) {
	while (current_size++ < max_size)
		ft_putchar(' ');
	ft_printf("%s ", str);
}

static void quoted(Command *cmd, char *str) {
	if (cmd->flags & quotes)
		ft_putchar('"');
	ft_putstr(str);
	if (cmd->flags & quotes)
		ft_putchar('"');
}

static void ls_display_file_name(Command *cmd, File *file) {
	ft_putstr(COLOR(file->type));
	quoted(cmd, file->name);
	ft_putstr(RESET);
}

void ls_display_file(Command *cmd, File *node, Size *size, bool last) {
	if (cmd->flags & long_display) {
		ft_printf("%s ", node->permissions);
		put_spaces(node->nb_links, size->link, ft_strlen(node->nb_links));
		
		if (!(cmd->flags & no_owner))
			put_spaces(node->owner, size->owner, ft_strlen(node->owner));
			
		put_spaces(node->group, size->group, ft_strlen(node->group));
		put_spaces(node->size, size->size, ft_strlen(node->size));
		
		ft_printf("%s ", node->last_modif_str);
		ls_display_file_name(cmd, node);

		if (node->type == SYMLINK || node->type == DEAD_LINK) {
			ft_putstr(" -> ");
			ft_putstr(COLOR(node->link_type));
			quoted(cmd, node->link_to);
			ft_putstr(RESET);
		}
		ft_putchar('\n');
	} else {
		ls_display_file_name(cmd, node);
		ft_putstr(last ? "\n" : cmd->flags & commas ? ", " : "  ");
	}
}

static void recursive_display(Command *cmd, File *node) {
	if (cmd->flags & reverse) {
		for (int i = node->nb_childs - 1; i >= 0; i--) {
			if (node->childs[i]->type == DIRECTORY)
				ls_display(cmd, node->childs[i]);
			else
				free_file(node->childs[i], cmd->flags & long_display);
		}
	} else {
		for (int i = 0; i < node->nb_childs; i++) {
			if (node->childs[i]->type == DIRECTORY)
				ls_display(cmd, node->childs[i]);
			else
				free_file(node->childs[i], cmd->flags & long_display);
		}
	}
}

static void list_files(Command *cmd, File *node) {
	if (cmd->flags & reverse) {
		for (int i = node->nb_childs - 1; i >= 0; i--) {
			ls_display_file(cmd, node->childs[i], &node->size_childs, i == 0);
		}
	} else {
		for (int i = 0; i < node->nb_childs; i++) {
			ls_display_file(cmd, node->childs[i], &node->size_childs, i == node->nb_childs - 1);
		}
	}
}

static void announce_path(Command *cmd, File *node) {
	bool quoted = cmd->flags & quotes;
	if (cmd->flags & basic_display) {
		ft_printf("%s%s%s:\n", quoted ? "\"" : "", node->path, quoted ? "\"" : "");
	}
}

void ls_display(Command *cmd, File *node) {
	if (!handle_errors(node)) {
		free_file(node, cmd->flags & long_display);
		return;
	}

	!cmd->displayed ? cmd->displayed = true : ft_printf("\n");

	announce_path(cmd, node);

	sort(node->childs, node->nb_childs, cmd->flags & time_modif ? compare_time : compare_name);

	if (cmd->flags & long_display) ft_printf("total %d\n", node->total);

	list_files(cmd, node);
}