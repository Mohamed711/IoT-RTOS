typedef void (*FnPtr)(void);

extern void timerInit();
extern void timerStart(uint32_t timeInMillis, FnPtr timeoutFn);
extern void timerDelay(uint32_t timeInMillis);
extern void timerStop();
