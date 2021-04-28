//
// Created by hectorhw on 07.04.2021.
//

#ifndef __SORTS_H
#define __SORTS_H

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>

template<class T> void bubble_sort(T* arr, T* buf, int size);

template<class T> void insertion_sort(T*arr, T* buf, int size);

template<class T> void shell_sort(T* arr, T* buf, int size);

template<class T> void shell_fib_sort(T* arr, T* buf, int size);

template<class T> void my_qsort(T* arr, T* buf, int size);

template<class T> void merge_sort(T* arr, T* buf, int size);

template<class T> void heap_sort(T* arr, T* buf, int size);

template<class T> void digit_sort(T* arr, T* buf, int size);

template<class T> void bubble_sort(T *arr, T* buf, int size) {

    for (int i = 0; i < size; ++i) {
        for (int j=0;j<size-i-1;++j){
            if(arr[j]>arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

}

template<class T> void shell_sort(T* a, T* _buf, int n)
{
    int i, j, k;
    // Gap 'i' between index of the element to be compared, initially n/2.
    for(i = n/2; i > 0; i = i/2)
    {
        for(j = i; j < n; j++)
        {
            for(k = j-i; k >= 0; k = k-i)
            {
                // If value at higher index is greater, then break the loop.
                if(a[k+i] >= a[k])
                    break;
                    // Switch the values otherwise.
                else
                {
                    std::swap(a[k], a[k+i]);
                }
            }
        }
    }
}

template<class T> int chose_pivot(T *arr, int size){
    int middle = size/2;

    T first_elem = arr[0];
    T last_elem = arr[size-1];
    T middle_Elem = arr[middle];
    T second_greatest;
    second_greatest = std::max(last_elem, middle_Elem);
    second_greatest = std::min(std::max(std::min(last_elem, middle_Elem), first_elem), second_greatest);

    if(second_greatest==first_elem) return 0;
    if(second_greatest==last_elem) return size-1;
    return middle;

}



template<class T> void _my_qsort(T *arr, T* buf, int size, int depth) {
    //std::cout<<size<<" ";
    int i,j;
    T pivot, temp;
    if(size<2) return;
    if(size==2){
        if(arr[0]>arr[1]) std::swap(arr[0], arr[1]);
        return;
    }

    if(size<16 || depth>40){
        insertion_sort<int>(arr, buf, size); return;
    }

    //pivot = chose_pivot(arr, size);
    //pivot = 0;
    pivot = size/2;
    i = 0;
    j = size-1;

    while(i<j){
        while (arr[i]<=arr[pivot] && i<size-1)
            i++;

        while (arr[j]>arr[pivot] && j>0)
            j--;

        if(i<j){
            std::swap(arr[i], arr[j]);
        }

    }

    std::swap(arr[pivot], arr[j]);
    _my_qsort<T>(arr, buf, j,depth+1);
    _my_qsort<T>(arr+j+1, buf, size-j-1,depth+1);
}

template<class T> void my_qsort(T *arr, T* buf, int size){
    _my_qsort(arr, buf, size, 0);
}

template<class T> void builtin_qsort(T *arr, T* buf, int size){
    std::sort(arr, arr+size, [](T a, T b){
        return a<b;
    });
}

template<class T> void merge_sort(T *arr, T* buf, int size) {
    if(size<2) return;
    if(size==2){
        if(arr[0]>arr[1]) std::swap(arr[0], arr[1]); return;
    }
    int half = size/2;
    merge_sort(arr, buf, half);
    merge_sort(arr+half, buf+half, size - half);
    int i = 0;
    int j = half;

    for(int step=0;step<size;step++){
        if((j==size) || ((i<half) && (arr[i]<arr[j]))){
            //записываем из левого
            buf[step] = arr[i]; i++;
        }else{
            //записываем из правого
            buf[step] = arr[j]; j++;
        }
    }

    memcpy(
            arr, buf, sizeof (int) *size
            );

}

template<class T> static void heapify(T arr[], int n, int i) {
    int max = i; //Initialize max as root
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    //If left child is greater than root
    if (leftChild < n && arr[leftChild] > arr[max])
        max = leftChild;

    //If right child is greater than max
    if (rightChild < n && arr[rightChild] > arr[max])
        max = rightChild;

    //If max is not root
    if (max != i) {
        std::swap(arr[i], arr[max]);
        //heapify the affected sub-tree recursively
        heapify(arr, n, max);
    }
}

template<class T> void heap_sort(T *arr, T* buf, int n) {
    //Rearrange array (building heap)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    //Extract elements from heap one by one
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]); //Current root moved to the end

        heapify(arr, i, 0); //calling max heapify on the heap reduced
    }
}



template<class T> void __heap_sort(T *arr, T* buf, int size) {
    int i,c;
    for(i=0;i<size;i++){
        c = i;
        do{
            int root = (c-1)/2;
            if(arr[root]<arr[c]){
                std::swap(arr[root], arr[c]);
            }
            c = root;
        } while(c!=0);
    }

    for(i=size-1;i>=0;i--){
        std::swap(arr[0], arr[i]);
        int root = 0;
        do{
            c = 2*root+1;
            if(arr[c] < arr[c+1] && c<i-1) c++;

            if(arr[root]<arr[c] && c<i) std::swap(arr[root], arr[c]);
            root = c;
        } while (c<i);

    }

}

