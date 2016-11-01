#include "../Common Files/config.hpp"

#include <cstdio>

int main(){
#if !(SET_NUM == 2)
	FILE *outfile;
	static char outfile_name[200];
	int l = 0, r = 0;
	for (int g = 0; g < SET_NUM; ++g){
		sprintf(outfile_name, "../data/input%d.txt", g);
		outfile = fopen(outfile_name, "w");
		
		l = r; r = l + SET_ELEM_CNT;
		for (int i = l; i < r; ++i)
		  fprintf(outfile, "%d\n", i);
		
		fclose(outfile);
	}
#else
	FILE *outfile = fopen("../data/input0.txt", "w");
    int l = ELEM_START, r = l + A_SET_ELEM_CNT;
    for (int i = l; i < r; ++i)
      fprintf(outfile, "%d\n", i);
    fclose(outfile);
    
    outfile = fopen("../data/input1.txt", "w");
    l = r; r = l + B_SET_ELEM_CNT;
    for (int i = l; i < r; ++i)
      fprintf(outfile, "%d\n", i);
    fclose(outfile);
    
    outfile = fopen("../data/input2.txt", "w");
    l = r; r = l + OUT_OF_SET_ELEM_CNT;
    for (int i = l; i < r; ++i)
	  fprintf(outfile, "%d\n", i);
	fclose(outfile);
#endif
    return 0;
}

