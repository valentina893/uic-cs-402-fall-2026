


#include <iostream>
#include <algorithm>
#include <chrono>
#include <concepts>
#include <type_traits>

#include "testing.h"
#include "Firstname_Lastname_project1.h"

using namespace std;

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written
 *   below (e.g., stability, in-place, etc.).
 *
 * - DO NOT MODIFY THE FUNCTION SIGNATURES!!!
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project1.h".
 *
 * - The file "testing.cpp" has various functions you can utilize to test
 *   your code. You can also add your own tests!
 *
 * - If you are working in a group, please modify the comments directly below.
 *
 */


/** This please add your name here as well **/
const std::string who_am_i() {
    return "valentina_susarret";
}


/*** GROUP PROJECT ***/
// Please list ALL of your other group members as comments below.
//   Member 1
//   Member 2



/* Bubble Sort 
 *
 * 5 points
 * 
 * Algorithm: Continuously compare adjacent elements and swap them if necessary.
 *            This is a stable, in-place sorting algorithm. Your implementation must be in-place.
 * 
 * Notes: We must iterate through the array N times.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void bubble_sort(vector<T> &list, bool descending) {
    // ascending
    if (!descending) {
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < list.size()-1; j++) {
                if (list.at(j) > list.at(j+1)) {
                    T temp = list.at(j);
                    list.at(j) = list.at(j+1);
                    list.at(j+1) = temp;
                }
            }
        }
    }
    // descending 
    else {
        for (int i = 0; i < list.size(); i++) {
            for (int j = list.size()-1; j > 0; j--) {
                if (list.at(j) > list.at(j-1)) {
                    T temp = list.at(j);
                    list.at(j) = list.at(j-1);
                    list.at(j-1) = temp;
                }
            }
        }
    }
}

template<typename T>
void test_bubble(std::vector<T> &list) {
    std::cout << "testing bubble sort\n";
    bubble_sort(list, false);
    std::cout << "  ascending: ";
    if (std::is_sorted(list.begin(), list.end()) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
    list = {0, 1, 5, 6, 2, 3, 9, 17, 16};
    bubble_sort(list, true);
    std::cout << "  desending: ";
    if (std::is_sorted(list.begin(), list.end(), std::greater<>{}) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
}














/* Selection Sort 
 *
 * 5 points
 * 
 * Algorithm: Continuously finds the minimium (or maximum) element in the list, 
 *            then swaps it with the first non-sorted element of the list.
 *            This is an unstable, in-place sorting algorithm. 
 *            Your implementation must be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void selection_sort(vector<T> &list, bool descending) {
    // ascending
    if (!descending) {
        for (int i = 0; i < list.size(); i++) {
            T min = *std::min_element(list.begin(), list.end());
            if (list.at(i) != min) {
                T temp = list.at(i);
                list.at(i) = min;
                min = temp;
            }
        }
        
    }
    // descending
    else {
        for (int i = list.size()-1; i >= 0; i--) {
            T max = *std::max_element(list.begin(), list.end());
            if (list.at(i) != max) {
                T temp = list.at(i);
                list.at(i) = max;
                max = temp;
            }
        }
    }
}

template<typename T>
void test_selection(vector<T> &list) {
    std::cout << "testing selection sort\n";
    selection_sort(list, false);
    std::cout << "  ascending: ";
    if (std::is_sorted(list.begin(), list.end()) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
    list = {0, 1, 5, 6, 2, 3, 9, 17, 16};
    selection_sort(list, true);
    std::cout << "  desending: ";
    if (std::is_sorted(list.begin(), list.end(), std::greater<>{}) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
}













/* Insertion Sort 
 *
 * 5 points
 * 
 * Algorithm: Iterates through the list and inserts the current element into
 *            the correct sorted position of the prefix of the list.
 *            This is a stable, in-place sorting algorithm. Your implementation
 *            does not need to be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
//template<typename T>
//void insertion_sort(vector<T> &list, bool descending = false);
template<typename T>
void insertion_sort(vector<T> &list, bool descending) {
    // ascending
    if (!descending) {
        for (int i = 1; i < list.size(); i++) {
            T key = list.at(i);
            int j = i - 1;

            while (j >= 0 && list.at(j) > key) {
                list.at(j+1) = list.at(j);
                j--;
            }
            list.at(j+1) = key;
        }
    }
    // descending
    else {
        for (int i = 1; i < list.size(); i++) {
            T key = list.at(i);
            int j = i - 1;

            while (j >= 0 && list.at(j) < key) {
                list.at(j+1) = list.at(j);
                j--;
            }
            list.at(j+1) = key;
        }
    }
}

template<typename T>
void test_insertion(vector<T> &list) {
    std::cout << "testing insertion sort\n";
    insertion_sort(list, false);
    std::cout << "  ascending: ";
    if (std::is_sorted(list.begin(), list.end()) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
    list = {0, 1, 5, 6, 2, 3, 9, 17, 16};
    insertion_sort(list, true);
    std::cout << "  desending: ";
    if (std::is_sorted(list.begin(), list.end(), std::greater<>{}) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
}





/* Quicksort 
 *
 * 10 points
 * 
 * Algorithm: Sorts by first choosing a random pivot from the list, then 
 *            partitioning the list into two halves with respect to the 
 *            pivot, then recursing on each half.
 *            This is an unstable sorting algorithm. Not required to be
 *            implemented as an in-place sort.
 *            
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 * */
template<typename T>
void quicksort(vector<T> &list, bool descending) {
    // ascending
    if (!descending) {
        quicksort_rec(list, 0, list.size()-1);
    }
    // descending
    else {
        quicksort_rec(list, list.size()-1, 0);
    }
}

