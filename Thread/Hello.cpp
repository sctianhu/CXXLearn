#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <condition_variable>

#include "template_fun_forward.h"

#include "NoCopyObj.h"

void thread_task(){
	std::cout<<"hello thread "<<std::endl;
}

void function1(int n){
	std::cout<<"enter function1 " <<std::endl;
	for (int i = 0; i < 5; ++i)
	{
		std::cout<<"Thread "<<n<<" executing \n";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	std::cout<<"leave function1 " <<std::endl;
}

void function2(int& n){

	std::cout<<"enter function2 " <<std::endl;
	for (int i = 0; i < 5; ++i)
	{
		std::cout<<" Thread 2 executing \n";
		++n ;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	std::cout<<"leave function2" <<std::endl;
}

volatile int counter(0);
std::mutex mtx;

void attempt_10k_increase( ){
	for (int i = 0; i < 10000; ++i)
	{
		if(mtx.try_lock()){
			++counter;
			mtx.unlock();
		}
	}
}

bool IsPrime(int x){
	std::cout<<"calculating please, waiting ... \n";
	
	for (int i = 2; i < x; ++i) {
		if(x%i == 0 ){
			return false;
		}
	}

	return true;
}

std::condition_variable cv;
int value;
bool ready = false;

void ReadValue( ){
	std::cin>> value;
	cv.notify_one();
}

void PrintId(int id){
	std::unique_lock<std::mutex> lck(mtx);
	std::cout<<"enter PrintId "<<std::endl;
	while(!ready){
		cv.wait(lck);
	}

	std::cout<<"thread "<<id<<'\n';
}

void Go(){
	std::unique_lock<std::mutex> lck(mtx);
	std::cout<<"notify all enter "<<std::endl;
	std::notify_all_at_thread_exit(cv,std::move(lck));
	std::cout<<"notify all leave "<<std::endl;
	ready = true;
}

std::atomic<int> global_counter(0);

void increase_global(int n){
	for (int i = 0; i < n; ++i)
	{
		++global_counter;
	}
}

void increase_reference(std::atomic<int>& variable,int n){
	for (int i = 0; i < n; ++i)
	{
		++variable;
	}
}

struct C : std::atomic<int> {
	C():std::atomic<int>(0) {}
	void increase_member(int n){
		for (int i = 0; i < n; ++i)
		{
			fetch_add(1);
		}
	}
};

#include "DynamicSort.h"
#include "IsVoid.h"
#include "StringTopoSort.h"

int testfun(int a)
{
	printf("%d\n", a);
	return 2;
}

class CA{
public:
	void fun(int a){ std::cout<<a ;}
};

int main(int argc, const char *argv[]){

	MMap<char,int,MMapComp< pair<char,int> > > test;

	test.insert(make_pair('D',1));
	test.insert(make_pair('D',2));
	test.insert(make_pair('B',3));
	test.insert(make_pair('A',4));

	for(auto & a : test ){
		cout<<a.first<<"\t"<<a.second<<endl;
	}

	// function_forward<int (int) > f1(&testfun);
	// f1(5);
	CA a;
	function_forward<void (CA::*)(int)> f(&CA::fun,&a);

	f(5);

	std::cout << is_void<void>().value ;

	vector<string> headers[] = {
		{"A","B","C"} ,
		{"B","D"} ,
		{"C"} ,
		{"D","C"}
	};
	StringTopoSort sorter(headers,4);
	vector<string> sorted = sorter.string_topo_sort();

	for(int i = 0; i < sorted.size(); i++ ){
		cout<<sorted[i] << " -- ";
	}
	cout<<endl;
	

	return 0;
}

	// std::thread t(thread_task);
	// t.join();

	// return EXIT_SUCCESS;

	// int n = 0;
	// std::cout<<"create t1 enter"<<std::endl;
	// std::thread t1;
	// std::cout<<"create t1 exit"<<std::endl;

	// std::cout<<"create t2 enter"<<std::endl;
	// std::thread t2(function1,n+1);
	// std::cout<<"create t2 exit"<<std::endl;

	// std::cout<<"create t3 enter"<<std::endl;
	// std::thread t3(function2,std::ref(n));
	// std::cout<<"create t3 exit"<<std::endl;

	// std::cout<<"create t4 enter"<<std::endl;
	// std::thread t4(std::move(t3));
	// std::cout<<"create t4 exit"<<std::endl;

	// t2.join();
	// t4.join();

	// std::cout<<"final value of n is "<< n <<'\n';

	// std::thread threads[10];
	// for (int i = 0; i < 10; ++i)
	// {
	// 	threads[i] = std::thread(attempt_10k_increase);
	// }

	// for(auto& t : threads ){
	// 	t.join();
	// }

	// std::cout<<counter<<" successful increase of the counter . \n";

	/*delete 拷贝构造函数测试 and move 构造函数*/
	// NoCopyObj nocpy;
	// NoCopyObj no2 = std::move(nocpy);

	// std::future<bool> fut = std::async(std::launch::async,IsPrime,313222313);
	// std::cout<<" checking whether 313222313 is prime .\n ";
	
	// bool ret = fut.get();

	// if(ret){
	// 	std::cout<<"it is prime \n .";
	// }else{
	// 	std::cout<<"it is not prime. \n";
	// }

	// std::cout<<"Please enter a integer(I'll be printng dots):";
	// std::thread th(ReadValue);

	// std::mutex mtx;
	// std::unique_lock<std::mutex> lck(mtx);
	// while(cv.wait_for(lck,std::chrono::seconds(1)) == std::cv_status::timeout){
	// 	std::cout<<'.'<<std::flush;
	// }
	// std::cout<<"You entered : "<<value <<'\n';

	// th.join();

	// std::thread threads[10];
	// for(int i = 0; i < 10 ; i++){
	// 	threads[i] = std::thread(PrintId,i);
	// }
	// std::cout<<"10 thread ready to race ... \n";

	// std::thread(Go).detach();

	// for(auto& t :threads ){
	// 	t.join();
	// }


	// std::vector<std::thread> threads;

	// std::cout<<"increase global counter with 10 threads .... \n";
	// for (int i = 0; i <= 10; ++i) {
	// 	threads.push_back(std::thread(increase_global,1000));
	// }

	// std::cout<<"increase counter (foo) with 10 threads using reference ... \n";
	// std::atomic<int> foo(0);
	// for (int i = 0; i <= 10; ++i)
	// {
	// 	threads.push_back(std::thread(increase_reference,std::ref(foo),1000));
	// }

	// std::cout<<"increase counter (bar) with 10 threads using memeber ... \n";
	// C bar;
	// for (int i = 0; i <= 10; ++i)
	// {
	// 	//threads.push_back(std::thread(&C::increase_member,std::ref(bar),1000));
	// }

	// std::cout<<"synchronizing all threads .... \n";
	// for(auto& t : threads){
	// 	t.join();
	// }

 	//  std::cout << "global_counter: " << global_counter << '\n';
 	//  std::cout << "foo: " << foo << '\n';
 	//  std::cout << "bar: " << bar << '\n';
