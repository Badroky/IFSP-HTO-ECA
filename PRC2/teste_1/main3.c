#include <stdio.h>

int a=0;

void incrementa() {
    int b = 0;
    static int c = 0;

    printf("a: %d, b: %d, c: %d\n", a, b, c);
    a++;
    b++;
    c++;
}

int main(){
    int i;
    for(i=0; i<5; i++){
        incrementa();
    }
    return 0;
}