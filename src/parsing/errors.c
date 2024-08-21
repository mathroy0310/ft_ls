/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:18 by maroy             #+#    #+#             */
/*   Updated: 2024/08/21 01:35:19 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool fatal_error(Command *cmd) {
	for (int i = 0; i < cmd->size; i++) {
		if (cmd->args[i].error.importance == 3) return true;
	}
	return false;
}