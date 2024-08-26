/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:52:10 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 16:03:43 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

void pre_treatment(File *file, Command *cmd);
int  ft_ls(Command *cmd, File *parent);

void add_to_file_system(File *parent, struct dirent *entry);