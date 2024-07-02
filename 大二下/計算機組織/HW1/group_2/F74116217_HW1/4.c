#include<stdio.h>

int main() { 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);

    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];

    /*
    // original code
    for (i = 0; i < 3; i++) {
        p_x = &x[0];
        for (int j = 0; j < 2; j++) {
            p_h = &h[i * 3];
            for (int f = 0; f < 3; f++) {
                *p_y += *p_x++ * *p_h++;
                p_x++;
            }
            p_x = &x[1];
            p_y++;
        }
    }    
    */

    asm volatile(
        "addi s1, zero, 0\n"// s1 = i          
        "addi s4, zero, 3\n"// s4 = 3
        "addi s5, zero, 2\n"// s5 = 2
        "addi s6, zero, 12\n"// s6 = 12
        "add a0, zero, %[p_x]\n"// a0 = &x[0]
        "addi a1, a0, 4\n"// a1 = &x[1]
        "add a2, zero, %[p_h]\n"// a2 = &h[0]

        "outer_loop:\n"
            "bge s1, s4, outer_done\n"// if (i >= 3) goto outer_done
            "mv %[p_x], a0\n"// p_x = &x[0]

            "addi s2, zero, 0\n"// s2 = j  
            "inner_loop:\n"
                "bge s2, s5, inner_done\n"// if (j >= 2) goto inner_done
                "mul t0, s1, s6\n"// t0 = offset i * 3
                "add t0, t0, a2\n"// t0 = &h[i * 3]
                "mv %[p_h], t0\n"// p_h = &h[i * 3]
                
                "addi s3, zero, 0\n"// s3 = f
                "innermost_loop:\n"
                    "bge s3, s4, innermost_done\n"// if (f >= 3) goto innermost_done
                    "lw t1, (%[p_x])\n"// load *p_x
                    "lw t2, (%[p_h])\n"// load *p_h
                    "mul t1, t1, t2\n"// t1 now stores *p_x * *p_h
                    "addi %[p_x], %[p_x], 4\n"// increment p_x
                    "addi %[p_h], %[p_h], 4\n"// increment p_h                    
                    "lw t2, (%[p_y])\n"// load *p_y
                    "add t2, t2, t1\n"// *p_y += result
                    "sw t2, (%[p_y])\n"// store *p_y"
                    "addi %[p_x], %[p_x], 4\n"// increment p_x again
                    "addi s3, s3, 1\n"// increment f
                    "j innermost_loop\n"// goto innermost_loop

                "innermost_done:\n"
                    "mv %[p_x], a1\n"// p_x = &x[1]
                    "addi %[p_y], %[p_y], 4\n"// increment p_y
                    "addi s2, s2, 1\n"// increment j
                    "j inner_loop\n"// goto inner_loop

            "inner_done:\n"
                "addi s1, s1, 1\n"// increment i
                "j outer_loop\n"// goto outer_loop

        "outer_done:\n"

        :[p_x] "+r" (p_x), [p_h] "+r" (p_h), [p_y] "+r" (p_y)
        :
        : "s1", "s2", "s3", "s4", "s5", "s6", "a0", "a1", "a2", "t0", "t1", "t2"
    );

	p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
}
