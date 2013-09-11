#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <time.h>

int g_res = -1;
int f_res = -1;

//if x argument for f function falls in range [INTMIN,10) then result is undefined,
//if arg x in range [10,20] then result is true
//if arg x in range (20,INTMAX] then result is false
void* f(void* ptr){
	int x = *((int*)ptr);
	printf("Computing function F\n");
	if(x<10){
		while(true){}
	}
	else{
		if(x<20) f_res = 1;
		else f_res = 0;
	}
}

//if x for g function falls in range [INTMIN,10) then result is true,
//if arg in range [10,20] then result is false
//if arg x in range (20,INTMAX] then result is undefined
void* g(void* ptr){
	int x = *((int*)ptr);
	printf("Computing function G\n");
	if(x<10) g_res = 1;
	else{
		if(x<20) g_res = 0;
		else{
			while(true){}
		}
	}
}

bool get_res(){
	if(f_res == 0 || g_res == 0){	
		printf("Result: false\n");
		return true;
	}
	if(f_res == 1 && g_res == 1){
		printf("Result: true\n");
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	if( argc < 3){
		printf("Not enough arguments for program");
		return 0;
	}

	int arg1 = atoi(argv[1]), arg2 = atoi(argv[2]);
	pthread_t first, second;
	int err1 = pthread_create(&first, NULL, &f, (void*)&arg1);
	int err2 = pthread_create(&second, NULL, &g, (void*)&arg2);
	
	time_t timer = time(NULL);
	
	bool is_valid_res = get_res();
	if(is_valid_res) return 0;

	char ans;
	while(true){
		if((time(NULL) - timer) >= 2){
			is_valid_res = get_res();
			if(is_valid_res) return 0;
			printf("Not answering, continue?\n");
			scanf("%c",&ans);
			if(ans == 'n' || ans == 'N'){
				printf("Result: undefined\n");
				return 0;
			}
			timer = time(NULL);
		}
	}

	//pthread_join(first,NULL);
	//pthread_join(second,NULL);
	return 0;
}
