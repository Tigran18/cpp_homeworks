#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    int n;
    cout<<"Enter the size of the vector: ";
    cin>>n;
    vector<int> vec;
    for(int i=0; i<n; i++){
        vec.push_back(rand()%(n*2+1)-n);
    }
    auto merge_sort=[&](auto& merge_sort, vector<int>& vec, int left, int right, auto comparator)->void{
        if(left<right){
            int mid=(left+right)/2;
            merge_sort(merge_sort, vec, left, mid, comparator);
            merge_sort(merge_sort, vec, mid+1, right, comparator);
            vector<int> temp;
            int i = left, j = mid + 1;

            while (i <= mid && j <= right) {
                if (comparator(vec[i], vec[j])) {
                    temp.push_back(vec[i++]);
                } else {
                    temp.push_back(vec[j++]);
                }
            }
            while (i <= mid) temp.push_back(vec[i++]);
            while (j <= right) temp.push_back(vec[j++]);

            for (int k = left; k <= right; k++) {
                vec[k] = temp[k - left];
            }
        }        
    };
    merge_sort(merge_sort, vec, 0, vec.size()-1, [](int a, int b){
        return a<b;
    });
    for(auto& el : vec){
        cout<<el<<"  ";
    }
    std::cout<<"\n";
    return 0;
}