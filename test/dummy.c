#include "pico_stack.h"

#if defined(PICO_SUPPORT_RTOS) || defined (PICO_SUPPORT_PTHREAD)
volatile uint32_t pico_ms_tick;
#endif

int main(void)
{
    struct pico_stack *stack = NULL;
    pico_stack_init(&stack);
    pico_stack_tick(stack);
    return 0;
}
