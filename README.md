<<<<<<< HEAD
# ZhiyinL-cathy-zhoubn-project
=======
## Project title
Smart Glove for Sign Langauge Recognition
## Team members
Beining Zhou, Zhiyin Lin
## Project description
We built a smart glove that detects the user’s hand gestures. As the client uses American Sign Language, our glove recognizes the 26 letters they gesture along with 2 "self-invented" space and backspace gestures.

The glove has five flex sensors on the five fingers to detect the extent of bending of the fingers. Each of the flex sensors is connected to an Analog-to-Digital Converter to read the resistance values. The glove also has an accelerometer that measures the rotation of the hand. These six degrees of freedom helps to distinguish the sign language gestures.

We have two platforms to interact with the use: a teaching platform that gives feedback to the user's gestures, and a console that allows a user to "type" using ASL.

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








