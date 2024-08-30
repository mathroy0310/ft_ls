/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:20:03 by maroy             #+#    #+#             */
/*   Updated: 2024/08/30 14:57:03 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "errors.h"
#include "libft.h"
#include <errno.h>
#include <grp.h>
#include <linux/limits.h>
#include <locale.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define DIR_COLOR "\e[1;34m"
#define LN_COLOR "\e[1;36m"
#define EX_COLOR "\e[1;32m"
#define OR_COLOR "\e[1;31m"
#define RESET "\e[0m"

#define COLOR(type)                  \
	type == DIRECTORY  ? DIR_COLOR : \
	type == SYMLINK    ? LN_COLOR :  \
	type == EXECUTABLE ? EX_COLOR :  \
	type == DEAD_LINK  ? OR_COLOR :  \
	                     ""
typedef enum {
	OPTION      = 1 << 0,
	LONG_OPTION = 1 << 1,
	ARG         = 1 << 2,
} Arg_type;

typedef enum {
	DIRECTORY,
	REGULAR_FILE,
	SYMLINK,
	DEAD_LINK,
	EXECUTABLE
} FileType;

typedef enum {
	long_display  = 1 << 0,
	recursive     = 1 << 1,
	all           = 1 << 2,
	reverse       = 1 << 3,
	time_modif    = 1 << 4,
	help          = 1 << 5,
	basic_display = 1 << 6,
	commas        = 1 << 7,
	quotes        = 1 << 8,
	no_owner      = 1 << 9,
	dir_only      = 1 << 10,
} Flag;

typedef struct {
	size_t link;
	size_t owner;
	size_t group;
	size_t size;
} Size;

typedef struct File {
	FileType      type;
	struct File **childs;

	char *path;
	char *name;

	char *error;

	int  nb_childs;
	Size size_childs;

	char     link_to[PATH_MAX];
	FileType link_type;

	time_t last_modif;
	char   permissions[11];
	char   last_modif_str[13];
	char  *nb_links;
	char  *owner;
	char  *group;
	char  *size;
	int    blocks;
	int    total;
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