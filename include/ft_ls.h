/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:20:03 by maroy             #+#    #+#             */
/*   Updated: 2024/08/21 01:49:10 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include <stdlib.h>
#include "errors.h"

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
	time = 1 << 4,
	help = 1 << 5,
} Flag;

typedef struct {
	int importance;
	int index;
} Error;

typedef struct {
	Arg_type type;
	char		*content;
	Error		error;
} Arg;

typedef struct {
	Arg		*args;
	int		size;
	Flag	flags;
} Command;

// apres les typedefs car besoin
#include "parsing.h"