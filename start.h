/* dummy include */
#ifndef STARTUP_H
#define STARTUP_H

static int List[13];

typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))



void on(int);
void off(int);
void setup();
int button();
int bereitschaftsmodus();
void wait(uint32_t);
void vorfuehrphase();
void randomeLedOn(int);
void nachahmphase();
void verloren();
void game();
void midGame();

#endif