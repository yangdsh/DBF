#include <cstdio>

int main(){
    FILE *fpA = fopen("A_input.txt", "w");
    for (int i = 1; i <= 20000; ++i){
        fprintf(fpA, "%d\n", i);
    }
    fclose(fpA);
    FILE *fpB = fopen("B_input.txt", "w");
    for (int i = 20001; i <= 40000; ++i){
        fprintf(fpB, "%d\n", i);
    }
    fclose(fpB);
    return 0;
}
