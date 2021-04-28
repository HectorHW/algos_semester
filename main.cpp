#include <cstdlib>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

#include "arrays.h"
#include "sorts.h"


typedef void (*array_function)(int*, int*, int);

typedef void(*fill_function)(int*, int);

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

    int* arr = new int[SIZE];
    int* buf = new int[SIZE];

    filler(arr, SIZE);

    for (int i=0;i<SIZE;i++){
        std::cout<<arr[i]<<" ";
    }

    std::cout<<std::endl;



    sorter(arr, buf, SIZE);

    for (int i=0;i<SIZE;i++){
        std::cout<<arr[i]<<" ";
    }

    std::cout<<std::endl;

    delete[] arr;
    delete[] buf;
}

template<class T> void test_powers(void (*filler)(T*,int),
                                   void (*sorter)(T*, T*, int), std::ofstream& out_file, int max_power=1<<21){
    for(int size = 16;size<=1<<20;size*=2){

        int* arr = new int[size];

        int test_size =  std::max(1000000/size,1000);


        auto test_result = measure_time(filler, sorter, arr, size, test_size);

        std::cout<<size<<" "<<test_size<<" "<<test_result/(double)test_size<<std::endl;

        double time = test_result/(double)test_size;

        out_file<<size<<" "<<test_size<<" "<<test_result/(double)test_size<<std::endl;

        delete[] arr;

        if(time>5e5) break;
    }
}

template<class T> int pick_sorter(int sort_method, void(**sorter)(T*,T*,int), std::string &name){
    switch (sort_method) {
        case 0:
            *sorter = bubble_sort<T>; name.append("bubble_"); break;
        case 1:
            *sorter = insertion_sort<T>; name.append("insertion_"); break;
        case 2:
            *sorter = shell_sort<T>; name.append("shell_"); break;
        case 3:
            *sorter = my_qsort<T>; name.append("myqsort_"); break;

        case 4:
            *sorter = merge_sort<T>; name.append("merge_"); break;
        case 5:
            *sorter = heap_sort<T>; name.append("heap_"); break;

        case 6:
            *sorter = builtin_qsort<T>; name.append("builtin_"); break;

        case 7:
            *sorter = fsort; name.append("fsort_"); break;

        case 8:
            *sorter = digit_sort; name.append("digitsort_"); break;

        default:
            std::cout<<"unknown sorting\n"; return 1;
    }
    return 0;
}


int pick_filler(int fill_method, fill_function &filler, std::string &name){
    switch (fill_method) {
        case 0:
            filler = fill_array; name.append("int"); break;
        case 1:
            filler = fill_10; name.append("10"); break;

        case 2:
            filler = fill_half_sorted; name.append("sorted"); break;

        case 3:
            filler = fill_half_sorted_reverse; name.append("reverse"); break;

        default:
            std::cout<<"unknown filler\n"; return 2;
    }
    return 0;
}

void test_sorters(){
    for(int sorter_id=2; sorter_id<=2; sorter_id++){
        for (int filler_id=0;filler_id<=3;filler_id++){
            array_function sorter = bubble_sort<int>;
            auto filler = fill_array;
            std::string name;

            pick_sorter(sorter_id, &sorter, name);

            pick_filler(filler_id, filler, name);

            name.append(".txt");

            test_20(filler, sorter);

            std::ofstream output_file(name);

            std::cout<<"file: "<<name<<std::endl;

            test_powers(filler, sorter, output_file);
            output_file.close();
        }
    }
}

int main(int argc, char **argv) {
    test_sorters();
    //test_20<int>(fill_10, digit_sort);
    return 0;
}
