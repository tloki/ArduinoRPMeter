#define MEASURE_PERIOD 1000   // measuring period, in this commit also a report period, in miliseconds
#define LPF_ALPHA 1.0         // low-pass-filter alpha value, as in [result = alpha * (new_measure) + (1.0 - alpha) * (old_result)].
                              // should be value in range <0.0 and 1.0], 1.0 meaning only new value is considered.
                              // in that case measures could be noisy (especially in low measure/report period scenarios)

#define INPUT_PIN             // this pin should support interrupts, and not interfere with timer Uno/Nano: [todo] Mega: [todo] pins
                              // also, do not measure pulses of amplitudes higher than 5.1V. This program should work with anything between 2.7V and 5.1V 

/* TODO:
- measure and report periods should be different constants
- add support for different sensors, right now measures only by digital input is supported

Tomislav Lokotar, Youth Research Center, July, 2017 http://icm.hr/
tomislav.lokotar@fer.hr

DO NOT CHANGE ANYHING BELOW THIS LINE
*/

void setup()
  {
  // put your setup code here, to run once:
  }

void loop()
  {
  // put your main code here, to run repeatedly:
  }
