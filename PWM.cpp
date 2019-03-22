#include "mbed.h"
PwmOut red_led(p21);
Serial pc(USBTX, USBRX); //enable serial port which links to USB 
int main() {

    red_led.period(0.01);          // red_led requires a 20ms period
    red_led.pulsewidth(0.00999);
    
    pc.printf("\r\n Program is started!\r\n");
    while (1) {
        //for(float offset=0.0; offset<0.01; offset+=0.006) {
            //red_led.pulsewidth(0.001 + offset);
            pc.printf("\n\r Pulse width = %f\r\n",red_led.read());
        //red_led.pulsewidth(0.15);
        //red_led.write(0.75);
            wait(10);
        //}
        red_led.pulsewidth(0);
        pc.printf("\n\r Reset Pulse width = %f\r\n",red_led.read());
        wait(5);
        red_led.pulsewidth(0.00999);
    }
}
