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

In our game, the LDR sensor will sense the background sensor and give high values (700~900) where it will feed the FPGA with a logic 0. When it hits a cactus the values will be dropped down (400~600) and feed the FPGA with logic 1 to turn on the LED. (in the figure above).
Moreover, XboxLite consists of 2 components which are MotorCTRL and CounterOn which will be discussed later. 

 
 


  

