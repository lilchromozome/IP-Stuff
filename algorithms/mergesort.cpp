#include <iostream>
#include <vector>
#include <cassert>

void sort(std::vector<int>& vec);
void printv(std::vector<int> vec);

int main(){
    std::vector< int > vec;
  size_t count;

  std::cout << "Enter the count: ";

  // PART 2 TO DO: read in the count of random numbers from the standard input.

  std::cin >> count;

  // PART 3 TO DO: Make the "vec" vector store "count" random values

  for(size_t i = 0; i < count; i++){
    vec.push_back(random() % count);
  }
  printv(vec);
  sort( vec );
  printv(vec);

  for( size_t i=1 ; i<vec.size() ; i++ ) assert( vec[i-1]<=vec[i] );

  return 0;
}

void merge(std::vector<int>& vec, int left, int middle, int right) {
    int left_size = middle - left + 1;
    int right_size = right - middle;

    std::vector<int> left_vec(left_size);
    std::vector<int> right_vec(right_size);

    for (int i = 0; i < left_size; i++) {
        left_vec[i] = vec[left + i];
    }

    for (int i = 0; i < right_size; i++) {
        right_vec[i] = vec[middle + 1 + i];
    }

    int left_index = 0;
    int right_index = 0;
    int merge_index = left;

    while (left_index < left_size && right_index < right_size) {
        if (left_vec[left_index] <= right_vec[right_index]) {
            vec[merge_index] = left_vec[left_index];
            left_index++;
        } else {
            vec[merge_index] = right_vec[right_index];
            right_index++;
        }
        merge_index++;
    }

    while (left_index < left_size) {
        vec[merge_index] = left_vec[left_index];
        left_index++;
        merge_index++;
    }

    while (right_index < right_size) {
        vec[merge_index] = right_vec[right_index];
        right_index++;
        merge_index++;
    }
}

void merge_sort_helper(std::vector<int>& vec, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = (left + right) / 2;
    merge_sort_helper(vec, left, middle);
    merge_sort_helper(vec, middle + 1, right);
    merge(vec, left, middle, right);
}

void sort(std::vector<int>& vec) {
    merge_sort_helper(vec, 0, vec.size() - 1);
}