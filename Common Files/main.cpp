#include <cstdio>

#include <sys/time.h>




#include "BOBHash.hpp"


BOBHash hf;

int h[10000000];

static double GetCurrentTime(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec / (double)1000000;
}

int main(){
    hf.initialize(10);
    
    double t = GetCurrentTime();
    for (int i = 1; i <= 100000000; ++i)
		hf.run((const unsigned char *)"100", 3);
	double t1 = GetCurrentTime() - t;
	
	int p = 0;
	int s;
	     t = GetCurrentTime();
	for( int j = 1; j <= 10010;  ++ j)
	for (int i = j; i <= 10000000; i += 1001){
		s = h[i];
	}
		double t2 = GetCurrentTime() - t;
	
	printf("%.6lf\n%.6lf\n", t1, t2);
	return 0;
}

	
	

	
