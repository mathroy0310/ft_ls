/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:29:38 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 15:45:28 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>

void    get_flags(Command *cmd);
bool    fatal_error(Command *cmd);
void    find_last_file(Command *cmd);
Command get_cmd(int ac, char **av);