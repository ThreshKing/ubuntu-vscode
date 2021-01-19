#include<iostream>
#include<thread>
#include<cstdlib>

using namespace std;

#define NUM_THREADS 5 

void* PrintHello(void* threadid)
{
    int tid = *((int*)threadid);
    cout << "Hello Runoob! 线程ID: " << tid << endl;
    pthread_exit(NULL); 
    
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int indexes[NUM_THREADS];
    int rc;
    int i;

    for(int i=0; i<NUM_THREADS; i++)
    {
        cout << "main(): 创建线程， " << i << endl;
        indexes[i] = i;
        rc = pthread_create(&threads[i], NULL, PrintHello, (void*)&(indexes[i]));
        if(rc)
        {
            cout << "Error，无法创建线程，" << rc << endl;
        }
    }
    pthread_exit(NULL);
}