/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:54:24 by maroy             #+#    #+#             */
/*   Updated: 2024/08/28 02:42:41 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

int free_command(Command *cmd);
void free_file(File *file);

void ls_display_file(Command *cmd, File *node, bool last);
void ls_display(Command *cmd, File *node);

char *clean_join(char *origin, const char *to_join);
void  analyze_file(File *file);

int compare_name(File *a, File *b);
int compare_time(File *a, File *b);

void sort(File **arr, int size, int (*compare)(File *a, File *b));