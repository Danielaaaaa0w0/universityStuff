#include <stdio.h>
int main(){
	int a, b;
	FILE *input = fopen("../input/1.txt", "r");
	fscanf(input, "%d %d", &a, &b);
	fclose(input);
	//a = a * b;
	asm volatile (
		"mul %[a], %[a], %[b]" // Inline assembly to multiply a by b
		: [a] "+r" (a)   // Output operand: a is modified, +r indicates it's read/write
		: [b] "r" (b)    // Input operand: b is read-only
	);
	printf("%d\n", a);
	return 0;
}


