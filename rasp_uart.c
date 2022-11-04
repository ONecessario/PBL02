#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#define BAUD_RATE 9600
#define NODEMCU_STATE 3
#define ANALOGIC 4
#define DIGITAL 5
#define LED 6

extern void init();
extern void write_char(char ch);
extern void clear_display();

int main (void) {
	int serial_port;
	init();
	if ((serial_port = serialOpen ("/dev/ttyS0", BAUD_RATE)) < 0) {
        fprintf (stderr, "Incapaz de abrir o dispositivo serial: %s\n", strerror (errno)) ;
        return 1 ;
  	}

  	if (wiringPiSetup () == -1) {
        fprintf (stdout, "Incapaz de iniciar a biblioteca wiringPi: %s\n", strerror (errno)) ;
        return 1;
  	}
 	while(1){
		printf("Selecione entre estas opcoes:\n");
		printf("1 - Estado Atual\n");
		printf("2 - Digital\n");
        printf("3 - Analogico\n\n");
		int option = scanf("%i", &option);
		if(serialDataAvail (serial_port) ) {
			switch(option) {
				case 1:
                    read(serial_port, NODEMCU_STATE);
				break;

				case 2:
                    read(serial_port, DIGITAL);
				break;

				case 3:
                    read(serial_port, ANALOGIC);
				break;
			}

		}
	}

}

void read(int port, int option) {
    serialPutchar(port, option);
    sleep();
    write(serialGetchar(port));
}

void write(char c) {
    write_char(c);
    printf("%d\n", c);
    fflush(stdout);
}
