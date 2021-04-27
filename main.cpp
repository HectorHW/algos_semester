#include <cstdlib>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

#include "arrays.h"
#include "sorts.h"


typedef void (*array_function)(ComparableString*, ComparableString*, int);

typedef void(*fill_function)(ComparableString*, int);

template<class T> auto measure_time(void (*filler)(T*,int),
        void (*sorter)(T*, T*, int), T* buffer, int buffer_size, int ITERATIONS=1000){

    T* tmp_array = new T[buffer_size];

    auto start_time = std::chrono::steady_clock::now();
    for(int i=0;i<ITERATIONS;i++){
        filler(buffer, buffer_size);
    }
    auto end_time = std::chrono::steady_clock::now();

    auto fill_time = std::chrono::duration_cast<std::chrono::microseconds> (end_time - start_time).count();

    start_time = std::chrono::steady_clock::now();

    for (int i=0;i<ITERATIONS;i++){
        filler(buffer, buffer_size);
        sorter(buffer, tmp_array, buffer_size);
    }

    end_time = std::chrono::steady_clock::now();

    auto sorting_time = std::chrono::duration_cast<std::chrono::microseconds> (end_time - start_time).count();

    delete[] tmp_array;

    return sorting_time - fill_time;

}

template<class T> void test_20(void (*filler)(T*,int),
                               void (*sorter)(T*, T*, int)){
    const int SIZE = 20;

    T* arr = new T[SIZE];
    T* buf = new T[SIZE];

    filler(arr, SIZE);

    print_arr(arr, SIZE);

    std::cout<<"after sorting:"<<std::endl;

    sorter(arr, buf, SIZE);

    print_arr(arr, SIZE);


    delete[] arr;
    delete[] buf;
}

template<class T> void test_powers(void (*filler)(T*,int),
                                   void (*sorter)(T*, T*, int), std::ofstream& out_file, int max_power=1<<21){
    for(int size = 16;size<=1<<20;size*=2){

        T* arr = new T[size];

        int test_size =  std::max(1000000/size,1000);


        auto test_result = measure_time<T>(filler, sorter, arr, size, test_size);

        std::cout<<size<<" "<<test_size<<" "<<test_result/(double)test_size<<std::endl;

        double time = test_result/(double)test_size;

        out_file<<size<<" "<<test_size<<" "<<test_result/(double)test_size<<std::endl;

        delete[] arr;

        if(time>5e5) break;
    }
}

int pick_sorter(int sort_method, array_function &sorter, std::string &name){
    switch (sort_method) {
        case 0:
            sorter = bubble_sort<ComparableString>; name.append("bubble_"); break;
        case 1:
            sorter = insertion_sort<ComparableString>; name.append("insertion_"); break;
        case 2:
            sorter = shell_sort<ComparableString>; name.append("shell_"); break;
        case 3:
            sorter = my_qsort<ComparableString>; name.append("myqsort_"); break;

        case 4:
            sorter = merge_sort<ComparableString>; name.append("merge_"); break;
        case 5:
            sorter = heap_sort<ComparableString>; name.append("heap_"); break;

        case 6:
            sorter = builtin_qsort<ComparableString>; name.append("builtin_"); break;

        default:
            std::cout<<"unknown sorting\n"; return 1;
    }
    return 0;
}

void test_sorters(){
    for(int sorter_id=0; sorter_id<=6; sorter_id++){

            array_function sorter = bubble_sort<ComparableString>;
            auto filler = fill_string_array;
            std::string name;

            pick_sorter(sorter_id, sorter, name);

            name.append("str.txt");

            test_20(filler, sorter);

            std::ofstream output_file(name);

            std::cout<<"file: "<<name<<std::endl;

            test_powers(filler, sorter, output_file);
            output_file.close();

    }
}

int main(int argc, char **argv) {
    initBlock(4000000); //4 mil symbols

    std::cout<<get_block_avg_len()<<std::endl;

    test_sorters();
    //test_20<int>(fill_10, digit_sort);

    freeBlock();

    return 0;
}
