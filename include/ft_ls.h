/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:20:03 by maroy             #+#    #+#             */
/*   Updated: 2024/08/28 02:26:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "errors.h"
#include "libft.h"
#include <errno.h>
#include <grp.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define DIR_COLOR "\e[1;34m"
#define LN_COLOR "\e[1;36m"
#define RESET "\e[0m"

#define COLOR(type) \
	type == DIRECTORY ? DIR_COLOR : type == SYMLINK ? LN_COLOR : ""

typedef enum {
	OPTION      = 1 << 0,
	LONG_OPTION = 1 << 1,
	ARG         = 1 << 2,
} Arg_type;

typedef enum { DIRECTORY, REGULAR_FILE, SYMLINK, DEAD_LINK } FileType;

typedef enum {
	long_display  = 1 << 0,
	recursive     = 1 << 1,
	all           = 1 << 2,
	reverse       = 1 << 3,
	time_modif    = 1 << 4,
	help          = 1 << 5,
	basic_display = 1 << 6,
	commas        = 1 << 7,
	quotes        = 1 << 8
} Flag;

typedef struct File {
	FileType      type;
	struct File **childs;

	char *path;
	char *name;

	char *error;

	int nb_childs;

	char     link_to[PATH_MAX];
	FileType link_type;

	time_t last_modif;
	char   permissions[11];
	char   last_modif_str[13];
	int    nb_links;
	char  *owner;
	char  *group;
	int    size;
	int    blocks;
} File;

typedef struct {
	Arg_type type;
	char    *content;
	bool     error;
} Arg;

typedef struct {
	Arg   *args;
	Flag   flags;
	File **file_system;

	int  size;
	int  nb_file;
	bool subdir_error;
	bool displayed;

	int return_status;
} Command;

// apres les typedefs car besoin
#include "exec.h"
#include "parsing.h"
#include "utils.h"