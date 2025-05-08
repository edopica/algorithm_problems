/* At first I approached this problem with a naive solution, focusing on the frequency of the single attributes and simply choosing wether to add an attribute if it appears less then n/2 times.
 * This approach works for basic scenarios, but fails in more complex ones.
 *
 * The key to solve this problem is to view each skill set as a node of a graph. We consider nodes that differ for just one bit "neighbors".
 * Using a BFS, we navigate the graph looking for the neighbor with the highest Hamming distance, ergo the most unique one!
 */
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath> // For pow, though bit shift is better

int main() {
    // Faster I/O, cool trick learned by competive programming try hards.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k;

    int num_possible_chars = 1 << k; // Sick way to calculate 2^k

    std::vector<int> min_dist(num_possible_chars, -1); // Stores minimum Hamming distance, -1 means unvisited
    std::queue<int> q; // Queue for BFS

    // Read input and initialize
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        int current_char_int = 0;
         // Convert binary string to integer using bit shifts
        for (int j = 0; j < k; ++j) {
            if (s[j] == '1') {
                current_char_int |= (1 << j); 
            }
        }


        if (min_dist[current_char_int] == -1) { // Handle duplicates, only add unique starting points
            min_dist[current_char_int] = 0;
            q.push(current_char_int);
        }
    }

    // Perform BFS
    while (!q.empty()) {
        int current_char = q.front();
        q.pop();

        // Explore neighbors (differ by one bit)
        for (int j = 0; j < k; ++j) {
            int neighbor_char = current_char ^ (1 << j); // Flip the j-th bit

            if (min_dist[neighbor_char] == -1) { // If neighbor hasn't been visited
                min_dist[neighbor_char] = min_dist[current_char] + 1;
                q.push(neighbor_char);
            }
        }
    }

    // Find the character with the maximum minimum distance
    int max_min_dist = -1;
    int best_t = -1;

    for (int t = 0; t < num_possible_chars; ++t) {
        if (min_dist[t] > max_min_dist) {
            max_min_dist = min_dist[t];
            best_t = t;
        }
    }

     // Convert the best integer representation back to a binary string
    std::string result_string = "";
    for (int i = 0; i < k; ++i) {
        result_string += ((best_t >> i) & 1) ? '1' : '0'; // Read bits from right to left
    }


    // Output the result
    std::cout << result_string << std::endl;

    return 0;
}
