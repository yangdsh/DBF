#include "../Common Files/config.hpp"

#include "../Common Files/typefwd.hpp"
#include "../Common Files/config.hpp"

#include "../ShBF/shiftbf.hpp"
#include "../vBF/kbf.hpp"
#include "../DBF/djbf.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
using namespace std;

#include <sys/time.h>

const int w = BF_WIDE;
const int k = BF_HASH_FUNCTION_NUM;

static shiftBF *sbf;
static double swrong[SET_NUM];
static uint32_t sum_sw;

static KBF *kbf;
static double kwrong[SET_NUM];
static uint32_t sum_kw;

static DJBF *djbf;
static double djwrong[SET_NUM];
static uint32_t sum_djw;
static vector<unsigned char *> data[SET_NUM+1];
static vector<uint32_t> length[SET_NUM+1];
static char s[1000];

void read(){
	FILE *infile;
	char *infile_name = new char[100];
	for (uint8_t g = 0; g < SET_NUM; ++g){
        sprintf(infile_name, "../data/input%hhu.txt", g);
        infile = fopen(infile_name, "r");
        while (fscanf(infile, "%s", s) != EOF){
            uint32_t l = strlen(s);
            length[g].push_back(l);
            unsigned char *ts = new unsigned char[l];
            memcpy(ts, s, l);
            data[g].push_back(ts);
        }
        fclose(infile);
    }
    delete []infile_name;
}

void sbf_test(){
	sbf = new shiftBF(w, k);
    for (uint8_t g = 0; g < SET_NUM; ++g){
        uint32_t n = length[g].size();
        for (uint32_t i = 0; i < n; ++i){
            sbf -> insert(g, data[g][i], length[g][i]);
        }
    }
    for (uint8_t g = 0; g < SET_NUM; ++g){
		uint32_t wrong = 0;
        uint32_t n = length[g].size();
        for (uint32_t i = 0; i < n; ++i){
			int r = sbf -> search(data[g][i], length[g][i]);
            if (r != g) ++wrong;
		}
		if (n != 0)
	    	swrong[g] = (double)wrong / n;
		sum_sw += wrong;
    }
    delete sbf;
}

void kbf_test(){
	kbf = new KBF(w, k);
    for (uint8_t g = 0; g < SET_NUM; ++g){
        uint32_t n = length[g].size();
        for (uint32_t i = 0; i < n; ++i)
            kbf -> insert(g, data[g][i], length[g][i]);
    }
    
    for (uint8_t g = 0; g < SET_NUM; ++g){
		uint32_t wrong = 0;
        uint32_t n = length[g].size();
		for (uint32_t i = 0; i < n; ++i){
			int r = kbf -> search(data[g][i], length[g][i]);
			if (r != g) ++wrong;
		}
		if (n != 0)
			kwrong[g] = (double)wrong / n;
		sum_kw += wrong;
    }
    delete kbf;
}

void djbf_test(){
	djbf = new DJBF(w, k+10);
	
    for (uint8_t g = 0; g < SET_NUM; ++g){
        uint32_t n = length[g].size();
        for (uint32_t i = 0; i < n; ++i)
			djbf -> insert(g, data[g][i], length[g][i]);
    }
		
    djbf -> insert_finish();
    
    for (uint8_t g = 0; g < SET_NUM; ++g){
		uint32_t wrong = 0;
        uint32_t n = length[g].size();
		for (uint32_t i = 0; i < n; ++i){
			int r = djbf -> search(data[g][i], length[g][i]);
            if (r != g) ++wrong;
		}
		if (n != 0)
		  djwrong[g] = (double)wrong / n;
		sum_djw += wrong;
    }
    delete djbf;
}

/*
void write(){
	FILE *outfile = fopen("../result/multiset_WA.txt", "w");
	for (uint8_t g = 0; g < SET_NUM; ++g)
	  fprintf(outfile, "%3hhu%13.7lf%13.7lf%13.7lf\n", g, djwrong[g], kwrong[g], swrong[g]);
	fclose(outfile);
}

void write(){
	FILE *outfile = fopen("../result/proportion.txt", "a");
	double p = (double)length[0].size() / (length[0].size() + length[1].size());
    uint32_t s = 0;
	for (uint8_t g = 0; g < SET_NUM; ++g)
	  s += length[g].size();
	
    fprintf(outfile, "%.6lf%11.6lf%11.6lf%11.6lf\n", p, 
					(double)sum_djw / s,
					(double)sum_kw / s,
					(double)sum_sw / s
	);
	fclose(outfile);
}
*/

void write(){
	FILE *outfile = fopen("../result/multiset_WA_rate_n.txt", "a");
	uint32_t s = 0;
	for (uint8_t g = 0; g < SET_NUM; ++g)
	  s += length[g].size();

	fprintf(outfile, "%6u%15.10lf%15.10lf%15.10lf\n", s / SET_NUM, 
			(double)sum_djw / s,
			(double)sum_kw / s,
			(double)sum_sw / s
	);
	fclose(outfile);
}


int main(){
	read();
	puts("1");
	sbf_test();
	puts("2");
	kbf_test();
	puts("3");
	djbf_test();
	puts("4");
	write();
	return 0;
}