template<class T>
void insertion_sort(T *arr, T *buf, int size) {
    for (int i=0;i<size;i++){
        int j = i-1;
        while(j>=0 && arr[j]>arr[j+1]){
            std::swap(arr[j], arr[j+1]);
            j--;
        }
    }
}

static int max_idx(const int* arr, int size){
    int res = 0;
    for(int i=1;i<size;i++){
        if(arr[i]>arr[res]) res = i;
    }
    return res;
}

static void _sort_digit(int* arr, int* buf, int size, int digit_power){
    int count[10] = {0};
    for (int i = 0; i < size; ++i) {
        count[(arr[i]/digit_power)%10]++;
    }
    for(int i=1;i<10;i++){
        count[i]+=count[i-1]; //индесы из размеров
    }

    for (int i = size-1; i >=0 ; --i) { //пройдёмся с конца, тогда можно будет трогать индексы справа
        buf[count[(arr[i]/digit_power)%10]-1] = arr[i];
        count[(arr[i]/digit_power)%10]--;
    }

    memcpy(arr, buf, sizeof (int)*size);
}


void digit_sort(int *arr, int* buf, int size) {
    int max = arr[max_idx(arr, size)];
    for (int i = 1; i<=max; i*=10) {
        _sort_digit(arr, buf, size, i);
    }
}

std::vector<int> fibs;

template<class T> void shell_fib_sort(T *arr, int size) {

    if(fibs.empty()){
        fibs.push_back(1);
        fibs.push_back(2);
    }

    while(fibs.end()[-1] < size){
        fibs.push_back(fibs.end()[-1] + fibs.end()[-2]);
    }

    int d_idx = 0;

    while (d_idx< fibs.size()-1 && fibs[d_idx]<size){
        d_idx++;
    }

    for (; d_idx >=0 ; d_idx--) {
        int d = fibs[d_idx];
        for(int i=0;i<size;i++){
            for(int j =i+d;j<size;j+=d ){
                if(arr[i]>arr[j]) std::swap(arr[i], arr[j]);
            }
        }
    }
}

struct Stack{
public:
    static int next_idx;
    int* begin;
    int* next;
    int capacity;

    int idx;
    Stack(){
        next = begin = nullptr;
        capacity = 0;
        idx = next_idx++;
    }

    void make_room(int size){
        if(capacity<size){
            long offset = next - begin;

            begin = (int*)(realloc(begin, size * (sizeof(int))));
            //std::cout<<"allocated "<<idx<<" with size "<<size<<std::endl;
            next = begin + offset;
            capacity = size;
        }
    }

    void push(int value){
        *(this->next) = value;
        this->next++;
    }

    void reset(){
        this->next = this->begin;
    }

    ~Stack(){
        //std::cout<<"freed "<<idx<<std::endl;
        free(begin);
    }

};
int Stack::next_idx = 0;

void print_arr(int* arr, int size){
    for(int i=0;i<size;i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}

static void f_count_sort(int* arr, int size){
    int bins[16]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int base = arr[0] - arr[0]%16;
    for (int i=0;i<size;i++){
        bins[arr[i]%16]++;
    }
    int j=0;
    for (int i = 0; i < 16; ++i) {
        while (bins[i]>0){
            arr[j] = base + i;
            j++;
            bins[i]--;
        }
    }
}

static void _fsort(int* arr, int size, int index, Stack stacks[16]){
    if(size<=1) return;
    if(size==2){
        if(arr[0]>arr[1]) std::swap(arr[0], arr[1]); return;
    }
    if(size<32){
        insertion_sort<int>(arr, nullptr, size);
    }

    if(index==0){
        f_count_sort(arr, size);
        return;
    }
    for (int i=0;i<16;i++){
        stacks[i].reset();
    }

    int b2 = index*4;
    int b1 = 0xf <<b2;

    for(int i=0;i<size;i++){
        int b_idx = (arr[i]&b1)>>b2;
        stacks[b_idx].push(arr[i]);
    }
    int bin_sizes[16];
    int running_sum = 0;
    for (int i=0;i<16;i++){
        bin_sizes[i] = stacks[i].next - stacks[i].begin;
        memcpy(arr+running_sum, stacks[i].begin, bin_sizes[i]*sizeof (int));
        running_sum+=bin_sizes[i];
    }

    running_sum=0;
    for(int i=0;i<16;i++){
        _fsort(arr+running_sum, bin_sizes[i], index-1, stacks);
        running_sum+=bin_sizes[i];
    }

}

Stack stacks[16];

void fsort(int* arr, int* buf, int size){

    for(int i=0;i<16;i++){
        stacks[i].make_room(size);
    }

    _fsort(arr, size, sizeof(int)*2 - 1, stacks);
}

#endif //__SORTS_H
