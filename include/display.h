/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:44:37 by maroy             #+#    #+#             */
/*   Updated: 2024/09/10 22:30:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_ls.h"

void announce_path(Command *cmd, File *node);
int  round_split(int a, int b);
void ls_display_file(Command *cmd, File *file, Size *size, bool last);
void ls_display(Command *cmd, File *node);