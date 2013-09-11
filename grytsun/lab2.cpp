#include <thread>
#include <future>
#include <iostream>
#include <cstdlib>
#include <ctime>

std::promise<int> f_res;
std::promise<int> g_res;

//if x argument for f function falls in range [INTMIN,10) then result is undefined,
//if arg x in range [10,20] then result is true
//if arg x in range (20,INTMAX] then result is false
void f(int x){
	f_res.set_value(-1);
	if(x<10){
		while(true){}
	}
	else{
		if(x<20) f_res.set_value(1);
		else f_res.set_value(0);
	}
}

//if x for g function falls in range [INTMIN,10) then result is true,
//if arg in range [10,20] then result is false
//if arg x in range (20,INTMAX] then result is undefined
void g(int x){
	g_res.set_value(-1);
	if(x<10) g_res.set_value(1);
	else{
		if(x<20) g_res.set_value(0);
		else{
			while(true){}
		}
	}
}

void foo(int x){
	std::cout << "HEllo";
}

int main(int argc, char* argv[]){

	if(argc < 3){
		std::cout << "not enough args" << std::endl;
		return 0;
	}
	
	int f_arg = atoi(argv[1]);
	int g_arg = atoi(argv[2]);
	std::cout << "Arguments: " << f_arg << ' ' << g_arg << std::endl;

	std::future<int> f_future = f_res.get_future();
	std::future<int> g_future = g_res.get_future();
	
	std::thread first(foo,f_arg);
	std::thread second(foo,g_arg);
	
	time_t timer = time(NULL);
	std::cout << "computations running concurently" << std::endl;
	
	int f_int = f_future.get();
	int g_int = g_future.get();
	if(f_int == 0 || g_int == 0){
		std::cout << "Result: false" << std::endl;
		return 0;
	}
	if(f_int == 1 && g_int == 1){
		std::cout << "Result: true" << std::endl;
		return 0;
	}
	char ans;
	while(true){
		if((time(NULL) - timer) >= 10000){
			timer = time(NULL);
			std::cout << "not answering, continue?" << std::endl;
			std::cin >> ans;
			if(ans == 'n' || ans == 'N'){
				std::cout << "Result: undefined" << std::endl;
				return 0;
			}
		}
	}
	return 0;
}
