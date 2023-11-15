#include "wrap.h"
#include "startup.h"
#include <stdlib.h>

typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))

static volatile uint32_t i = 0;

void on(uint32_t num);
void off(uint32_t num);
static void setup(void);
static uint32_t button(void);
static uint32_t bereitschaftsmodus(void);
void wait(uint32_t num);
static void vorfuehrphase( void );
static void randomeLedOn(uint32_t num);
static void nachahmphase(void);
static void verloren(void);
void game(void);
static void midGame(void);
static void endmodus(void);
static void zwischensequenz(void);


extern uint32_t GPIO_BASE;
uint32_t GPIO_BASE = 0x10012000u;
extern uint32_t GPIO_PUE;
uint32_t GPIO_PUE = 0x10u;
extern uint32_t GPIO_INPUT_EN;
uint32_t GPIO_INPUT_EN = 0x4u;
extern uint32_t GPIO_INPUT_VAL;
uint32_t GPIO_INPUT_VAL = 0x0;
extern uint32_t GPIO_OUTPUT_EN; 
uint32_t GPIO_OUTPUT_EN = 0x8u;
extern uint32_t GPIO_OUTPUT_VAL;
uint32_t GPIO_OUTPUT_VAL = 0xcu;
extern uint32_t GPIO_IOF_EN;
uint32_t GPIO_IOF_EN = 0x38u;

static const uint32_t GREEN_LED = 18u;
static const uint32_t BLUE_LED = 21u;
static const uint32_t YELLOW_LED = 0u;
static const uint32_t RED_LED = 3u;
static const uint32_t GREEN_BUTTON = 19u;
static const uint32_t BLUE_BUTTON = 20u;
static const uint32_t YELLOW_BUTTON = 1u;
static const uint32_t RED_BUTTON = 2u;
static const uint32_t T_SHORT = 300000u;
static const uint32_t T_LONG = 2u*T_SHORT;
extern uint32_t T_VERY_LONG;
uint32_t T_VERY_LONG = 4u* T_SHORT;


static uint32_t List[13];

extern uint32_t n;
uint32_t n=3;

int main ( void ){
	setup();
	game();
	return 0;
}

void game( void ){
	while (1)
		{
			if (bereitschaftsmodus() == 1u)
			{	
				midGame();
			}
		}
	}

void midGame( void ){
	wait(T_SHORT);
	vorfuehrphase();
	wait(T_SHORT);
	nachahmphase();
}


void setup( void ){
	// setup Green LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << GREEN_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1u << GREEN_LED);
	//REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1u << GREEN_LED;

	// setup Green BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << GREEN_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1u << GREEN_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1u << GREEN_BUTTON;
	//REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1u << GREEN_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1u << GREEN_BUTTON);



	// setup Blue LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << BLUE_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1u << BLUE_LED);
	//REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1u << BLUE_LED;


	// setup Blue BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << BLUE_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1u << BLUE_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1u << BLUE_BUTTON;
	//REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1u << BLUE_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1u << BLUE_BUTTON);



	// setup Yellow LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << YELLOW_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1u << YELLOW_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1u << YELLOW_LED;

	// setup Yellow BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << YELLOW_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1u << YELLOW_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1u << YELLOW_BUTTON;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1u << YELLOW_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1u << YELLOW_BUTTON);



	// setup Red LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << RED_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1u << RED_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1u << RED_LED;

	// setup Red BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << RED_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1u << RED_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1u << RED_BUTTON;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1u<< RED_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1u << RED_BUTTON);
}

void on(uint32_t x){
	if (x == 0u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << GREEN_LED); 
	}
	else if (x == 1u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << BLUE_LED); 
	}
	else if (x == 2u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << YELLOW_LED); 
	}
	else if (x == 3u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << RED_LED); 
	} else {}
}
void off(uint32_t x){

	if (x == 0u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << GREEN_LED); 
	}
	else if (x == 1u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << BLUE_LED); 
	}
	else if (x == 2u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << YELLOW_LED); 
	}
	else if (x == 3u){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << RED_LED); 
	} else {}
}
void wait(uint32_t time){

for (i = 0; i < time; i++){
	}
};
uint32_t button( void ){

	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << GREEN_BUTTON))){
		
		return 0u;
	}
	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << BLUE_BUTTON))){
		
		return 1u;
	}
	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << YELLOW_BUTTON))){
		
		return 2u;
	}
	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << RED_BUTTON))){
		
		return 3u;
	} 
	return -1u;
}

