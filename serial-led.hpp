#ifndef serial_led_h
#define serial_led_h

extern char pinOutputs[4];
extern char selectedPinOutput;


void ledInit(void);
void ledPulse(void);
void ledFlash(void);

void ledCommand(char c);

#endif //serial_led_h