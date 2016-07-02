typedef void (*FnPtr)(void);

extern void Timer_Init();
extern void Timer_Start(uint32_t timeInMillis, FnPtr timeoutFn);
extern void Timer_Delay(uint32_t timeInMillis);
extern void Timer_Stop();
void Timer_New(FnPtr timeoutFn, uint32_t time);
