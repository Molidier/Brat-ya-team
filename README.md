# Reverse plastic-accepting vending machine

Moldir Azhimukhanbet, moldir.azhimukhanbet@nu.edu.kz

Kamila Spanova, kamila.spanova@nu.edu.kz

Rassul Mukhambetkali, rassul.mukhambetkali@nu.edu.kz


<h2>1. Introduction</h2>

The main goal of our project is to make a reverse plastic-accepting vending machine that takes plastic bottles from the users, counts their amount, and gives back different promo codes according to the number of
bottles submitted. For example, if the user submitted less than 3 bottles, then they will get the “choco” promo code. There are “tea”, and “coffee” promo codes available also, which could be received by submitting
more than 3 or 7 bottles, respectively.  If the container is full, the machine will not work, until it gets empty. Furthermore, it handles the case when the input device detects an object at the moment it gets
through the hole but does not fall down to the doors of the motors, so the counter will not be triggered nor incremented. The start and end of the operations of inserting the bottles will be identified by the value
of states of the “start” and “stop” buttons.
    
## 2. Materials and methods

1. Arduino MEGA 2560 R3
2. Breadboard
3. Foam Board
4. HS-322HD Deluxe Servo x2
5. Ultrasonic Distance Sensor - HC-SR04 x3
6. HC-SR501 Passive Infrared (PIR) sensor
7. LCD Display (I2C LCD1602)
8. Vex bumper switch

## 3. Results
<p align="center">
<img src= https://github.com/Molidier/Brat-ya-team/assets/73649370/86ad983f-3858-4f1b-bd30-80260844d62f >
         <b><i>Figure 1. Scheme of the reverse plastic-accepting vending machine </i></b>
</p>

The circled numbers in Figure 1 represent the corresponding ordered hardware components from Materials and methods.

<p align="center">
<img width = "300" src=https://github.com/Molidier/Reverse-plastic-accepting-vending-machine-Brat-ya-team-/assets/73649370/263398d9-6b66-4f1e-bf11-d45798f36676 >
</p>

<p align="center">
<b><i>Figure 2. Picture of the  final machine</i></b>

</p>



### Description of the work:
The front side of our machine can be seen in Figure 2 presented above. The Arduino and the sensors used are hidden inside the container in such a way that all the parts are attached to the inner side of the front wall so that the container is almost hollow inside.  The operation of loading plastic bottles to the machine will start only after pressing the “start” button. Initially, the LCD displays the “Press the start button”, and when the user starts the operation, it is altered to “Count: ” and outputs the number of the bottles loaded, which equals 0 at the beginning. Then, due to its motion, the presence of the bottle is detected by the PIR sensor, and, additionally, the Distance Sensor, which measures the change in the distance from the roof of the opening hole to the opening doors. After the bottle has been detected, the doors open thanks to the servo motors that temporarily change their angle of position. When the bottle falls down the container, it will affect the distance between the second Distance Sensor and the side wall, so that is when the counter of the bottles loaded by one user increments. At that time, the value of the counter increments on the LCD as well. The counter stops counting bottles after the user presses the “end” button. After that, the caption “Wait for promo” will be depicted on the LCD display, then, for the duration of 10 seconds the promo code for a specific reward will be shown as “Promo code: ” and the name corresponding to the number of bottles loaded. In case the container gets filled up by the bottles, the third Distance sensor will identify that the height of the top of the cumulated content of the box has reached almost the same horizontal position as the motors.


### Video link: 
https://drive.google.com/file/d/1TgS2UtJ76bkeadOgplVJaVyKijo_BtX6/view?usp=sharing 

## 4. Student contributions
Rassul Mukhambetkali has worked with the motors and made a fundament for the hardware with the use of foam board. 
Moldir Azhimukhanbet and Kamila Spanova have worked with the other parts of the software, designed the project, and tested all parts of the hardware.
