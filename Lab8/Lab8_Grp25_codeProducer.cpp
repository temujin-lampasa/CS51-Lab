#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

int main( int argc, char* argv[] )
{
    if (argc != 3){
        cout << "Usage: ./producer <textfile> <shared memory size in bytes>" << endl;
        exit(1);
    }
    // args: dest. file and shared memory size (bytes).
    string filename = argv[1];
    int shmSize = atoi(argv[2]);

    // --- Semaphore ---
    int semId;
    key_t semKey = 2626;
    int semFlag = IPC_CREAT | 0666;
    int nSems = 2;
    semId = semget( semKey, nSems, semFlag );
    if( semId == -1 )
    {
        perror( "semget" );
        exit( 1 );
    }

    // --- Shared Memory ---
    // 1st mem = the chunk of text
    int shmId;
    key_t shmKey = 1111;
    int shmFlags = IPC_CREAT | 0666;
    char* sharedMem;
    shmId = shmget( shmKey, shmSize, shmFlags );
    sharedMem = (char*)shmat( shmId, NULL, 0 );

    // 2nd mem - an integer, the current size of the chunk
    int shmId2;
    key_t shmKey2 = 2222;
    int shmFlags2 = IPC_CREAT | 0666;
    int* sharedMem2;
    shmId2 = shmget( shmKey2, 1, shmFlags2 );
    sharedMem2 = (int*)shmat( shmId2, NULL, 0 );

    if( ((int*)sharedMem) == (int*)-1 )
    {
        perror( "shmop: shmat failed" );
    }
    else  // Read from file and write chunks to shared memory
    {
        ifstream fin(filename);
        vector<char> buffer (shmSize,0);
        std::vector<char> write_data;

        // read from file and write to shared memory...
        while(!fin.eof()) {
            cout << "Waiting for consumer..." << endl;
            // CONSUMER -> WAIT
            int nOperations = 1;
            struct sembuf sema[nOperations];
            sema[0].sem_num = 1;
            sema[0].sem_op = -1;
            sema[0].sem_flg = SEM_UNDO;
            int opResult = semop( semId, sema, nOperations );
            cout << "Success -- wait" << endl;

            // Write to memory
            fin.read(buffer.data(), buffer.size());
            streamsize s=fin.gcount();
            write_data = std::vector<char>(&buffer[0], &buffer[s]);
            strcpy( sharedMem, (char*)&buffer[0]); 
            sharedMem2[0] = s;
            printf("Writing ... ");

            
            // PRODUCER -> POST
            nOperations = 1;
            sema[0].sem_num = 0;
            sema[0].sem_op = 1;
            sema[0].sem_flg = SEM_UNDO;
            opResult = semop( semId, sema, nOperations );
            printf("Success -- post\n");
        
        }
    }

    return 0;
}

