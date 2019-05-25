//Makro definition to *10Us delay

#define delay10US(us) do {                       \
  asm volatile ("MOV R0,%[loops]\n                 \
                 1: \n                             \
                 SUB R0, #1\n                      \
                 CMP R0, #0\n                      \
                 BNE 1b \t"                        \
                : : [loops] "r" (5*us) : "memory" \
               );                                  \
} while(0)