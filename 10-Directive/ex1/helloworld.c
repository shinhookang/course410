#include<stdio.h>

int main(){
    #pragma acc parallel loop
    for (int i=0; i < 10; ++i){
        printf("Hello World! %d\n", i);
    }
    return 0;
}
