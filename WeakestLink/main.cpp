/**
 * This problem boils down to a search problem.
 * My intuition is that instead of comparing each possible combination,
 * I should pivot the search arounf minumums.
 * To understand why, let's look at an example, suppose we have a list [3, 8, 2, 3, 5]
 * The first combination I analyze is the array as a whole so we sum each number and we multiply by the minimum (2).
 * After this first step, If I changed the combination by removing the first or the last element,
 * I would be left with a new combination that is guranteed have a lower value,
 * because I subtracted a number a number from the previous sum, while multiplying by the same minimum.
 * sum * minumum > (sum - n) * minimum.
 * So, the only reason is to remove the minimum from the list and split the group in two sub lists.
 * In this way I can treat the problem as a binary search where I pivot on minimums instead of mid points.
 * The final complexity is O(log n).
 * -----------------------------------------
 * After submitting and failing due to excessive time, I've realized that my analysis was wrogn as I excluded the operations of min search and sum.
 * I though about a way to avoid a iterating through ranges each time to find the min and the sum.
 * The first thought was to calculate all the sums before the execution. By storing in another array all the sums up to the Nth element,
 * we can calculate the sum of a range by sums[r+1] - sums[l]. This was sufficient to pass the test.
 * I wasn't able to find a better way to find minimums. That could be done ad priori as well but it wouldn't reduce the total number of operations.
 * Since calculating all the sums just one was sufficient to pass the test I will call it a day.
 */
#include <iostream>
#include <stack>
#include <utility>

using namespace std;


/**
 * @brief reads the members data.
 * @param n_members: number of members
 * @param members: array for storing members values
 */
void get_members(long n_members, long members[]) {
    for(int i=0; i<n_members; i++)
        cin >> members[i];
}

/**
 * @brief finds the position of the minimum in the range of an array
 * @param l the left bound of the range
 * @param r the right bound of the range
 * @param arr the array
 * @return the position of the lowest value in the range.
 */
int find_min(long l, long r, long arr[]) {
    long min_index = l, i;

    for(i=l+1; i<=r; i++) {
        if (arr[i] < arr[min_index])
            min_index = i;
    }

    return min_index;
}


/**
 * @brief find the strongest group of memebrs
 * @param n_members: number of members
 * @param members: array for storing members values
 * @param sums: array that stores in each element i+1 the sum up to the ith member
 * @return strength of the strongest group
 */
long strongest_team(int n_members, long members[], long sums[]) {

    long max_value = 0, new_value, lowest;
    int l, r, index;
    // Use a stack of pairs to store ranges to visit
    stack<pair<int, int>> ranges;
    ranges.emplace(0, n_members-1);

    // Cycle until no ranges are left
    while(! ranges.empty()) {
        // get bounds and pop range
        l = ranges.top().first;
        r = ranges.top().second;
        ranges.pop();
        // Calculate new value and update max if necessary
        index = find_min(l, r, members);
        lowest = members[index];
        //new_value = sum(l, r, members) * lowest;
        new_value = (sums[r+1] - sums[l]) * lowest;
        if(new_value > max_value)
            max_value = new_value;
        // Add new ranges if valid if (l <= r)
        if((index - 1) >= l)
            ranges.emplace(l, index - 1);
        if((index + 1) <= r)
            ranges.emplace(index + 1, r);
        //cout << "max is: " << max_value << " while range is:  " << l << " , " << r << endl;
    }
    return max_value;
}


/**
 * @brief calculates the sum of all the elements up to the ith element.
 * @param n_members: number of elements in the original array.
 * @param members: original array
 * @param sums: array where to store the sums
 */
void get_sums(int n_members, long members[], long sums[]) {
    n_members++;
    sums[0] = 0;
    for(int i=1; i<n_members; i++)
        sums[i] = sums[i-1] + members[i-1];
}


int main()
{
    long n_samples, n_members;
    // Get number of cases
    cin >> n_cases;
    long results[n_cases];
    // Get case info, solve it and store solution
    for(int i=0; i<n_cases; i++) {
        cin >> n_members;
        long members[n_members];
        get_members(n_members, members);
        long sums[n_members+1];
        get_sums(n_members, members, sums);
        results[i] = strongest_team(n_members, members, sums);
    }
    // Print solutions
    for(int i=0; i<n_cases; i++) {
        cout << results[i] << endl;
    }

    return 0;
}
