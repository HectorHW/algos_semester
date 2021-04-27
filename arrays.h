//
// Created by hectorhw on 07.04.2021.
//

#ifndef __ARRAYS_H
#define __ARRAYS_H

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <ostream>

void fill_array(int* arr, int size);

void fill_10(int* arr, int size);

void fill_half_sorted(int* arr, int size);

void fill_half_sorted_reverse(int* arr, int size);

struct ComparableString{

    char* ptr;

    bool operator<(ComparableString& other) const{
        return std::strcmp(this->ptr, other.ptr)<0;
    }

    bool operator>(ComparableString& other) const{
        return std::strcmp(this->ptr, other.ptr)>0;
    }

    bool operator<=(ComparableString& other) const{
        return std::strcmp(this->ptr, other.ptr)<=0;
    }

    bool operator>=(ComparableString& other) const{
        return std::strcmp(this->ptr, other.ptr)>=0;
    }

    bool operator==(ComparableString& other) const{
        return std::strcmp(this->ptr, other.ptr)==0;
    }

    friend std::ostream& operator<<(std::ostream& os, ComparableString& obj);
};

void fill_string_array(ComparableString* arr, int size);



void initBlock(int size);
void freeBlock();

float get_block_avg_len();


#endif //__ARRAYS_H
