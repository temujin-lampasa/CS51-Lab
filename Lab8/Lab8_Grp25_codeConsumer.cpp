#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main( int argc, char* argv[] )
{
    if (argc != 3){
        cout << "Usage: ./consumer <textfileCopy> <shared memory size in bytes>" << endl;
        exit(1);
    }
    // args: dest. file and shared memory size (bytes).
    string filename = argv[1];
    int shmSize = atoi(argv[2]);

    cout << "FILENAME: "<< filename << endl;
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
    // 2 sems, set:
    // Sem0 = producer_sem = 0
    // Sem1 = consumer_sem = 1
    int nOperations = 2;
    struct sembuf sema[nOperations];
    sema[0].sem_num = 1;
    sema[0].sem_op = 1;
    sema[0].sem_flg = SEM_UNDO;
    sema[1].sem_num = 0;
    sema[1].sem_op = 0;
    sema[1].sem_flg = SEM_UNDO;
    int opResult = semop( semId, sema, nOperations );
    if (opResult != -1){
        printf("Sem creation success.\n");
    } else {
        perror("Sem creation failed");
        exit(0);
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
    else  // Read from shared memory and write chunks to file
    {
        fstream fout(filename, ios::out | ios::binary);
        vector<char> buffer (shmSize,0);
        std::vector<char> write_data;

        // Read from shared memory and write to file
        while(1) {
            cout << "Waiting for producer..." << endl;
            // PRODUCER -> WAIT
            // wait for producer to produce something
            int opResult;
            int nOperations = 1;
            struct sembuf sema[nOperations];
            sema[0].sem_num = 0;
            sema[0].sem_op = -1;
            sema[0].sem_flg = SEM_UNDO;
            opResult = semop( semId, sema, nOperations );
            cout << "Success -- wait" << endl; 

            // Read from memory then write to file
            int s = sharedMem2[0];
            strcpy((char*)&buffer[0], sharedMem); 
            write_data = std::vector<char>(&buffer[0], &buffer[s]);
            cout << "Writing data ..." << endl;
            fout.write((char*)&write_data[0], s);

            // CONSUMER -> POST
            sema[0].sem_num = 1;
            sema[0].sem_op = 1;
            sema[0].sem_flg = SEM_UNDO;
            opResult = semop( semId, sema, nOperations );
            cout << "Success -- post" << endl;

            if (s != shmSize){
                break;
            }
        }
    }

    return 0;
}

