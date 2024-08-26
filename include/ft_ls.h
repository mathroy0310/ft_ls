/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:20:03 by maroy             #+#    #+#             */
/*   Updated: 2024/08/26 16:24:21 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "errors.h"
#include "libft.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DIR_COLOR "\e[1;34m"
#define RESET "\e[0m"

typedef enum {
	OPTION      = 1 << 0,
	LONG_OPTION = 1 << 1,
	ARG         = 1 << 2,
} Arg_type;

typedef enum { DIRECTORY, REGULAR_FILE, SYMLINK } FileType;

typedef enum {
	list          = 1 << 0,
	recursive     = 1 << 1,
	all           = 1 << 2,
	reverse       = 1 << 3,
	time          = 1 << 4,
	help          = 1 << 5,
	basic_display = 1 << 6,
} Flag;

typedef struct {
	int importance;
	int index;
} Error;

typedef struct File {
	FileType      type;
	struct File **childs;

	char *name;
	char *path;
	char *error;

	int nb_childs;
	int level;
} File;

typedef struct {
	Arg_type type;
	char    *content;
	Error    error;
} Arg;

typedef struct {
	Arg   *args;
	Flag   flags;
	File **file_system;

	int   size;
	int   nb_file;
	int   last_file;
	bool  subdir_error;
	char *perm_errors;
	bool  file_arg;
} Command;

// apres les typedefs car besoin
#include "exec.h"
#include "parsing.h"
#include "utils.h"