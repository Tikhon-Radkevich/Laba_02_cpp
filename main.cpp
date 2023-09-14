#include <windows.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>


int* numbers;
int size;


struct MinMaxThreadArgs {
    std::vector<int> min_positions;
    std::vector<int> max_positions;
};

DWORD WINAPI MinMaxThread(LPVOID lpParam) {
    std::cout << "min_max thread is started." << std::endl;

    MinMaxThreadArgs* args = reinterpret_cast<MinMaxThreadArgs*>(lpParam);

    // Find the minimum and maximum elements
    int min = numbers[0];
    args->min_positions.push_back(0);
    int max = numbers[0];
    args->max_positions.push_back(0);

    for (int i = 1; i < size; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
            args->min_positions.clear();
            args->min_positions.push_back(i);
        }
        Sleep(7);
        if (numbers[i] > max) {
            max = numbers[i];
            args->max_positions.clear();
            args->max_positions.push_back(i);
        }
        Sleep(7);
}

    

    std::cout << "Minimum value: " << min << std::endl;
    std::cout << "Maximum value: " << max << std::endl;

    std::cout << "min_max thread is finished." << std::endl;
    return 0;
}

DWORD WINAPI AverageThread(LPVOID lpParam) {
    std::cout << "average thread is started." << std::endl;

    double average = 0;

    // Calculate the sum of elements and the average value
    for (int i = 0; i < size; ++i) {
        average += numbers[i];
        Sleep(12);
    }
    average /= size;

    std::cout << "Average value: " << average << std::endl;

    std::cout << "average thread is finished." << std::endl;
    return 0;
}

int main() {
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    numbers = new int[size];

    std::cout << "Enter " << size << " integers:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }



    // Create min_max and average threads
    MinMaxThreadArgs min_max_args;
    HANDLE hMinMaxThread = CreateThread(NULL, 0, MinMaxThread, &min_max_args, 0, NULL);
    HANDLE hAverageThread = CreateThread(NULL, 0, AverageThread, NULL, 0, NULL);

    if (hMinMaxThread == NULL || hAverageThread == NULL) {
        std::cerr << "Error creating threads." << std::endl;
        return GetLastError();
    }

    // Wait for both threads to finish
    WaitForSingleObject(hMinMaxThread, INFINITE);
    WaitForSingleObject(hAverageThread, INFINITE);

    CloseHandle(hMinMaxThread);
    CloseHandle(hAverageThread);

    for(int i : min_max_args.min_positions){
        std::cout << i << " ";
    }

    // // Find the minimum and maximum elements
    // int min, max;
    // min = *std::min_element(numbers, numbers + size);
    // max = *std::max_element(numbers, numbers + size);

    // // Calculate the average value
    // double average = 0;
    // for (int i = 0; i < size; ++i) {
    //     average += numbers[i];
    // }
    // average /= size;

    // // Replace min and max elements with the average
    // for (int i = 0; i < size; ++i) {
    //     if (numbers[i] == min || numbers[i] == max) {
    //         numbers[i] = static_cast<int>(average);
    //     }
    // }

    // // Output the modified array
    // std::cout << "Modified array: ";
    // for (int i = 0; i < size; ++i) {
    //     std::cout << numbers[i] << " ";
    // }
    std::cout << std::endl;

    delete[] numbers;

    return 0;
}
