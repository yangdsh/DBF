#include "../Common Files/config.hpp"

#include "../Common Files/typefwd.hpp"

#include "../DBF/djbf.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
using namespace std;

const int w = BF_WIDE;
const int k = BF_HASH_FUNCTION_NUM;

static DJBF *djbf;
static uint32_t djwrong[SET_NUM];
static uint32_t dj_ins_fail[SET_NUM];

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

void djbf_test(){
	djbf = new DJBF(w, k+10);
	
    for (uint8_t g = 0; g < SET_NUM; ++g){
        uint32_t n = length[g].size();
        for (uint32_t i = 0; i < n; ++i)
			djbf -> insert(g, data[g][i], length[g][i]);
    }
		
    djbf -> insert_finish(dj_ins_fail);
	    
    for (uint8_t g = 0; g < SET_NUM; ++g){
		uint32_t wrong = 0;
        uint32_t n = length[g].size();
		for (uint32_t i = 0; i < n; ++i){
			int r = djbf -> search(data[g][i], length[g][i]);
            if (r != g) ++wrong;
		}
		djwrong[g] = wrong;
    }
    delete djbf;
}

void write(){
	FILE *outfile = fopen("../result/multiset_WA.txt", "w");
	
	for (uint8_t g = 0; g < SET_NUM; ++g){
	  uint32_t n = length[g].size();
	  if (n == 0)
		fprintf(outfile, "%3hhu%13s%13s\n", g, "NaN", "NaN");
       else
	    fprintf(outfile, "%3hhu%13.7lf%13.7lf\n", g, 
					(double)djwrong[g] / n, 
					(double)dj_ins_fail[g] / n
		);
	}
	fclose(outfile);
}

int main(){
	read();
	puts("3");
	djbf_test();
	puts("4");
	write();
	return 0;
}
