#include <stdio.h>

#define MAX_BUFF 40000
#define uint unsigned int

uint buff[MAX_BUFF];
int len = 0;

void printnum() {
    int i;
    printf("%u", buff[len]);
    for (i = len-1; i >= 0; i--)
        printf("%04u", buff[i]);
    printf("\n");
}

void multiply(uint n) {
    unsigned long i, q, r = 0;
    for (i = 0; i <= len; i++) {
        q = (buff[i] * n + r);
        buff[i] =  q % 10000;
        r = q / 10000;
    }
    while (r != 0) {
        buff[i] = r % 10000;
        r /= 10000;
        len++;
    }
}

void factorial() {
    uint n, i;
    len = 0;
    buff[0] = 1;
    printf("Enter a number:");
    scanf("%u", &n);
    for(i=1; i<=n; i++) {
	multiply(i);
    }
    printf("factorial(%d) = ", n);
    printnum();
}

void exponentiation() {
    int n, i;
    len = 0;
    buff[0] = 1;
    printf("Enter a number:");
    scanf("%d", &n);
    int k = (n>>13)<<13;
    for(i=0; i<k; i+=13) {
	multiply(1<<13);
    }
    for(;i<n;i++)
	multiply(2);
    printf("2^%d = ", n);
    printnum();
}
int main() {
    int ch;
    do {
	printf("What should i do?\n");
	printf("1. Factorial\n");
	printf("2. Exponentiation\n");
	printf("3. Exit\n");
	printf("Enter your choice:");
	scanf("%d", &ch);
	switch(ch) {
	case 1:
	    factorial();
	    break;
	case 2:
	    exponentiation();
	    break;
	case 3:
	    printf("Bye!\n");
	    break;
	default:
	    printf("Invalid option. Please Reselect\n");
	    break;
	}
    }while(ch!=3);
    return 0;
}
