/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:04:07 by maroy             #+#    #+#             */
/*   Updated: 2024/08/27 01:04:16 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int compare_name(File *a, File *b) { return ft_strcmp(a->name, b->name); }

int compare_time(File *a, File *b) {
	if (a->last_modif < b->last_modif) return 1;
	return 0;
}

void sort(File **arr, int size, int (*compare)(File *a, File *b)) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (compare(arr[i], arr[j]) > 0) {
				File *temp = arr[j];
				arr[j]     = arr[i];
				arr[i]     = temp;
			}
		}
	}
}