template<typename T>
void quicksort_rec(vector<T> &list, int low, int high) {
    if (low < high) {
        int pi = partition(list, low, high);

        quicksort_rec(list, low, pi-1);
        quicksort_rec(list, pi+1, high);
    }
}

template<typename T>
int partition(vector<T> &list, int low, int high) {
    int pivot = list.at(high);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (list.at(j) <= pivot) {
            i++;
            T temp = list.at(i);
            list.at(i) = list.at(j);
            list.at(j) = temp;
        }
    }

    T temp = list.at(i+1);
    list.at(i+1) = list.at(high);
    list.at(high) = temp;

    return i + 1;
}

template<typename T>
void test_quick(std::vector<T> &list) {
    std::cout << "testing quick sort\n";
    quicksort(list, false);
    std::cout << "  ascending: ";
    if (std::is_sorted(list.begin(), list.end()) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
    list = {0, 1, 5, 6, 2, 3, 9, 17, 16};
    quicksort(list, true);
    std::cout << "  descending: ";
    if (std::is_sorted(list.begin(), list.end(), std::greater<>{}) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }  
}



/* Merge Sort 
 *
 * 10 points
 * 
 * Algorithm: Sorts the list by recursively sorting the left and right
 *            halves, then merging the two left and right halves together.
 *            This is a stable sorting algorithm. Not required to be implemented
 *            as an in-place sort.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 * */
template<typename T>
void merge_sort(vector<T> &list, bool decending) {
    if (list.size() <= 1) {
        return;
    }

    int mid = list.size() / 2;
    vector<T> left;
    vector<T> right;

    for (int i = 0; i < mid; i++) {
        left.push_back(list.at(i));
    }
    for (int i = mid; i < list.size(); i++) {
        right.push_back(list.at(i));
    }
    
    // ascending
    if (!decending) {
        merge_sort(left, decending);
        merge_sort(right, decending);
        list = merge(left, right);
    }
    // descending
    else {

    }
}

template<typename T>
vector<T> merge(vector<T> &left, vector<T> &right) {
    vector<T> result;
    int i = 0;
    int j = 0;

    while (i < left.size() && j < right.size()) {
        if (left.at(i) < right.at(j)) {
            result.push_back(left.at(i));
            i++;
        } else {
            result.push_back(right.at(j));
            j++;
        }
    }

    for (int k = i; k < left.size(); k++) {
        result.push_back(left.at(k));
    }
    for (int k = j; k < left.size(); k++) {
        result.push_back(right.at(k));
    }

    return result;
}

template<typename T>
void test_merge(std::vector<T> &list) {
    std::cout << "testing merge sort\n";
    merge_sort(list, false);
    std::cout << "  ascending: ";
    if (std::is_sorted(list.begin(), list.end()) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
    list = {0, 1, 5, 6, 2, 3, 9, 17, 16};
    merge_sort(list, true);
    std::cout << "  descending: ";
    if (std::is_sorted(list.begin(), list.end(), std::greater<>{}) == true) {
        std::cout << "passed\n";
    } else {
        std::cout << "failed\n";
    }
}











/* Your Hybrid Sort
 *
 * 20 points
 *
 * Algorithm: Your own custom Hybrid Sorting algorithm! Remember, a hybrid
 *            sort tries to take advantage of two (or more) sorting algorithms
 *            to speed up data processing.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 */
template<typename T>
void my_hybrid_sort(vector<T> &list, bool descending) {
    // Your code here!
}


/* Binary Radix Sort
 *
 * 20 points
 *
 * Algorithm:
 *
 * Parameters: 
 *   vector<T> &list: reference to a list of type T.
 *                    IMPORTANT: this type T is assumed to be *integral*. It
 *                    can be any of the following integral types in C++:
 *                      - (unsigned) short int
 *                      - (unsigned) int
 *                      - (unsigned) long int
 */
//template<class T>
//concept Integral = std::is_integral<T>::value;
template<Integral T> 
void binary_radix_sort(vector<T> &list, bool descending) {
    // Your code here!
}



/* Base B Radix Sort 
 *
 * 25 Points
 *
 * Algorithm: Implement Radix Sort as discussed in class, but with
 *            respect to any unspecified base.
 *
 * Parameters: 
 *   vector<T> &list: reference to a list of type T.
 *                    IMPORTANT: this type T is assumed to be *integral*. It
 *                    can be any of the following integral types in C++:
 *                      - (unsigned) short int
 *                      - (unsigned) int
 *                      - (unsigned) long int
 *
 *   unsigned int base: the base with which to implement the radix sort. 
 *                      Note that base should be at least 2. The default
 *                      base is 10.
 *
 *   bool decending: if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default).
 *
 *
 * Additional Information:
 *   - If you are enrolled in the graduate section of this course, you MUST
 *     implement this function (i.e., it counts towards your total grade).
 *
 *   - If you are enrolled in the undergraduate section of this course, this
 *     function is optional and worth extra credit.
 *
 */
template<Integral T>
void radix_sort(vector<T> &list, unsigned int base, bool descending) {
    // Your code here!
}






int main() {
    /**** STUDENT CODE HERE ****/ 

    std::vector<int> test1 = {1, 2, 4, 7, 3, 2, -1, 0};
    std::vector<int> test2 = {6, -3, 4, 8, 0, 2, -1, 20};
    std::vector<int> test3 = {6, -3, 4, 8, 0, 2, -1, 20};
    std::vector<int> test4 = {6, -3, 4, 8, 0, 2, -1, 20};
    std::vector<int> test5 = {6, -3, 4, 8, 0, 2, -1, 20};
    test_bubble(test1);
    test_selection(test2);
    test_insertion(test3);
    test_quick(test4);
    test_merge(test5);

    /**** END STUDENT CODE ****/

    /***** DO NOT MODIFY BELOW THIS LINE *****/
    /*** INSTRUCTIONS ***
     *
     * Before submitting your code: 
     *   - remove all code within the main function that you have written above the `do-not-modify` line;
     *   - uncomment all lines below that begin with "//".
     *   - NOTE: you can uncomment the code below if you are testing your code with the autograder. The 
     *     autograder will throw an error if you run it without uncommenting the code.
     */

    //vector<int> test_list {1, 2, 3, 4, 5};
    //vector<unsigned int> test_list2 {1, 2, 3, 4, 5};
    //vector<StableChar> test_list3  {};
    //vector<StableInt> test_list4 {};
    //vector<StableString> test_list5 {};
    //vector<short> test_list6  {};
    //vector<unsigned short> test_list7  {};
    //vector<long> test_list8  {};
    //vector<unsigned long> test_list9  {};


    //insertion_sort(test_list);
    //insertion_sort(test_list2);
    //insertion_sort(test_list3);
    //insertion_sort(test_list4);
    //insertion_sort(test_list5);
    //insertion_sort(test_list6);
    //insertion_sort(test_list7);
    //insertion_sort(test_list8);
    //insertion_sort(test_list9);


    //selection_sort(test_list);
    //selection_sort(test_list2);
    //selection_sort(test_list3);
    //selection_sort(test_list4);
    //selection_sort(test_list5);
    //selection_sort(test_list6);
    //selection_sort(test_list7);
    //selection_sort(test_list8);
    //selection_sort(test_list9);

    //bubble_sort(test_list);
    //bubble_sort(test_list2);
    //bubble_sort(test_list3);
    //bubble_sort(test_list4);
    //bubble_sort(test_list5);
    //bubble_sort(test_list6);
    //bubble_sort(test_list7);
    //bubble_sort(test_list8);
    //bubble_sort(test_list9);


    //merge_sort(test_list);
    //merge_sort(test_list2);
    //merge_sort(test_list3);
    //merge_sort(test_list4);
    //merge_sort(test_list5);
    //merge_sort(test_list6);
    //merge_sort(test_list7);
    //merge_sort(test_list8);
    //merge_sort(test_list9);

    //quicksort(test_list);
    //quicksort(test_list2);
    //quicksort(test_list3);
    //quicksort(test_list4);
    //quicksort(test_list5);
    //quicksort(test_list6);
    //quicksort(test_list7);
    //quicksort(test_list8);
    //quicksort(test_list9);

    //my_hybrid_sort(test_list);
    //my_hybrid_sort(test_list2);
    //my_hybrid_sort(test_list3);
    //my_hybrid_sort(test_list4);
    //my_hybrid_sort(test_list5);
    //my_hybrid_sort(test_list6);
    //my_hybrid_sort(test_list7);
    //my_hybrid_sort(test_list8);
    //my_hybrid_sort(test_list9);

    //binary_radix_sort(test_list);
    //binary_radix_sort(test_list2);
    //binary_radix_sort(test_list6);
    //binary_radix_sort(test_list7);
    //binary_radix_sort(test_list8);
    //binary_radix_sort(test_list9);

    //radix_sort(test_list);
    //radix_sort(test_list2);
    //radix_sort(test_list6);
    //radix_sort(test_list7);
    //radix_sort(test_list8);
    //radix_sort(test_list9);


    return 0;
}









