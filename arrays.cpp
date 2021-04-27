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

std::ostream& operator<<(std::ostream &os, ComparableString& obj) {
    os<<obj.ptr;
    return os;
}


char* block;
int char_block_size;

void fill_string_array(ComparableString *arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i].ptr = block + rand()%char_block_size;
    }
}

float get_block_avg_len() {
    int nuls = 0;
    for (int i = 0;  i<char_block_size ; i++) {
        if(block[i]=='\0') nuls++;
    }
    return char_block_size / (float)nuls;
}

void initBlock(int size) {
    const int RATIO = 3; //~80 chars

    block = (char*) malloc(size+1);
    char_block_size = size;

    for (int i=0;i<size;i++){
        int r = rand()% (1 + 26*RATIO);
        if(r==0){
            block[i] = '\0';
        }else{
            block[i] = 'a' + (char)(r/RATIO + (r%RATIO!=0 ? 1 : 0) - 1);
        }

    }

    block[size] = '\0';
}

void freeBlock(){
    free(block);
}
