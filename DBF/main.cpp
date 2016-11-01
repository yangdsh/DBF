#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "djbf.hpp"

int range[] = {
    0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000
};

const int n = (sizeof(range) / sizeof(*range)) - 1;

int right[n];

int main(){
    const int k = 18;
    const int w = (int)(144500);
    
    DJBF filter(w, k);

    char data[100]; uint32_t length;
    
    for (uint8_t g = 0; g < n; ++g)
      for (int i = range[g]; i < range[g+1]; ++i){
        sprintf(data, "%d", i);
        length = strlen(data);
        filter.insert(g, (unsigned char *)data, length);
      }
    filter.insert_finish();
    
    for (uint8_t g = 0; g < n; ++g){
      for (int i = range[g]; i < range[g+1]; ++i){
        sprintf(data, "%d", i);
        length = strlen(data);
        int r = filter.search((unsigned char *)data, length);
        if (r == g) ++right[g];
      }
      printf("right[%hhd] = %d\n", g, right[g]);
    }

/*
    int miss = 0;
    for (int i = 1000000; i < 1100000; ++i){
      sprintf(data, "%d", i);
      length = strlen(data);
      int r = filter.search((unsigned char *)data, length);
      if (r == -1) ++miss;
    }
    printf("miss = %d\n", miss);
*/
    
    return 0;
}