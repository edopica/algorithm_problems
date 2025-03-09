/**
 * This problem is all about finding the closest value in a list for each element in another list.
 * It can be didived in two steps:
 *
 *  - Sorting the list of available dates: we can do it using radix sort since all values are integers.
 *    my first thought was counting sort, but it's made unfeasible by the range of the keys (10^9).
 *    Radix sort allows to apply counting sort on single digits (10 keys) while maintaining linear complexity.
 *
 *  - Searching: after sorting the array of available dates, we can inspect it using binary search.
 *    The only teak that needs to be made is that in the case of a miss (value not found) the closest value
 *    to the searched one must be returned. In the case of a tie, the smaller value is chosen.
 *
 */
#include <vector>
#include <iostream>
#include <cmath>

struct SingleCase {
    int num_days, num_customers;
    std::vector<int> available_dates, requested_dates;
};

/**
 * @brief Finds the maximum value in an array.
 *
 * @param arr The array to search.
 * @param size The size of the array.
 * @return int The maximum value.
 */
int get_maximum_value(const int arr[], int size) {
    int max_value = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
}

/**
 * @brief Performs counting sort on an array based on a specific digit.
 *
 * @param arr The array to sort.
 * @param size The size of the array.
 * @param exp The exponent representing the digit to sort by.
 */
void count_sort(int arr[], int size, int exp) {
    const int NUM_DIGITS = 10;
    int output[size];
    int count[NUM_DIGITS] = { 0 };

    for (int i = 0; i < size; i++) {
        count[(arr[i] / exp) % NUM_DIGITS]++;
    }

    for (int i = 1; i < NUM_DIGITS; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % NUM_DIGITS] - 1] = arr[i];
        count[(arr[i] / exp) % NUM_DIGITS]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

/**
 * @brief Sorts an array using radix sort.
 *
 * @param arr The array to sort.
 * @param size The size of the array.
 */
void radix_sort(int arr[], int size) {
    int max_value = get_maximum_value(arr, size);

    for (int exp = 1; max_value / exp > 0; exp *= 10) {
        count_sort(arr, size, exp);
    }
}

/**
 * @brief Finds the closest available date to the requested date.
 *
 * @param requested_date The date requested by the customer.
 * @param num_available_dates The number of available dates.
 * @param available_dates Array of available dates.
 * @return int The closest available date.
 */
int find_date(int requested_date, int num_available_dates, int available_dates[]) {
    int low = 0, high = num_available_dates - 1;
    int closest_date = available_dates[0];

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (available_dates[mid] == requested_date) {
            return requested_date;
        }
        // When we have a miss, the closest value can get updated in two cases
        // smaller distance
        if ((std::abs(requested_date - available_dates[mid]) < std::abs(requested_date - closest_date))) {
            closest_date = available_dates[mid];
        }
        // same distance and smaller date
        else if ((std::abs(requested_date - available_dates[mid]) == std::abs(requested_date - closest_date)) and available_dates[mid] < closest_date) {
            closest_date = available_dates[mid];
        }
        if (available_dates[mid] < requested_date) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return closest_date;
}

/**
 * @brief Solves a single test case.
 *
 * @param test_case The test case to solve.
 */
void solve_case(const SingleCase& test_case) {
    std::vector<int> available_dates = test_case.available_dates;
    radix_sort(available_dates.data(), test_case.num_days);

    for (int i = 0; i < test_case.num_customers; i++) {
        std::cout << find_date(test_case.requested_dates[i], test_case.num_days, available_dates.data()) << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Reads a single integer value from standard input.
 *
 * @return int The read value.
 */
int read_value() {
    std::string value;
    std::cin >> value;
    return std::stoi(value);
}

/**
 * @brief Reads a single test case from standard input.
 *
 * @return SingleCase The read test case.
 */
SingleCase get_case() {
    SingleCase new_case;
    new_case.num_days = read_value();
    for (int i = 0; i < new_case.num_days; i++) {
        new_case.available_dates.push_back(read_value());
    }
    new_case.num_customers = read_value();
    for (int i = 0; i < new_case.num_customers; i++) {
        new_case.requested_dates.push_back(read_value());
    }
    return new_case;
}

int main() {
    std::vector<SingleCase> cases;
    int num_test_cases = read_value();

    for (int i = 0; i < num_test_cases; i++) {
        cases.push_back(get_case());
    }

    for (int i = 0; i < num_test_cases; i++) {
        solve_case(cases[i]);
    }

    return 0;
}
