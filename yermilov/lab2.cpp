#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

bool fReady = false;
int fResult = -1;

bool gReady = false;
int gResult = -1;

void* f (void* ptr) {
    int x = *((int*)ptr);
    printf("Computing f...\n");
    if (x == 0) {
        fReady = true;
        fResult = 0;
    } else if (x > 0) {
        fReady = true;
        fResult = x;
    } else {
        while(true) { }  
    }
}

void* g(void* ptr){
    int x = *((int*)ptr);
    printf("Computing g...\n");
    if (x == 0) {
        gReady = true;
        gResult = 0;
    } else if (x > 0) {
        gReady = true;
        gResult = x;
    } else {
        while(true) { }  
    }
}

bool retrieveResult() {
     if (fReady && fResult == 0) {
        printf("0\n");
        return true;
     }
     if (gReady && gResult == 0) {
        printf("0\n");
        return true;
     }
     if (fReady && gReady) {
        printf("%d\n", fResult * gResult);
        return true;
     }
     return false;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Missing arguments");
        return 1;
    }

    int argForF = atoi(argv[1]), argForG = atoi(argv[2]);
    pthread_t threadForF, threadForG;

    pthread_create(&threadForF, NULL, &f, (void*)&argForF);
    pthread_create(&threadForG, NULL, &g, (void*)&argForG);
        
    time_t timer = time(NULL);
        
    bool resultReady = retrieveResult();
    if (resultReady) return 0;

    char ans;
    while(true) {
        if ((time(NULL) - timer) >= 2) {
            resultReady = retrieveResult();
            if(resultReady) return 0;

            printf("Continue?\n");
            scanf("%c", &ans);
            if(ans == 'n' || ans == 'N'){
                printf("undefined\n");
                return 0;
            }

            timer = time(NULL);
        }
    }

    return 0;
}
