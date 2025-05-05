#include <iostream>
#include <vector>
#include <future>

template <typename T>
void merge(std::vector<T>& vec, size_t left, size_t mid, size_t right){
    std::vector<T> v_left(vec.begin()+left, vec.begin()+mid+1);
    std::vector<T> v_right(vec.begin()+mid+1, vec.begin()+right+1);
    size_t i=0, j=0, k=left;
    while(i<v_left.size() && j<v_right.size()){
        if(v_left[i]<=v_right[j]){
            vec[k++]=v_left[i++];
        }
        else{
            vec[k++]=v_right[j++];
        }
    }
    while(i<v_left.size()){
        vec[k++]=v_left[i++];
    }
    while(j<v_right.size()){
        vec[k++]=v_right[j++];
    }
}

template <typename T>
void merge_sort(std::vector<T>& vec, size_t left, size_t right, size_t depth = 0) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        if (depth < 3) {
            auto left_future = std::async(std::launch::async, merge_sort<T>, std::ref(vec), left, mid, depth + 1);
            auto right_future = std::async(std::launch::async, merge_sort<T>, std::ref(vec), mid + 1, right, depth + 1);
            left_future.get();
            right_future.get();
        } else {
            merge_sort(vec, left, mid, depth + 1);
            merge_sort(vec, mid + 1, right, depth + 1);
        }
        merge(vec, left, mid, right);
    }
}

int main(){
    srand(static_cast<unsigned>(time(0)));
    size_t n;
    int max, min;
    std::vector<int> vec;
    std::cout<<"Enter the size of the vector: ";
    std::cin>>n;
    std::cout<<"Enter the max and min values of the elements: ";
    std::cin>>max>>min;
    while(max<=min){
        std::cout<<"Invalid inpu! Max must be higher than min! Enter new values: ";
        std::cin>>max>>min;
    }
    for(size_t i=0; i<n; ++i){
        vec.push_back(rand()%(max-min+1)+min);
    }
    std::cout<<"Original vector: ";
    for(const auto& el : vec){
        std::cout<<el<<"  ";
    }
    std::cout<<"\n";
    merge_sort(vec, 0, vec.size()-1);
    std::cout<<"After merge sort: ";
    for(const auto& el : vec){
        std::cout<<el<<"  ";
    }
    std::cout<<std::endl;
    return 0;
}