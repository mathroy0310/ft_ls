/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:44:36 by maroy             #+#    #+#             */
/*   Updated: 2024/09/10 23:06:08 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void calculate_size(Size *size, File *node) {
	if (ft_strlen(node->nb_links) > size->link)
		size->link = ft_strlen(node->nb_links);
	if (ft_strlen(node->size) > size->size) size->size = ft_strlen(node->size);
	if (ft_strlen(node->owner) > size->owner)
		size->owner = ft_strlen(node->owner);
	if (ft_strlen(node->group) > size->group)
		size->group = ft_strlen(node->group);
}

void add_to_file_system(File *parent, struct dirent *entry, bool long_display) {
	File **new_file_system = malloc((parent->nb_childs + 1) * sizeof(File));

	for (int i = 0; i < parent->nb_childs; i++) {
		new_file_system[i] = parent->childs[i];
	}
	free(parent->childs);
	parent->childs = new_file_system;

	File *new_entry                    = ft_calloc(1, sizeof(File));
	new_file_system[parent->nb_childs] = new_entry;
	parent->nb_childs++;

	new_entry->name = ft_strdup(entry->d_name);
	new_entry->path = ft_strdup(parent->path);
	new_entry->path = clean_join(new_entry->path, "/");
	new_entry->path = clean_join(new_entry->path, new_entry->name);

	if (entry->d_type == DT_DIR)
		new_entry->type = DIRECTORY;
	else if (entry->d_type == DT_LNK)
		new_entry->type = SYMLINK;
	else
		new_entry->type = REGULAR_FILE;

	int len = ft_strlen(new_entry->name);
	if (parent->len.max_el < len) parent->len.max_el = len;

	analyze_file(new_entry, long_display);
	if (!long_display) return;
	calculate_size(&parent->len, new_entry);

	parent->total += new_entry->blocks / 2;
}
