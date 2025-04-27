/* This problem is just another one where we need to exploit the monotonic nature of the 
 * objective variable to use binary search. 
 * We know that the minimum feasible capcacity corresponds to the maximum module weight, 
 * while the maximum feasible capacity corresponds to the sum of all the weights.
 *
 * Now that we have established boundaries we can just cycle through the possible capacities until we 
 * find the minimum.
 * 
 * We can optimize more by calculating prefix sums at the beginning so that we don't have to do it 
 * in O(n)
 */ 

#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int n_parts, n_launches, min_capacity=0, max_capacity=0;
    // Get input and compute prefix sums    
    cin >> n_parts;
    int weights[n_parts], sums[n_parts+1]={0};
    cin >> n_launches;

    for(int i=0; i<n_parts; i++) {
        cin >> weights[i];
        sums[i+1] = weights[i] + sums[i];

        if(weights[i] > min_capacity)
            min_capacity = weights[i];
    }
    max_capacity = sums[n_parts];

    // Start searching the min capcacity
    int launch; // Launch number
    int i, start; // Pointers to the ends of the module
    int final_capacity = sums[n_parts]; 

    while(min_capacity <= max_capacity) {
        // Initialize cycle varibales
        launch = 0;
        start=0;
        i=0;
        int c = (min_capacity + max_capacity) / 2;
        
        // We keep adding modules to the current launch until we reach weight capacity
        while(launch < n_launches && i<n_parts) {
            if(sums[i+1] - sums[start] < c) { 
                i++;
            }
            else if(sums[i+1] - sums[start] == c) {
                i++;
                start = i;
                launch++;
            }
            else {
                launch++;
                start = i;
            }
        }
        // Check for new feasible capcacity    
        if(i==n_parts && c<final_capacity) {
            //cout << c; 
            final_capacity = c; 
        }
        // Update search boundaries
        if(i<n_parts){
          min_capacity = c+1;
        }
        else {
          max_capacity = c-1;
        }
    }

    cout << final_capacity;

    return 0;
}
