/**
 *  Course: CS201
 *  Section: 1
 *  Homework: 02
 *  Author: Zeynep CANKARA
 *  ID: 21703381
 *  Description: Time analysis on different solutions of the Maximum Subsequent Sum Problem.
 */

#include <iostream> // cout
#include <chrono> // for time
#include <cmath>  //pow
#include <stdlib.h>  //rand
#include <time.h>    //clock_t
using namespace std;


/**
 * @brief generates a random array
 */
void createRandomArray(int * arr, const int size) {
    for (int i = 0; i < size; i++) {
        int randomNumber = rand() % size;
        arr[i] = randomNumber;
    }
}


/**
 * @brief O(n^3) 1st Solution to Maximum Subsequent sum problem
 *        Algorithm iterates through all possible subsets arrays of the original array
 *        Calculates sum of elements within the subset
 */
int maxSubSum1(int *arr, const int size){
    // maximum subsequent sum
    int maxSum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            // calculate sum within the subset
            int curSum = 0;
            for (int k = i; k <= j; k++) {
                curSum += arr[k];
            }
            // compare with maximumSum to check whether current sum > maximum sum
            if (curSum > maxSum) {
                maxSum = curSum;
            }
        }
    }
    return maxSum;
}


/**
 * @brief O(n^2) 2nd Solution to Maximum Subsequent sum problem
 *        Algorithm iterates through all possible subsets arrays of the original array
 *        Algorithm calculates sum within the subset within the second loop.
 */
int maxSubSum2(const int *arr, const int size){
    int maxSum = 0;
    
    for (int i = 0; i < size; i++) {
        // calculate sum within the subset
        int curSum = 0;
        for (int j = i; j < size; j++) {
            curSum += arr[j];
            // compare with maximumSum to check whether current sum > maximum sum
            if (curSum > maxSum) {
                maxSum = curSum;
            }
        }
    }
    return maxSum;
}

/**
 * @brief O(n*log(n)) 3rd Solution to Maximum Subsequent sum problem
 *        Algorithm takes divide and conquer approach
 *        Divide array into 2 halves
 *          - calculate max subsequent sum within the left subtree
 *          - calculate max subsequent sum within the right subtree
 *          - check case where max subsequent sum is between the boundry
 *          - This algorithm does not necessarily conserves the original array: Not in place
 */
int maxSubSum3Helper(int *arr, int left, int right){
    // base case
    if (left == right) {
        if (arr[left] > 0) {
            return arr[left];
        } else {
            return 0;
        }
    }
    
    int center = (int)((left + right) / 2); // find the mid point
    // solve the subproblems
    int maxLeftSum = maxSubSum3Helper(arr, left, center);
    int maxRightSum = maxSubSum3Helper(arr, center + 1, right);
    // check the border case where max sum can be in between
    int maxLeftBorderSum = 0;
    int leftBorderSum = 0;
    for (int i = center; i >= left; i--) {
        // calculate the sum of left border
        leftBorderSum += arr[i];
        if (leftBorderSum > maxLeftBorderSum) {
            maxLeftBorderSum = leftBorderSum;
        }
    }
    // calculate the sum of right border
    int maxRightBorderSum = 0;
    int rightBorderSum = 0;
    for (int i = center + 1; i <= right; i++) {
        rightBorderSum += arr[i];
        if (rightBorderSum > maxRightBorderSum) {
            maxRightBorderSum = rightBorderSum;
        }
    }
    // return the maximum of those 3 cases
    return max(max(maxLeftSum, maxRightSum), (maxRightBorderSum + maxLeftBorderSum));
    }

/**
 *  @brief Driver function for O(n*log(n)) 3rd Solution of the Maximum Subsequent sum problem
 */
int maxSubSum3(int *arr, const int size){
    // call to the helper function
    return maxSubSum3Helper(arr, 0, size-1);
}


/**
 * @brief O(n) 4th Solution to Maximum Subsequent sum problem
 *         - Just check whether current sum goes below 0
 *         -set current sum to 0 if that's the case
 */
int maxSubSum4(const int *arr, const int size){
    int maxSum = 0;
    int curSum = 0;
    for (int i = 0; i < size; i++) {
        // add the current element to the current sum
        curSum += arr[i];
        // maximum sum check
        if (curSum > maxSum) {
            maxSum = curSum;
        }
        // current sum below 0 case
        if (curSum < 0) {
            curSum = 0;
        }
    }
    return maxSum;
}



int main() {
    // Test Driver program for the solution algorithms
    // Test will done with following sizes 10, 100, 1000, 10000, 100000
    // change arrSize accordingly
    const int arrSize = 100000;
    int *arr = new int[arrSize];
    createRandomArray(arr, arrSize);
    // Initial variables
    clock_t timer; //counts the elapsed time
    // Compute the number of milliseconds that passed since the starting time
    timer = clock();
    // Code block for executing functions
    maxSubSum1(arr, arrSize);
    // calculate the time
    timer = clock() - timer;
    double timeElapsed = (double)(timer * 1000) / CLOCKS_PER_SEC;
    cout << "Time passed is " << timeElapsed << " msec"<<  endl;
    return 0;
}
