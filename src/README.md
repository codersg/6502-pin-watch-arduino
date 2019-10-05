# 6502 CPU PIN Monitor

This projects is for anyone who's hooking up a 6502 processor in their own project (such as on a Breadboard) and just wants to be able to monitor the values on the Address Bus and Data Bus. Typically you can do this by placing a bunch of LEDs on the board, but who can do 16-bit binary translation in their head? ..well, maybe some of you, but certainly not me. One alternative is to use a Logic Analyser, but those are damn expensive and for me at least, too much trouble. So why not make use of an Arduino? Anyone pluggin 6502's into a breadboard is likely to have an Arduino laying around somewhere! So connect all the output pins from the 6502 to the Arduino and let it show you what's going on.

# Example

Below shows how you can connect the Address Bus, Data Bus, Read/Write and Clock Signal to the Arduino.
You could use the Arduino to provide the clock, or to use the clock as a signal to generate an interrupt and read the Address Bus and Data Bus. In this project, the clock is assumed to be external, and the Arduino is using it as a trigger to read the buses.

![](/images/6502_wiring_bb.png)



