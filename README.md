# ChromeDinoSimulator
We wanted to take computer games to the next level by adding some interaction to them and for this task we chose the dinosaur game that appears each time there is no internet connection, our idea was to allow the player to play this game not only through pressing some buttons on his/her keyboard but actually through jumping in real life, so the player has to actually jump in order to skip the cactus and win the game.

Sensors and parts used:

●	1 IR sensor

●	1 LDR Sensor

●	Field Programmable Gate Array ( FPGA )

●	Arduino Uno

●	1 LED

●	1 Servo Towerpower SG90 Motor 

●	1 10k ohm resistor


The implementation :

  General code implementation was constructed through several entities. Some of those entities have sub-entities.
  
  The vhdl file has 5 entities (XboxLite, CounterOn, ConvertBCD, MotorCTRL, and Servo). The VHDL code begins from XboxLite
  entity which is the main entity 3 inputs (1 for LDR sensor , 1 for IR sensor, 1 for 10 Mhz clock) and 3 outputs (LED , 7 Segment display and Servo Motor) as shown in the figurebelow.

  ![image](https://user-images.githubusercontent.com/68373114/149662533-8aef5ba8-768a-4335-bce0-23e226398049.png)
  
➠	XboxLite Entity

  It consists - as mentioned before - of 3 inputs and 3 outputs. 2 of the 3 inputs are used in other entities (which are IR sensor  and 10MHZ clock) but the third input has been operated in this entity where it informs the player when exactly to jump on turning on the LED directly. The LDR sensor stands for Light dependent resistor. It is used where there is a need to sense the presence and absence of light. Moreover it gives high values when it’s kept in front of any light emission and gives low values when dim. The LDR sensor has been used directly on any PC monitor and senses if there is very high contrast of light or not. 

 ![image](https://user-images.githubusercontent.com/68373114/149662591-74a34750-bf91-42b7-9076-af5bff20ca47.png)

In our game, the LDR sensor will sense the background sensor and give high values (700 - 900) where it will feed the FPGA with a logic 0. When it hits a cactus the values will be dropped down (400 - 600) and feed the FPGA with logic 1 to turn on the LED. (in the figure above).
Moreover, XboxLite consists of 2 components which are MotorCTRL and CounterOn which will be discussed later.

➠	CounterOn Entity

For CounterOn  Entity the input is the jump  (one bit) that comes from the IR sensor, and the output is num (16 bit ) could be displayed and processed on 2 digit 7 segments.

For the architecture  there is a signal temp (8 bits are all zeros)  which is divided to the most right 4 bits for units and the most left 4 bits for tens . then a process that take the jump as an input, in this process if jump input equals ‘1’ we check if the units bits (the most right 4 bits) if there are less than 9 we will increment it by one , if there are more than 9 we increment tens bits by one and make the units bits equals zero.
After that we give the units bits (the most right 4 bits in signal temp) as an input for the convertBCD  which give us the 7 segment code for units digit  to put it in the most right 8 bits in the output num and give the tens bits  (the most left 4 bits for signal temp) as an input for the convertBCD  which gives us the 7 segment code for tens digit to put it in the most left 8 bits in the output num.

➠	convertBCD  Entity

For convertBCD  Entity the input is the s (four bits) that comes from the CounterOn entity either for units bits or for tens bits, and the output is o(8 bits) that is a code for one digit 7 segment display.

For the architecture there is a case statement because every input s gives a distinctive  7 segment code as an output, and this output is complemented as if the bit equals ‘1’ so its corresponding segment is off and if it equals ‘0’ its corresponding segment is on.


➠	MotorCTRL Entity

The FPGA controls the Servo motor through PWM control (stands for pulse with modulation). The PWM control is a powerful technique for controlling analog circuits with a microcontroller’s digital output. It is basically a digital unipolar square wave signal where the duration of the ON time can be modulated as desired.
The figure below shows a typical PWM signal. The ON and the OFF times are sometimes referred to as the MARK (or M) and SPACE (or S) times of the signal, respectively. Here, we are interested in three parameters: signal amplitude, signal frequency (or period), and the signal duty cycle.
The amplitude is usually fixed by the logic 1 level of the microcontroller output which depends on the power supply which is 5v in our case.
The frequency depends on the application. In this project, we will generate a PWM signal with a frequency of 10MHz that’s why we need clk with this frequency as an input in our entity.
The duty cycle, denoted by D, is the ratio of the ON time to the period of the signal, i.e. D = M/T. D can range from 0 to 1 and is sometimes expressed as a percentage, i.e. from 0% to 100%. The power supplied to the load is controlled by varying the duty cycle.

![image](https://user-images.githubusercontent.com/68373114/149663118-625856cc-609a-4da3-b824-099454054941.png)

In this entity we have two main input which are IR sensor signal and 10MHZ clk. On changing the value of the clk the pwm gets triggered and send signals to the servo motor according the angle desired where the default value of the servo motor torque angle is 0 (0 degree) and when it is triggered it moves to the desired position or angle which is 85 (60 degree).
In design perspective, when the IR sensor is pointed to the ground, it always feeds to the MotorCTRL entity with logic 0 where no action won’t be taken by the FPGA otherwise, it takes the selected angle which is declared in the motor positioning. As shown in the figure below

![image](https://user-images.githubusercontent.com/68373114/149663135-07bd19bd-a989-4bb6-9509-25f11a662913.png)






 
 


  

