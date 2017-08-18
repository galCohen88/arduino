# Gals' Arduino Projects

Servo controlled by wifi
https://youtu.be/JGj9tMbddVU

Slider potentiometer logging to sd card
https://www.youtube.com/watch?v=WN422QPnU6o


###### **In the world of VMs and containers, there is something neat and beautiful in embedded code**

## Why I started this?

I heard about arduino few years ago in uni. The only thing I knew about it that it uses C as its programming language.
The motivation when started was creating a remote controlled servo opening my office door.

## Why not raspberry pi?
Raspberry Pi is great, but the idea of running code on another OS was not charming as running embedded code.
(nothing against linux - I love it, I use it by daily basis). 

## Hardware
**Arduino board**

I'm using Arduino uno r3. Why did i choose this model? mainly because it was in stock, and recommended by the community.

**WIFI shield**

I'm using ESP8266 backed with SparkFun WiFi Shield
This shield enables the arduino operating as http server and client

**Servo motor**

I'm using HD-3001HB servo which is a standard servo. In case that the servo is the only extra component connected to the arduino, power 
supply from the board itself will be ok. In other cases such as having the WIFI shield connected, I added 4XAA batteries as external power source. 

## What is in the repo?
Neat and lean examples of usage for using the arduino board by itself, and examples using the WIFI shield with it.

## What is not in the repo?
Circuit schematics. Why? because I believe you will not get the exact hardware I have

Explanations about how bad the head banging might get (maybe this is a fare explanation)


**Have fun!**
***

![Alt text](intro.jpg?raw=true "WIFI shield controlling servo motor by http request")
![Alt text](sd.jpeg?raw=true "SD card recording potentiometer values")
![Alt text](tft.jpg?raw=true "TFT screen")

