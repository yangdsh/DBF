#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "kbf.hpp"

int range[] = {
    0, 1000000, 2000000
};

const int n = (sizeof(range) / sizeof(*range)) - 1;

int right[n];

int main(){
    const int k = 10;
    const int w = 28900000 ;
    
    KBF filter(w, k);

    char data[100]; uint32_t length;
/* 
    FILE *fpA = fopen("A_input.txt", "r");
    while (fscanf(fpA, "%s", data) != EOF){
          length = strlen(data);
          filter.insert(0, (unsigned char *)data, length);
    }
    fclose(fpA);

    FILE *fpB = fopen("B_input.txt", "r");
    while (fscanf(fpB, "%s", data) != EOF){
          length = strlen(data);
          filter.insert(1, (unsigned char *)data, length);
    }
    fclose(fpB);
*/

    
    for (uint8_t g = 0; g < n; ++g)
      for (int i = range[g]; i < range[g+1]; ++i){
        sprintf(data, "%d", i);
        length = strlen(data);
        filter.insert(g, (unsigned char *)data, length);
      }

    for (uint8_t g = 0; g < n; ++g){
      for (int i = range[g]; i < range[g+1]; ++i){
        sprintf(data, "%d", i);
        length = strlen(data);
        int r = filter.search((unsigned char *)data, length);
        if (r == g) ++right[g];
      }
      printf("right[%hhd] = %d\n", g, right[g]);
    }
    return 0;
}