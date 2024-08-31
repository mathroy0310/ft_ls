/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:04:07 by maroy             #+#    #+#             */
/*   Updated: 2024/08/31 13:57:06 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int compare_name(File *a, File *b) { return strcoll(a->name, b->name); }

int compare_time(File *a, File *b) {
	if (a->last_modif < b->last_modif) return 1;
	return 0;
}

static void swap(File **a, File **b) {
	File *temp = *a;
	*a         = *b;
	*b         = temp;
}

static int partition(File **arr, int low, int high, int (*compare)(File *a, File *b)) {
	File *pivot = arr[high];
	int   i     = low - 1;

	for (int j = low; j < high; j++) {
		if (compare(arr[j], pivot) <= 0) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

static void quicksort(File **arr, int low, int high, int (*compare)(File *a, File *b)) {
	if (low < high) {
		int pi = partition(arr, low, high, compare);
		quicksort(arr, low, pi - 1, compare);
		quicksort(arr, pi + 1, high, compare);
	}
}

void sort(File **arr, int size, int (*compare)(File *a, File *b)) {
	quicksort(arr, 0, size - 1, compare);
}