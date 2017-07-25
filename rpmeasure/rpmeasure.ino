#include <Arduino.h>
#define MEASURE_PERIOD 1000   // measuring period, in this commit also a report period, in miliseconds
#define LPF_ALPHA 1.0         // low-pass-filter alpha value, as in [result = alpha * (new_measure) + (1.0 - alpha) * (old_result)].
                              // should be value in range <0.0 and 1.0], 1.0 meaning only new value is considered.
                              // in that case measures could be noisy (especially in low measure/report period scenarios)

#define INPUT_PIN 2           // this pin should support interrupts, and should not interfere with other interrupt libraryes:

                              // Uno, Nano, Mini, other 328-based PINS:	2, 3
                              // 
                              // Mega, Mega2560, MegaADK PINS:	2, 3, 18, 19, 20, 21
                              // also, do not measure pulses of amplitudes higher than 5.1V. This program should work with anything between 2.7V and 5.1V

#define SERIAL_BAUD 115200   // Serial speed. Highest possible speed is preffered, to interferre with other interrupt-sensitive actions as little as possible                   
#define LED_PIN 13

/* TODO:
- measure and report periods should be different constants
- add support for different sensors, right now measures only by digital input is supported

Tomislav Lokotar, Youth Research Center, July, 2017 http://icm.hr/
tomislav.lokotar@fer.hr

DO NOT CHANGE ANYHING BELOW THIS LINE
*/

unsigned long long global_rpm_counter = 0;
float lpf_rpm = 0;

void ISRHigh()
    {
    noInterrupts();
    global_rpm_counter += 1;
    //detachInterrupt(digitalPinToInterrupt(INPUT_PIN));
    //attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ISRLow, FALLING);
    detachInterrupt(INPUT_PIN);
    attachInterrupt(INPUT_PIN, ISRLow, FALLING);
    digitalWrite(LED_PIN, HIGH);
    interrupts();
    return;
    }

void ISRLow()
    {
    noInterrupts();
    //detachInterrupt(digitalPinToInterrupt(INPUT_PIN));
    //attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ISRHigh, RISING);
    detachInterrupt(INPUT_PIN);
    attachInterrupt(INPUT_PIN, ISRHigh, RISING);
    digitalWrite(LED_PIN, LOW);
    interrupts();
    return;
    }

void setup()
    {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    Serial.begin(SERIAL_BAUD);
    //attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ISRHigh, RISING));
    attachInterrupt(INPUT_PIN, ISRHigh, RISING);
    }

void loop()
    {
    delay(MEASURE_PERIOD);
    float rpm = (float) global_rpm_counter / MEASURE_PERIOD;
    lpf_rpm = (float) LPF_ALPHA * (rpm) + (1.0 - LPF_ALPHA) * (lpf_rpm);
    global_rpm_counter = 0;  
    
    /*
    detachInterrupt(digitalPinToInterrupt(INPUT_PIN));
    Serial.println(lpf_rpm);
    if(global_rpm_counter > 0) // to gain some precision
        {
        //attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ISRLow, FALLING));
        attachInterrupt(INPUT_PIN, ISRLow, FALLING));
        } 
    else
        {
        //attachInterrupt(digitalPinToInterrupt(INPUT_PIN), ISRHigh, RISING));
        attachInterrupt(INPUT_PIN, ISRHigh, RISING));
        }
    */
    
    Serial.println(rpm);
    }
