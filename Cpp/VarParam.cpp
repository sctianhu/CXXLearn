#include <iostream>
#include <stdarg.h>
#include <stdlib.h>

using namespace std;

int sum(char  *msg, ... );
int my_vsprintf(char *buf,char *format, ... );

int main()
{
	sum("the sum of the list is : ", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0);
	cout <<endl;
	char buffer[256] = {};
	my_vsprintf(buffer,"%My name is %s and I am %d years old.", "Ben", 24);
	cout<<buffer<<endl;

	system("pause");
	return 0;
}

int sum(char *msg, ... )
{
	va_list st;
	va_start(st,msg);
	int total = 0;
	int tmp ;

	while((tmp = va_arg(st,int)) != 0)
	{
		total += tmp;
	}
	va_end(st);
	cout<<"the sum of the list is : "<<total;

	return 0;
}

int my_vsprintf(char *buf,char *format, ... )
{
	va_list st;
	va_start(st,format);
	vsprintf(buf,format,st);
	va_end(st);

	return 0;
}