uint32_t bereitschaftsmodus( void ){
	
	while (1)
	{
		on(0); // Grüne Lampe umschalten
        wait(T_SHORT);
        off(0);

		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << GREEN_BUTTON))){
			return 1u;
		}

        on(1); // Blaue Lampe umschalten
        wait(T_SHORT);
        off(1);

		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << GREEN_BUTTON))){
			return 1u;
		}

        on(2);// Gelbe Lampe umschalten
        wait(T_SHORT);
        off(2);

		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << GREEN_BUTTON))){
			return 1u;
		}

        on(3); // Rote Lampe umschalten
        wait(T_SHORT);
        off(3);


		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << GREEN_BUTTON))){
			return 1u;
		}

			
	
		
	}
	
	
}


void vorfuehrphase( void ){

	on(1u);
	on(2u);
	wait(T_SHORT);
	off(1u);
	off(2u);

	wait(T_SHORT);
	volatile uint32_t count = 0u;
	while (count < n)
	{
		randomeLedOn(count);
		count++;
	}
	

		
	on(0);
	on(1);
	on(2);
	on(3);

	wait(T_SHORT);

	off(0);
	off(1);
	off(2);
	off(3);		

}


void randomeLedOn( uint32_t counter ){

	uint32_t randome_number = rand() % 4;

	if(randome_number == 0u){
		on(0u);
		wait(T_SHORT);
		off(0u);
			}
	else if (randome_number == 1u){
		on(1u);
		wait(T_SHORT);
		off(1u);
			}
	else if (randome_number == 2u){
		on(2u);
		wait(T_SHORT);
		off(2u);
	}
			
	//actualy not always true
	else{
		on(3u);
		wait(T_SHORT);
		off(3u);
	}

	List[counter] = randome_number;

	wait(T_SHORT);
	

}


void nachahmphase( void ){
	for(i=0; i < n; i ++){	
		wait(T_LONG);
	
		uint32_t ans = 0u;
		ans = button();

		if(ans != List[i]){

			verloren();
		} else {

			on(List[i]);
			wait(T_SHORT);
			off(List[i]);
		}
	}

	wait(T_SHORT);
	zwischensequenz();

}

void verloren( void ){

	n=3;
	on(0);
	on(3);
	wait(T_SHORT);
	off(0);
	off(3);
	wait(T_SHORT);
	on(0);
	on(3);
	wait(T_SHORT);
	off(0);
	off(3);
	wait(T_SHORT);


	//Green = 1, Blue = 2, Yellow = 4, Red = 8;
	//Needed to light up the binary code
	uint32_t result = n - 3u;

	if (result >= 8u){
		result -= 8u;
		on(0);
	}
	if (result >= 4u){
		result -= 4u;
		on(1);
	}
	if (result >= 2u){
		result -= 2u;
		on(2);
	}
	if (result >= 1u){
		on(3);
	}

	wait(T_VERY_LONG);

	off(4);
	off(3);
	off(2);
	off(1);

	game();
}

void zwischensequenz( void ){
	on(0);
	on(2);
	wait(T_SHORT);
	off(0);
	off(2);
	on(1);
	on(3);
	wait(T_SHORT);
	on(0);
	on(2);
	off(1);
	off(3);
	wait(T_SHORT);
	off(0);
	off(2);
	on(1);
	on(3);
	wait(T_SHORT);
	off(1);
	off(3);


	if(n==13u){
		endmodus();
		
	} else {
		n ++;
		midGame();
	}

	

}

void endmodus( void ){
	on(0u);
	on(1u);
	on(2u);
	on(3u);
	wait(T_SHORT);
	off(0u);
	off(1u);
	off(2u);
	off(3u);
	wait(T_SHORT);

	on(0u);
	on(1u);
	on(2u);
	on(3u);
	wait(T_SHORT);
	off(0u);
	off(1u);
	off(2u);
	off(3u);
	wait(T_LONG);

	on(0u);
	on(1u);
	on(2u);
	on(3u);
	wait(T_SHORT);
	off(0u);
	off(1u);
	off(2u);
	off(3u);
	wait(T_SHORT);

	on(0u);
	on(1u);
	on(2u);
	on(3u);

	midGame();
}
