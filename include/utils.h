/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:54:24 by maroy             #+#    #+#             */
/*   Updated: 2024/09/10 23:00:16 by maroy            ###   ########.fr       */
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

void sort(Command *cmd, File **arr, int size);