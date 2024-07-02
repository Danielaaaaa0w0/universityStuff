"li t1, 0\n\t"
"li t3, -1\n\t"     
"addi %[lw_cnt], %[lw_cnt], 2\n\t"

"loop:\n\t"
	"add t2, zero, t1\n\t"
	"addi %[add_cnt], %[add_cnt], 1\n\t"
	
    "slli t2, t2, 1\n\t"
    "addi %[others_cnt], %[others_cnt], 1\n\t"
    
    "addi t2, t2, 1\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    
    "fcvt.d.w f2, t2\n\t"
    "neg t3, t3\n\t"  
    "fcvt.d.w f1, t3\n\t"
    "addi %[others_cnt], %[others_cnt], 3\n\t"
    
    "fdiv.d f1, f1, f2\n\t"
    "addi %[div_cnt], %[div_cnt], 1\n\t"
    
    "fadd.d %[pi], %[pi], f1\n\t"
    "addi t1, t1, 1\n\t"
    "addi %[add_cnt], %[add_cnt], 2\n\t"
    
    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "blt t1, %[N], loop\n\t"
