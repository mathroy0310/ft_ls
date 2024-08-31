/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:35:28 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 14:39:40 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define ERAMBIGUOUS "ft_ls: option '--%s' is ambiguous;"
#define ERNOOPT "ft_ls: invalid option -- '%s'\n"
#define ERNOAC "ft_ls: cannot access '%s': "
#define ERNOPERM "ft_ls: cannot open directory '%s': "
#define TRY_HELP "Try 'ft_ls --help' for more information.\n"