/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:28:18 by maroy             #+#    #+#             */
/*   Updated: 2024/09/10 23:18:41 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int round_split(int a, int b) {
	if (b == 0) return 0;
	int result = a / b;
	if ((double) (a) / (double) (b) > result) result++;
	return result;
}

static void put_spaces(char *str, int max_size, int current_size) {
	while (current_size++ < max_size) {
		ft_putchar(' ');
	}
	ft_printf("%s ", str);
}

static void quoted(Command *cmd, char *str) {
	if (cmd->flags & quotes) ft_putchar('"');
	ft_putstr(str);
	if (cmd->flags & quotes) ft_putchar('"');
}

static void ls_display_file_name(Command *cmd, File *file) {
	if (!cmd->def) ft_putstr(COLOR(file->type));
	quoted(cmd, file->name);
	if (!cmd->def) ft_putstr(RESET);
}

void ls_display_file(Command *cmd, File *file, Size *size, bool last) {
	if (cmd->flags & long_display) {
		if (file->error == STAT) {
			ft_printf("%c???????? ? ? ? ? ? ", file->type == DIRECTORY ? 'd' : '-');
			ls_display_file_name(cmd, file);
			ft_putchar_fd('\n', 1);
			return;
		}
		ft_printf("%s ", file->permissions);
		put_spaces(file->nb_links, size->link, ft_strlen(file->nb_links));

		if (!(cmd->flags & no_owner))
			put_spaces(file->owner, size->owner, ft_strlen(file->owner));

		put_spaces(file->group, size->group, ft_strlen(file->group));
		put_spaces(file->size, size->size, ft_strlen(file->size));

		ft_printf("%s ", file->last_modif_str);
		ls_display_file_name(cmd, file);

		if (file->type == SYMLINK || file->type == DEAD_LINK) {
			ft_putstr(" -> ");
			if (!cmd->def) ft_putstr(COLOR(file->link_type));
			quoted(cmd, file->link_to);
			if (!cmd->def) ft_putstr(RESET);
		}
		ft_putchar('\n');
	} else {
		ls_display_file_name(cmd, file);
		if (cmd->flags & commas && !last) ft_putchar(',');
		if (!last) {
			if (!cmd->def)
				put_spaces(cmd->flags & commas ? "" : " ",
				           size->cols[size->curr_col].size, ft_strlen(file->name));
			else
				ft_printf(cmd->flags & commas ? ",\n" : "\n");
		}
	}
}