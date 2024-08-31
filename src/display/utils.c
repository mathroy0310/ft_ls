/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:28:18 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 14:40:12 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void put_spaces(char *str, int max_size, int current_size) {
	while (current_size++ < max_size)
		ft_putchar(' ');
	ft_printf("%s ", str);
}

static void quoted(Command *cmd, char *str) {
	if (cmd->flags & quotes) ft_putchar('"');
	ft_putstr(str);
	if (cmd->flags & quotes) ft_putchar('"');
}

static void ls_display_file_name(Command *cmd, File *file) {
	ft_putstr(COLOR(file->type));
	quoted(cmd, file->name);
	ft_putstr(RESET);
}

void ls_display_file(Command *cmd, File *node, Size *size, bool last) {
	if (cmd->flags & long_display) {
		if (node->error == STAT) {
			ft_printf("%c???????? ? ? ? ? ? ", node->type == DIRECTORY ? 'd' : '-');
			ls_display_file_name(cmd, node);
			ft_putchar_fd('\n', 1);
			return;
		}
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