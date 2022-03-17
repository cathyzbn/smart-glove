<<<<<<< HEAD
# ZhiyinL-cathy-zhoubn-project
=======
## Project title
Smart Glove for Sign Langauge Recognition
## Team members
Beining Zhou, Zhiyin Lin
## Project description
We built a smart glove that detects the user’s hand gestures. As the client uses American Sign Language, our glove recognizes the 26 letters they gesture along with 2 "self-invented" space "_" and backspace "\b" gestures.

We created two intefaces to interact with the user. First, we built a typing console with graphics display, where the user is able to type with whitespace and backspace. Second, we built an ASL teaching system that gives feedback. If the client is trying to practice American Sign Language, our interface will allow the client to go through each of A - Z and provide feedback, such as “Congrats you got it!” or "We read X, please try again!" 

The glove has two major components, an accelerometer (https://www.pololu.com/product/2736) and five flex sensors (https://www.sparkfun.com/products/10264) with A to D converter (MCP3008). 

The accelerometer is mainly for detecting movement of hand to distinguish between I and J, D and Z. 

The five flex sensors are put on five fingers to detect the angle of bending for each finger (degree 0 to 90). The code requires an initial calibration process to keep track of the maximum and minimum angle a finger gets to accustom to different user hands. Then, with the obtained range, we rescale the range to be 0 to 90 degrees. 

To obtain the angle bent, we make use of voltage divider in the circuit design. Total voltage of the circuit remains constant 3.3V. In addition to a flex sensor (resistance ranges from straight 30kOhm to bent 150kOhm), there is also a resistor (constant resistance, known = 100kOhm). If a flex sensor is greatly bent, its resistance is big, so it takes a big proportion of the total voltage. If a flex sensor is straight, its resistance is small, so it takes a small proportion of the total voltage. And it is in a linear fashion. Based on how much voltage is detected from the flex sensor, we are able to track the angle. Each of the flex sensors is connected to an Analog-to-Digital Converter channel to translate numerical voltage values to digital signals that a Pi understands. 

To distinguish the 26 letters, we collected intensive empirical data to find out how to separate each letter from others. 


## Member contribution
Cathy was mainly in charge of the hardware, and Zhiyin was mainly in charge of the software. However, both member contributed to each part. 
## References
The idea was developed by our own. However, afterwards, we found this source: https://create.arduino.cc/projecthub/173799/a-glove-that-translate-sign-language-into-text-and-speech-c91b13 that was similar to our idea.

We referenced the hardware design. We coded from scratch.

## Self-evaluation
We executed our plan on the proposal very well; There were so many unexpected places that went wrong, but with the help of the staff and our tireless hours, we figured it out!

The accelerometer was really hard to work with on our end. We had many issues with the location, the reading, the infinite loops, that we essentially read through the whole i2c driver and found out about the connection buts and a bug that we made by ourselves in i2c.

We were super proud of the end product and to see it work! We learned so much about hardware, connecting software, and making a product that we always was interested in making.

However, there were still so many parts that we want to add to our product. We would want to design our GUI to better accomodate user experiences, provide specific feedback on gestures, and add more sensor, such as a metal-to-metal reading that could detect whether two fingers touch eaches each other. However, we were really satisfied with our end product!


## Photos
Video submitted with code.
>>>>>>> 9caaa12217440953a99ec80c87c1cb7773e19cc1








