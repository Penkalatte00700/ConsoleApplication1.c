#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int a;
int b;

printf("Enter a");
fgets(a, sizeof(a), stdin);

printf("Enter b");
fgets(b, sizeof(b), stdin);

if (a > b) {
	printf("a is bigger than b");
}
else if (b > a) {
	printf("b is bigger than a");
}
else {
	printf("a and b equal");
}

printf("Enter command: 1 for sum, 2 for division, 3 for multiplication");
fgetch(stdin);

switch (command) {
case 1: {
	printf(a + b);
	break;
}
case 2:
	printf(a / b)
		break;
case 3: {
	printf(a * b);
	break;
}
case 0:
	return 0;
default:
	printf("Unknown command\n");
	break;
}

while (a > b) {
	a--;
	printf("a is bigger than b");
}
do while (a < b) {
	a++;
	printf("a is smaller than b");
}

for (int i = 0; i < 10; i++) {
	if (i % 2 == 0) {
		continue;
	}
	else {
		printf(i);
	}
}

int main() {
	int x = 10;

	printf("In outer scope:", x);
	{
		int x = 20;
		printf("In inner scope:", x);
	}
	printf("In outer scope again:", x);
	return 0;
}
