#include "quicksort.h"

void swap(Task** a, Task** b)
{
        Task* tmp = *a;
        *a = *b;
        *b = tmp;
}

int partition(Task** list, int low, int high)
{
        double pivot_duration = list[high]->duration;
        int i = low - 1; // i will track the boundary of the smallest number < pivot

        for (int j = low; j < high; ++j) {
                if (list[j]->duration < pivot_duration) {
                        ++i;
                        swap(&list[i], &list[j]);
                }
        }

        // put the pivot after the last smallest number
        swap(&list[i+1], &list[high]);

        // return index of the pivot
        return i + 1;
}

void quicksort(Task** list, int low, int high)
{
        if (low < high) {
                int pivot_index = partition(list, low, high);

                quicksort(list, low, pivot_index - 1); // left size [low ... pivot_index - 1]
                quicksort(list, pivot_index + 1, high); // rightsize [pivot_index + 1 ... high]
        }
}

// sort tasks by ascending order of task duration
void sort_tasks(Task** list, int len)
{
        int low = 0;
        int high = len - 1;
        quicksort(list, low, high);
}
