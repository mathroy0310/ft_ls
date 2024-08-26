/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:54:24 by maroy             #+#    #+#             */
/*   Updated: 2024/08/26 16:31:50 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

char *clean_join(char *origin, const char *to_join);

int compare_name(File *a, File *b);

void sort(File **arr, int size, int (*compare)(File *a, File *b));