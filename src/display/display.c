/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:13:41 by maroy             #+#    #+#             */
/*   Updated: 2024/09/10 23:13:41 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int handle_errors(File *node) {
	if (node->type == REGULAR_FILE) {
		return 0;
	}
	if (node->error) return 0;
	return 1;
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

static void default_list(Command *cmd, File *node) {
	for (int i = 0; i < node->nb_childs; i++) {
		ls_display_file(cmd, node->childs[i], &node->len, i >= node->nb_childs);
	}
}

static void list_files(Command *cmd, File *node) {
	for (int line = 0; line < node->len.n_lines; line++) {
		for (node->len.curr_col = 0;
		     node->len.curr_col < node->len.n_cols && line + node->len.curr_col < node->nb_childs;
		     node->len.curr_col++) {
			ls_display_file(
			    cmd, node->childs[node->len.cols[node->len.curr_col].files[line]], &node->len,
			    node->len.curr_col >= node->len.n_cols - 1 || line + node->len.curr_col >= node->nb_childs - 1);
		}
		ft_printf("\n");
	}
	for (int col = 0; col < node->len.n_cols; col++) {
		free(node->len.cols[col].files);
	}
}

void announce_path(Command *cmd, File *node) {
	if (!(cmd->flags & basic_display)) return;
	bool quoted = cmd->flags & quotes;
	if (cmd->flags & basic_display) {
		ft_printf("%s%s%s:\n", quoted ? "\"" : "", node->path, quoted ? "\"" : "");
	}
}

static void get_cols_indexes(File *node) {
	for (int i = 0, col = 0, line = 0; i < node->nb_childs; i++, line++) {
		if (line >= node->len.n_lines) {
			line = 0;
			col++;
		}
		if (!line) {
			node->len.cols[col].files = ft_calloc(node->len.n_lines, sizeof(int));
			for (int k = 0; k < node->len.n_lines; k++) {
				node->len.cols[col].files[k] = -1;
			}
		}
		node->len.cols[col].files[line] = i;

		int len = ft_strlen(node->childs[i]->name);
		if (node->len.cols[col].size < len) node->len.cols[col].size = len;
	}
}

void ls_display(Command *cmd, File *node) {
	if (!handle_errors(node)) {
		free_file(node, cmd->flags & long_display);
		return;
	}

	int total_len = ((node->len.max_el + 2) * node->nb_childs) - 2;

	node->len.n_lines = round_split(total_len, cmd->cols);
	if (!node->len.n_lines) node->len.n_lines = 1;

	node->len.n_cols = round_split(node->nb_childs, node->len.n_lines);

	node->len.cols = ft_calloc(node->len.n_cols, sizeof(Col));

	sort(cmd, node->childs, node->nb_childs);

	if (cmd->flags & long_display) ft_printf("total %d\n", node->total);

	if (cmd->flags & long_display || cmd->cols <= 0) {
		cmd->def = true;
		default_list(cmd, node);
	} else {
		get_cols_indexes(node);
		list_files(cmd, node);
	}
	if (node->len.cols) free(node->len.cols);
}