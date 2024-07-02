#include <stdio.h>
int main ()
{
    int a[10] = {0}, b[10]= {0}, c[10] = {0}; 
    int i, arr_size = 10;
    FILE *input = fopen("../input/2.txt", "r");
    for(i = 0; i < arr_size; i++) fscanf(input, "%d", &a[i]);
    for(i = 0; i < arr_size; i++) fscanf(input, "%d", &b[i]);
    for(i = 0; i < arr_size; i++) fscanf(input, "%d", &c[i]);
    fclose(input);
    int *p_a = &a[0];
    int *p_b = &b[0];
    int *p_c = &c[0];
    /* Original C code segment
    for (int i = 0; i < arr_size; i++){
    *p_c++ = *p_a++ * *p_b++;
    }
    */
for (int i = 0; i < arr_size; i++) {
    asm volatile(
        "lw t1, 0(%0)\n"    // Load a[i] into t1
        "lw t2, 0(%1)\n"    // Load b[i] into t2
        "mul t3, t1, t2\n"  // Multiply a[i] and b[i], result stored in t3
        "sw t3, 0(%2)\n"    // Store the result in c[i]
        "addi %0, %0, 4\n"  // Increment p_a by 4 (since each int is 4 bytes)
        "addi %1, %1, 4\n"  // Increment p_b by 4
        "addi %2, %2, 4\n"  // Increment p_c by 4
        : "+r"(p_a), "+r"(p_b), "+r"(p_c)
        :
        : "t1", "t2", "t3"
    );
}
    p_c = &c[0];
    for (int i = 0; i < arr_size; i++)
    printf("%d ", *p_c++);
    printf("\n");
    return 0;
}
