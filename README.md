# OpenAUTOS
Vehicular Operating System implementing the OSEK/VDX standard. 

Initial plans for the library had a much broader scope and there were plans to support the AutoSAR OS industry standard, but due to restricted time constrains, those plans were put to rest, at least for now.

The library also was designed with concepts of cross-platform support in mind but it only offers support for Microchip's PIC18F25k80 microcontrollers at the moment.

# Showcasing through Little McQueen

Little McQueen was the name given to the RC car built specifically to showcase the OpenAUTOS OS in action to my thesis defence committee.

A list of features implemented in this project (all of them being controled by the OS) were:
  * Velocity control through a slider on the cellphone and PWM on the vehicle's DC motor;
  * Direction control through the cellphones velocimeter and a servomotor on the vehicle's front wheels;
  * LED activation groups include:
    * Rear lights are automatically activated when the car is in reverse;
    * Left/Right turn signals automatically blink, through the use of a soft-timer;
    * Headlights are a simple On/Off switch on the controller.

All of these features are showcased in this video: https://youtu.be/aofbh7Vu_KI

This other video, at an earlier stage, shows the custom board being tested: https://youtu.be/Coepr_hbfWQ

## A little backstory on Little McQueen

One week prior to my thesis defense, all I had to show to the judging committee was a board with some blinking lights, that were supposed to illustrate the activation of different functionalities of the OpenAUTOS Operating System. Although me and my coordinator were sure they would comprehend that the main effort was put into creating an OS from scratch, we both knew it was lacking (badly) in the visual appeal department.

Later that night, while talking to some of my friends from the Robotics's laboratory, I mentioned that I could program an RC car that would showcase the capabilities of the OS in a much better way than what I had so far (blinking lights on a board), but that I would not be able to deliver it with a custom board and a cellphone remote control until the day of my defense. At that moment, *Thiago Raulino Dal Pont* and *Cristiano Abreu* both offered to help me with those specific tasks.

From this point onward, I was developing the custom firmware for the vehicle, while guiding Cristiano and Thiago on how they should customize their parts in order to fit everything together by the end of the week.

The final result coudn't have been better, and this was easily my most exciting moment during this undergraduate program. The results impressed all the watchers that were present in my thesis defense, and all of this would not be achievable in that limited timeframe without the help and the teamwork of multiple people.

So I engrave here my most special thanks to:
 * Professor Anderson Luiz Fernandes Perez for guiding me through this adventure;
 * Thiago Raulino Dal Pont for creating the cellphone controller app;
 * Cristiano Abreu for designing and soldering the car's custom board;
 * Alan Kunz Cechinel for helping me test and record the videos;

This project would not be possible to be delivered on time without your help.
