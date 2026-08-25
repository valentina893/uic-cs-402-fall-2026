#include <vector>
#include <random>
#include <concepts>
#include <type_traits>


#ifndef FIRSTNAME_LASTNAME_PROJECT1
#define FIRSTNAME_LASTNAME_PROJECT1

using namespace std;



/*** Helper Functions ***/
/* DO NOT MODIFY THIS FUNCTION */
inline unsigned int get_rand_index(unsigned int len) {
    srand(time({}));
    return static_cast<unsigned int>(std::rand() % len);
}


/*** STUDENT HELPER FUNCTIONS HERE ***/
/* You may write your own custom helper functions
 * in order to make your implementations easier.
 */



/*** END STUDENT HELPER FUNCTIONS ***/





/*** DO NOT MODIFY BELOW ***/
/*** Main Functions for Students to Implement ***/

/** Helper type for integrals only **/
template<class T>
concept Integral = is_integral<T>::value;


/* Bubble Sort */
template<typename T>
void bubble_sort(vector<T> &list, bool descending = false);

/* Test method for Bubble Sort */
template<typename T>
void test_bubble(std::vector<T> &list);

/* Selection Sort */
template<typename T>
void selection_sort(vector<T> &list, bool descending = false);

/* Test method for selection Sort */
template<typename T>
void test_selection(std::vector<T> &list);

/* Insertion Sort */
template<typename T>
void insertion_sort(vector<T> &list, bool descending = false); 

/* Test method for Insertion Sort */
template<typename T>
void test_insertion(std::vector<T> &list);

/* Quick Sort */
template<typename T>
void quicksort(vector<T> &list, bool descending = false);

/* Test method for Quick Sort */
template<typename T>
void test_quick(std::vector<T> &list);

/* Merge Sort */
template<typename T>
void merge_sort(vector<T> &list, bool descending = false);

/* Test method for Merge Sort */
template<typename T>
void test_merge(std::vector<T> &list);

/* Your Hybrid Sort */
template<typename T>
void my_hybrid_sort(vector<T> &list, bool descending = false);

/* Test method for Hybrid Sort */
template<typename T>
void test_hybrid(std::vector<T> &list);

/* Binary Radix Sort */
template<Integral T>
void binary_radix_sort(vector<T> &list, bool descending = false);

/* Test method for Binary Radix Sort */
template<typename T>
void test_binary_radix(std::vector<T> &list);

/* Base B Radix Sort */
template<Integral T> 
void radix_sort(vector<T> &list, unsigned int base = 10, bool descending = false);

/* Test method for Base B Radix Sort */
template<typename T>
void test_radix(std::vector<T> &list);


#endif
