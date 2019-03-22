#include <iostream>
#include <ctime>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
#include <algorithm>



using namespace std;

// https://www.geeksforgeeks.org/c-classes-and-objects/
class Experiment {
    public:
    
    int number;

    Experiment(){
        srand(time(0));
        generateRandom();
    }

    void generateRandom(){
        // https://www.daniweb.com/programming/software-development/threads/1769/c-random-numbers#
        number = rand()%3;
    }

    void printNumber(){
        cout << number << "\n";
    }
};

int main (int argc, char** argv) {
    
    int numExperiments = 10; // Default


    // get number of random experiments from argument
    //https://stackoverflow.com/questions/9748393/how-can-i-get-argv-as-int
    errno = 0;

    // Convert argument to long
    long conv = strtol(argv[1], NULL, 10);

    // Check for errors: e.g., the string does not represent an integer
    // or the integer is larger than int
    if (errno != 0 || conv > INT_MAX) {
        cout << "Unable to convert argument to int.  Using default experiment number.";
    } else {
        // No error
        numExperiments = conv;
        cout << "Plan to run " << numExperiments << " experiments:\n";
    }

    cout << "\nRunning...\n";
    int results[numExperiments];
    Experiment e1;
    for (int i=0; i<numExperiments; i++){
        e1.generateRandom();
        //e1.printNumber();
        results[i] = e1.number;
    }


    // printf("\nResults:\n");
    // for(int i=0; i<numExperiments; i++){
    //     cout << results[i] << "\n";
    // }

    cout << "\nCounts:\n";
    // http://www.cplusplus.com/reference/algorithm/count/
    for(int i=0; i <=2; i++){
        int mycount = std::count (results, results+numExperiments, i);
        float percentage = (float)mycount/(float)numExperiments;
        cout << "Count of " << i << " was " << mycount << ". Percentage: " << percentage << "\n";
    }


    return 0;
}


