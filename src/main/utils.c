/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:54:12 by maroy             #+#    #+#             */
/*   Updated: 2024/08/22 16:14:15 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char **ft_strsjoin(char **arr, char *str) {
	int size = 0;

	while (arr[size])
		size++;
	char **result = malloc((size + 1) * sizeof(char *));
	for (int i = 0; i < size - 1; i++) {
		result[i] = arr[i];
	}
	result[size - 1] = str;
	result[size]     = NULL;
	return result;
}

char *clean_join(char *origin, const char *to_join) {
	char *tmp = origin;
	char *res = ft_strjoin(origin, to_join);
	free(tmp);
	return res;
}