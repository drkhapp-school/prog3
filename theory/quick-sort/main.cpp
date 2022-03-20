//
//  main.cpp
//  quick-sort
//
//  Created by Jean-Philippe on 2021-11-12.
//
#include <chrono>
#include <ctime>
#include <iostream>
#define DATA_COUNT 250

int dataBubble[DATA_COUNT];
int dataQuick[DATA_COUNT];

using namespace std;
using namespace std::chrono;

steady_clock::time_point start, stop;
duration<double> deltaTime;

void bubbleSort() {
  for (int i = 0; i < DATA_COUNT; i++)
    for (int j = 0; j < DATA_COUNT; j++)
      if (dataBubble[i] < dataBubble[j])
        swap(dataBubble[i], dataBubble[j]);
}

void quickSort(int min, int max) {
  int left = min;
  int right = max;
  int pivot = left;

  while (left != right) {
    if (dataQuick[left] > dataQuick[right]) {
      swap(dataQuick[left], dataQuick[right]);
      pivot = left + right - pivot;
    }

    pivot == left ? right-- : left++;
  }

  if (min < pivot - 1)
    quickSort(min, pivot - 1);
  if (max > pivot + 1)
    quickSort(pivot + 1, max);
}

int main() {
  srand(time(0));

  // Génération
  start = steady_clock::now();
  for (int i = 0; i < DATA_COUNT; i++)
    dataBubble[i] = dataQuick[i] = rand() % 1000;
  stop = steady_clock::now();
  deltaTime = duration_cast<duration<double> >(stop - start);
  cout << "Génération: " << deltaTime.count() << " secondes" << endl;

  // Bubble sort
  /* start = steady_clock::now(); */
  /* bubbleSort(); */
  /* stop = steady_clock::now(); */
  /* deltaTime = duration_cast<duration<double> >(stop - start); */
  /* cout << endl << "Simple sort: " << deltaTime.count() << " secondes" <<
   * endl; */

  // Quick sort
  start = steady_clock::now();
  quickSort(0, DATA_COUNT - 1);
  stop = steady_clock::now();
  deltaTime = duration_cast<duration<double> >(stop - start);
  cout << endl << "Quick sort: " << deltaTime.count() << " secondes" << endl;

  return 0;
}
