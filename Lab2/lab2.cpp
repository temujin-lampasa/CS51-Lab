#include <iostream>
#include <string>

using namespace std;

int main(){
    int N;
    cin >> N;
    cin.ignore();
    for (int i=0; i<N; i++){
        string line;
        getline(cin, line);

        // Get indices of all spaces in line
        int space_idx[3];
        int count = 0;
        for (int idx=0; idx<line.length(); idx++) {
            char c = line[idx];
            if (c == ' ') space_idx[count++] = idx;
        }

        // Separate integer inputs and string input
        // sep by 2nd space
        string int_inputs = line.substr(0, space_idx[1]);
        string str_input = line.substr(space_idx[1]+1);

        // Split the two ints
        // sep by 1st space
        string i1 = int_inputs.substr(0, space_idx[0]);
        string i2 = int_inputs.substr(space_idx[0]+1);
        cout << "Agent#" << i+1 << " is at (" << i1 << ", " << i2 << ")" << endl;
        cout << "Says: " << str_input << endl;
    }
    return 0;
}