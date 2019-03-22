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
    
    
    int _prizeBoxNumber;
    int _firstPick;
    bool _switchBoxes;
    bool won = false;



    Experiment(bool switchBoxes){
        _switchBoxes = switchBoxes;
        srand(time(0));
    }

    void runExperiment(){
        // https://www.daniweb.com/programming/software-development/threads/1769/c-random-numbers#
        _prizeBoxNumber = rand()%3;
        _firstPick = rand()%3;
        if(_firstPick == _prizeBoxNumber){
            won = true;
        }
        else{
            won = false;
        }

        
    }

    void printExperiment(){
        cout << "prizeBoxNumber=" << _prizeBoxNumber << " ";
        cout << "firstPick=" << _firstPick << " ";
        if(won){
            cout << "WON";
        }
        cout << "\n";
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
    bool results[numExperiments];
    Experiment e1(false);
    for (int i=0; i<numExperiments; i++){
        e1.runExperiment();
        results[i] = e1.won;
        e1.printExperiment();
    }

    cout << "\nCount up wins...\n";
    // http://www.cplusplus.com/reference/algorithm/count/
    int mycount = std::count (results, results+numExperiments, true);
    float percentage = (float)mycount/(float)numExperiments;
    cout << "Win Count was " << mycount << ". Percentage: " << percentage << "\n";


    return 0;
}


