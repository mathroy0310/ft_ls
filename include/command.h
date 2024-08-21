/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:20:03 by maroy             #+#    #+#             */
/*   Updated: 2024/08/21 01:21:45 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>

typedef enum {
	OPTION = 1 << 0,
	LONG_OPTION = 1 << 1,
	ARG = 1 << 2,
	_FILE = 1 << 3,
	FOLDER = 1 << 4
} Arg_type;

typedef enum {
	list = 1 << 0,
	recursive = 1 << 1,
	all = 1 << 2,
	reverse = 1 << 3,
	time = 1 << 4
} Flag;

typedef struct {
	Arg_type type;
	char    *content;
} Arg;

typedef struct {
	Arg *args;
	Flag flags;
} Command;

#endif // COMMAND_H