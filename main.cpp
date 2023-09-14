#include <windows.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>


using std::cout;


double* numbers;
int size;
double average;

struct MinMaxThreadArgs {
    std::vector<int> min_positions;
    std::vector<int> max_positions;
};

DWORD WINAPI MinMaxThread(LPVOID lpParam) {
    // cout << "min_max thread is started.\n";

    MinMaxThreadArgs* args = reinterpret_cast<MinMaxThreadArgs*>(lpParam);

    // Find the minimum and maximum elements && Save their positions
    int min = numbers[0];
    args->min_positions.push_back(0);
    int max = numbers[0];
    args->max_positions.push_back(0);

    for (int i = 1; i < size; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
            args->min_positions.clear();
        }
        if (numbers[i] == min) {
            args->min_positions.push_back(i);
        }
        Sleep(7);

        if (numbers[i] > max) {
            max = numbers[i];
            args->max_positions.clear();
        }
        if (numbers[i] == max) {
            args->max_positions.push_back(i);
        }
        Sleep(7);
    }

    cout << "Minimum value: " << min << std::endl;
    cout << "Maximum value: " << max << std::endl;

    // cout << "min_max thread is finished.\n";
    return 0;
}

DWORD WINAPI AverageThread(LPVOID lpParam) {
    // cout << "average thread is started.\n";

    average = 0;

    // Calculate the sum of elements and the average value
    for (int i = 0; i < size; ++i) {
        average += numbers[i];
        Sleep(12);
    }
    average /= size;

    cout << "Average value: " << average << std::endl;

    // cout << "Average thread is finished.\n";
    return 0;
}

int main() {
    cout << "\nEnter the size of the array: ";
    std::cin >> size;

    numbers = new double[size];

    cout << "Enter " << size << " integers:\n>>> ";
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }

    // Create min_max and average threads
    MinMaxThreadArgs min_max_args;
    HANDLE hMinMaxThread = CreateThread(NULL, 0, MinMaxThread, &min_max_args, 0, NULL);
    HANDLE hAverageThread = CreateThread(NULL, 0, AverageThread, NULL, 0, NULL);

    if (hMinMaxThread == NULL || hAverageThread == NULL) {
        cout << "Error creating threads.\n";
        return GetLastError();
    }

    // Wait for both threads to finish
    WaitForSingleObject(hMinMaxThread, INFINITE);
    WaitForSingleObject(hAverageThread, INFINITE);

    CloseHandle(hMinMaxThread);
    CloseHandle(hAverageThread);

    // Replace min and max elements with the average
    for (int pos : min_max_args.max_positions) {
        numbers[pos] = average;
    }
    for (int pos : min_max_args.min_positions) {
        numbers[pos] = average;
    }

    cout << "Result: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << ";  ";
    }

    cout << "\n\n";

    delete[] numbers;

    return 0;
}
