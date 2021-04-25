//
// Created by hectorhw on 07.04.2021.
//

#include "arrays.h"
#include <climits>

void fill_array(int *arr, int size) {

    for (int i=0;i<size;i++){
        arr[i] = rand()%0xffff;
    }

}

void fill_10(int *arr, int size) {
    for (int i=0;i<size;i++){
        arr[i] = rand()%10 + 1;
    }
}

void fill_half_sorted(int *arr, int size) {
    int sorted_size = size/2;

    int delta = INT_MAX/2 / sorted_size;

    arr[0] = rand()%delta;
    int i=1;
    for (;i<sorted_size;i++){
        arr[i] = arr[i-1] + rand()%delta;
    }

    for (;i<size;i++){
        arr[i] = rand();
    }
}

void fill_half_sorted_reverse(int *arr, int size){
    int sorted_size = size/2;

    int delta = INT_MAX/2 / sorted_size;

    arr[sorted_size] = rand()%delta;
    for (int i=sorted_size-1;i>=0;i--){
        arr[i] = arr[i+1] + rand()%delta;
    }

    for(int i=sorted_size+1;i<size;i++){
        arr[i] = rand();
    }
}

