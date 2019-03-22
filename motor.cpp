#include "mbed.h"
#include "string"

PwmOut motor(p21);
DigitalOut myled(LED1);
Serial pc(USBTX, USBRX); //enable serial port which links to USB 
AnalogIn sensor(p15); //LM35 sensor
float current_pulse = 0;
float offset = 0;
Ticker  in;
void motor_speed(float offset)
{
    //current_pulse += offset;
    motor = offset;
} 
float getTemperature(){
        int i,N=400;
        float tempC, avg, a[N]; 
        myled = 1;
        avg = 0;
        
        for(i=0;i<N;i++)
        {
            a[i]=sensor.read();
            
            wait(.01);
        }
        for(i=0;i<N;i++)
        {
            
            avg=avg+(a[i]/10*1000); 
            
        }
        tempC = (avg/N*10);
        pc.printf("\n\rTemperature is %4.1f C, avg = %4.5f  \r\n",tempC, avg/N);

    return tempC;
}
int main() {
    
    motor.period(0.01);
    motor = 0;
    float tempC, threshold = 15;
    string err_str;
    pc.printf("\r\nLM35 Temperature Program");
    pc.printf("\r\n******************\r\n");
    wait(1); // wait 1 second for device stable status
    while (1) {
        
        tempC = getTemperature();
        
            
            if(tempC >= threshold)
            {
                offset = tempC - threshold + 0.5;
                motor_speed(offset);                  
            }
            else
            {
                offset = 0;
                motor_speed(offset);
            }
            pc.printf("\n\r pulse width %f, offest = %f \r\n",motor.read(), offset);
             
        myled = 0;
        wait(1);
    }
    
}

