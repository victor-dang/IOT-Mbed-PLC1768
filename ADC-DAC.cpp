#include "mbed.h"
AnalogIn Ain(p20); //object definitions
AnalogOut Aout(p18);
PwmOut Buzzer(p22);
//AnalogIn delay_pot(p16);
//AnalogIn feedback_pot(p17);
InterruptIn record_btn(p10);
InterruptIn play_btn(p12);
Serial pc(USBTX, USBRX); //enable serial port which links to USB 
Ticker s20khz_tick;
void s20khz_task(void); // function prototypes
#define MAX_BUFFER 1400 // max data samples
signed short data_in; // signed allows positive and negative
unsigned short data_out; // unsigned just allows positive values
float delay=10;
float feedback=10;
signed short buffer[MAX_BUFFER]={0}; // define buffer and set values to 0
int i=0;
void ISR1()
{
    pc.printf("\r\n record button was pressed! recording ....\r\n");
    s20khz_tick.attach_us(&s20khz_task,50);
}
void ISR2()
{
    pc.printf("\r\n play button was pressed! playing ....\r\n");
    for(int j=0;j<=i;j++){
    data_out=buffer[j]+0x7FFF; // output buffer data value
    Aout.write_u16(data_out); // write output
    pc.printf("\r\n buffer out: %d",data_out);
    }
} 
//main program start here
int main() {
    pc.printf("\r\n\r\n");
    pc.printf("=================================\r\n");
    pc.printf("=================================\r\n");
    record_btn.rise(&ISR1); // attach the address of the ISR function to the
    // interrupt rising edge  
    play_btn.rise(&ISR2);
    //s20khz_tick.attach_us(&s20khz_task,50);
    while(1){
        }
}
// function 20khz_task
void s20khz_task(void){
    data_in=Ain.read_u16()-0x7FFF; // read data and normalise
    buffer[i]=data_in+(buffer[i]*feedback); // add data to buffer data
    //data_out=buffer[i]+0x7FFF; // output buffer data value
    //Aout.write_u16(data_out); // write output
    if (i>(delay)){ // if delay loop has completed
    i=0; // reset counter
    //delay=delay_pot*MAX_BUFFER; // calculate new delay buffer size
    //feedback=(1-feedback_pot)*0.9; // calculate feedback gain value
    }else{
    i=i+1; // otherwise increment delay counter
    }
}
