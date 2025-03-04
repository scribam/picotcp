#define EXISTING_TIMERS 9


START_TEST (test_timers)
{
    uint32_t T[128];
    int i;
    struct pico_timer_ref *tref;
    struct pico_stack *S;

    pico_stack_init(&S);

    for (i = 0; i < 128; i++) {
        pico_time expire = (pico_time)(999999 + i);
        void (*timer)(pico_time, void *) =(void (*)(pico_time, void *))0xff00 + i;
        void *arg = ((void*)0xaa00 + i);

        T[i] = pico_timer_add(S, expire, timer, arg);
        printf("New timer %u\n", T[i]);
    }
    for (i = 0; i < 128; i++) {
        void (*timer)(pico_time, void *) =(void (*)(pico_time, void *))0xff00 + i;
        void *arg = ((void*)0xaa00 + i);

        fail_if((uint32_t)(i + 1) > S->Timers->n);
        tref = heap_get_element(S->Timers, (uint32_t)i + EXISTING_TIMERS);
        fail_unless(tref->id == T[i]);
        fail_unless(tref->tmr->timer == timer);
        fail_unless(tref->tmr->arg == arg);
    }
    for (i = 127; i >= 0; i--) {
        printf("Deleting timer %d \n", i );
        pico_timer_cancel(S, T[i]);
        printf("Deleted timer %d \n", i );
        tref = heap_get_element(S->Timers, (uint32_t)i + EXISTING_TIMERS);
        fail_unless(tref->tmr == NULL);
    }
    pico_stack_tick(S);
    pico_stack_tick(S);
    pico_stack_tick(S);
    pico_stack_tick(S);
}
END_TEST
