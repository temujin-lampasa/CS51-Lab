#include <iostream>

using namespace std;


void set_next_letter(char *c) {
    bool is_letter = ((0x41 <= *c) & (*c <= 0x5A)) | ((0x61 <= *c) & (*c <= 0x7A));
    if (is_letter){
        if (*c == 'Z') *c = 'A';
        else if (*c == 'z') *c = 'a';
        else *c += 1;
    }
}

int main(){
    string name;

    // #1 Ask for name
    cout << "1. ";
    cin >> name;

    // #2 Print out name
    cout << "2. " << name;

    // #3 Print name w/ only 1st letter revealed
    string temp = "";
    temp += name[0];
    for (int i=1; i<name.length(); i++) {
        temp += "#";
    }
    cout << endl << "3. " << temp << endl;

    // #4-5 Replace all letters with the next letter. Use function w/ pointers
    for (int i=0; i<name.length(); i++) {
        set_next_letter(&name[i]);
    }
    cout << "4. " << name << endl;
    return 0;
}