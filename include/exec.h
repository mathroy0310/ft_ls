/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:52:10 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 13:58:47 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

void ft_ls(Command *cmd, File *parent);

void calculate_size(Size *size, File *node);

void add_file_to_link(File *link);
void add_to_file_system(File *parent, struct dirent *entry, bool long_display);