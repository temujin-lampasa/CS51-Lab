#include <iostream>
#include <unistd.h>

using namespace std;

// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "[%Y-%m-%d] %X", &tstruct);

    return buf;
}


int main(){
    int forkRet = fork();
    int count = 0;
    if (forkRet == 0){
        execl("/opt/X11/bin/xclock", "myXclock", NULL);
    } else {
        while (true){
            cout << currentDateTime() << endl;
            count++;
            if (count == 3){
                cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << endl;
                count = 0;
            }
            sleep(3);
        }
    }
}
