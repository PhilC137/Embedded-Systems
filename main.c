#include "start.h"
#include <stdlib.h>


/*// polling
	volatile uint32_t i = 0;
	
	while(1)
	{
		// a little delay

		// check if button pressed and if turn led on else off
		// attention: no debouncing.
		if (REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << BLUE_BUTTON))
		{
			REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BLUE_LED);
		}
		else
		{
			REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);
		}
	}
}*/

typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))


const uint32_t GPIO_BASE = 0x10012000;
const uint32_t GPIO_PUE = 0x10;
const uint32_t GPIO_INPUT_EN = 0x4;
const uint32_t GPIO_INPUT_VAL = 0x0;

const uint32_t GPIO_OUTPUT_EN = 0x8;
const uint32_t GPIO_OUTPUT_VAL = 0xc;
const uint32_t GPIO_IOF_EN = 0x38;

const uint32_t GREEN_LED = 18;
const uint32_t BLUE_LED = 21;
const uint32_t YELLOW_LED = 0;
const uint32_t RED_LED = 3;

const uint32_t GREEN_BUTTON = 19;
const uint32_t BLUE_BUTTON = 20;
const uint32_t YELLOW_BUTTON = 1;
const uint32_t RED_BUTTON = 2;

const uint32_t BUTTON = 18;

const uint32_t T_SHORT = 300000;
const uint32_t T_LONG = 2*T_SHORT;
const uint32_t T_VERY_LONG = 2 * T_LONG;



int n = 3;
int count = 0;

int main (void){
	setup();
	game();
}

void game(){
	while (1)
		{
			if (bereitschaftsmodus() == 1)
			{	
				midGame();
			}
		}
	}

void midGame(){
	wait(T_SHORT);
	vorfuehrphase();
	wait(T_SHORT);
	nachahmphase();
}


void setup(){
	// setup Green LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << GREEN_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << GREEN_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << GREEN_LED;

	// setup Green BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << GREEN_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << GREEN_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << GREEN_BUTTON;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << GREEN_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << GREEN_BUTTON);



	// setup Blue LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << BLUE_LED;


	// setup Blue BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << BLUE_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << BLUE_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << BLUE_BUTTON;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << BLUE_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BLUE_BUTTON);



	// setup Yellow LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << YELLOW_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << YELLOW_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << YELLOW_LED;

	// setup Yellow BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << YELLOW_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << YELLOW_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << YELLOW_BUTTON;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << YELLOW_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << YELLOW_BUTTON);



	// setup Red LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << RED_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << RED_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << RED_LED;

	// setup Red BUTTON as input
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << RED_BUTTON);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << RED_BUTTON;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << RED_BUTTON;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << RED_BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << RED_BUTTON);
}
void on(int x){
	if (x == 0){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << GREEN_LED); 
	}
	else if (x == 1){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << BLUE_LED); 
	}
	else if (x == 2){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << YELLOW_LED); 
	}
	else if (x == 3){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) |= (1u << RED_LED); 
	}
}
void off(int x){

	if (x == 0){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << GREEN_LED); 
	}
	else if (x == 1){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << BLUE_LED); 
	}
	else if (x == 2){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << YELLOW_LED); 
	}
	else if (x == 3){
		REG(GPIO_BASE+GPIO_OUTPUT_VAL) &= ~(1u << RED_LED); 
	}
}
void wait(uint32_t time){
for (int i = 0; i < time; i++){

	}
}
int button(){

	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << GREEN_BUTTON))){
		printf("GREEN\n\n");
		return 0;
	}
	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << BLUE_BUTTON))){
		printf("BLUE\n\n");
		return 1;
	}
	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << YELLOW_BUTTON))){
		printf("YELLOW\n\n");
		return 2;
	}
	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << RED_BUTTON))){
		printf("RED\n\n");
		return 3;
	}


}

int bereitschaftsmodus(){
	
	while (1)
	{
		on(0); // Grüne Lampe umschalten
        wait(T_SHORT);
        off(0);

		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << GREEN_BUTTON))){
			return 1;
		}

        on(1); // Blaue Lampe umschalten
        wait(T_SHORT);
        off(1);

		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << GREEN_BUTTON))){
			return 1;
		}

        on(2);// Gelbe Lampe umschalten
        wait(T_SHORT);
        off(2);

		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << GREEN_BUTTON))){
			return 1;
		}

        on(3); // Rote Lampe umschalten
        wait(T_SHORT);
        off(3);


		if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << GREEN_BUTTON))){
			return 1;
		}

			
	
		
	}
	
	
}


void vorfuehrphase(){
	
	printf("vorfuehrphase\n\n");

	on(1);
	on(2);
	wait(T_SHORT);
	off(1);
	off(2);

	wait(T_SHORT);
	
	volatile int count = 0;
	while (count < n)
	{
		printf("int n = %d\n\n", n);
		printf("int count = %d\n\n", count);	
		
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

	printf("ENDE vorfuehrphase\n\n"); 
	

}


void randomeLedOn(int count){

	int randome_number = rand() % 4;

	if(randome_number == 0){
		printf("GREEN LED ON\n\n");
		on(0);
		wait(T_SHORT);
		off(0);
			}
	else if (randome_number == 1){
		printf("BLUE LED ON\n\n");
		on(1);
		wait(T_SHORT);
		off(1);
			}
	else if (randome_number == 2){
		printf("YELLOW ON\n\n");
		on(2);
		wait(T_SHORT);
		off(2);
	}
			
	else if (randome_number == 3){
		printf("RED ON\n\n");
		on(3);
		wait(T_SHORT);
		off(3);
	}

	List[count] = randome_number;

	wait(T_SHORT);
	

}


void nachahmphase(){

	printf("Nachahmphase\n\n");
	for(int j=0; j < n; j ++){	
		wait(T_LONG);
		printf("DU BRAUCHST %d\n\n",List[j]);
		int ans = NULL;
		ans = button();
		printf("DIE ANTWORT %d\n\n",ans);
		if(ans != List[j]){
			printf("Verloren\n\n");
			verloren();
		} else {
			printf("Richtig\n\n");
			on(List[j]);
			wait(T_SHORT);
			off(List[j]);
		}
	}

	wait(T_SHORT);
	zwischensequenz();

}

void verloren(){

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
	int result = n - 3;

	if (result >= 8){
		result -= 8;
		on(0);
	}
	if (result >= 4){
		result -= 4;
		on(1);
	}
	if (result >= 2){
		result -= 2;
		on(2);
	}
	if (result >= 1){
		result -= 1;
		on(3);
	}

	wait(T_VERY_LONG);

	off(4);
	off(3);
	off(2);
	off(1);

	game();


}

void zwischensequenz(){
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


	if(n==13){
		main();
	} else {
		n ++;
		midGame();
	}

	

}

void endmodus(){
	on(0);
	on(1);
	on(2);
	on(3);
	wait(T_SHORT);
	off(0);
	off(1);
	off(2);
	off(3);
	wait(T_SHORT);

	on(0);
	on(1);
	on(2);
	on(3);
	wait(T_SHORT);
	off(0);
	off(1);
	off(2);
	off(3);
	wait(T_LONG);

	on(0);
	on(1);
	on(2);
	on(3);
	wait(T_SHORT);
	off(0);
	off(1);
	off(2);
	off(3);
	wait(T_SHORT);

	on(0);
	on(1);
	on(2);
	on(3);
}
