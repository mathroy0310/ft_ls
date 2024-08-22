/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:52:10 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 10:56:13 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

void pre_treatment(Arg *arg, Command *cmd);
int ft_ls(const char *path, Command *cmd);