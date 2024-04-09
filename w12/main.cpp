// Martins_Prokuratovs_221RDB473
#include <fstream>
#include <limits>
#include <unordered_map>

using namespace std;


typedef struct num {
    int value;
    int index;
} num;

int main(int argc, char** argv) {
    int i = 0;
    int target = 0; int ind = 0;

    if (argc < 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }
    
    ifstream numberStream (argv[1]);

    if ( numberStream.is_open() ) {
        numberStream >> target;

        // Skip line https://stackoverflow.com/a/25012566
        numberStream.ignore(numeric_limits<streamsize>::max(), '\n');

        /**
         * For discovered nums, store their value keyed by the distance to the target.
         * Then, if distance is encountered, the number is easily found
         */
        unordered_map<int, num> diffToNum;

        while ( numberStream >> i ) {
            // If this number is already in the map as a difference, and it's not the same number, we've got it
            if (diffToNum.find(i) != diffToNum.end() && diffToNum[i].value != i) {
                printf("Solution found\n");
                printf("Indices: %d, %d\n", ind, diffToNum[i].index);
                return 0;

            } else {
                // Otherwise, store the number and its difference
                int diff = target - i;
                diffToNum[diff] = {i, ind};
            }

            ind++;
        }

        printf("No solution found\n");

        return 0;
        
    } else {
        printf("Could not read from file\n");

        return 1;
    }
}
