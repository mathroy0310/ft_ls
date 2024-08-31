/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:54:24 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 14:47:30 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

int  free_command(Command *cmd);
void free_file(File *file, bool long_display);
void free_childs(File *file, bool long_display);

char *clean_join(char *origin, const char *to_join);
void  analyze_file(File *file, bool long_display);

int compare_name(File *a, File *b);
int compare_time(File *a, File *b);

void sort(File **arr, int size, int (*compare)(File *a, File *b));