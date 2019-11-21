----------------------------------
Disclaimer
----------------------------------
This program collects data and stores it locally on the computer. This data is used for optimising the program and can be found in the respective folder for either the C++ code and Python code. THIS DATA IS NOT SEND ANYWHERE and is only stored locally. (Python part only stores the data is “Q” is pressed, this also closes the program)

----------------------------------
I. Introduction
----------------------------------
The aim of the program is to create an open air MIDI, in the form of an air guitar. The structure of the code is divided into two sections: a C++ section and a python section: 
the server and MIDI player is in the c++ section,  while the image processing and client is coded in Python. 


A library called TinySoundFont is used which is made in C++, this library however is NOT made by the authors and credit is due to “Based on SFZero, Copyright (C) 2012 Steve Folta (https://github.com/stevefolta/SFZero)””

----------------------------------
II. Getting Started/prerequisites
----------------------------------
In order for the program to be able to run, the following libraries needs to be installed  throughAnaconda, and the tinySoundFont must be located in MED3_Project -> RealMIDIPlayer -> RealMIDIPlayer folder:

-----------------
     Python
-----------------
OpenCV/CV2 (version 3.6)
numpy
XlsxWriter


In order for the python code to work, these libraries must be installed. This is done by downloading and installing Anaconda, opening the Anaconda console and running the following commands:


conda create -n opencv python=3.6
conda activate opencv
conda install -c conda-forge opencv


Once this is done, install Python and set it up with Anaconda. 


XlsxWriter and Numpy are installed by running the following commands in Anaconda, while Anaconda has opencv activated:.


conda install -c anaconda xlsxwriter
conda install -c anaconda numpy

-----------------
      C++
-----------------
In order for the C++ code to work, a sound library called ‘TinySoundFont’ must be present in the root folder. 


The library can be found here: https://drive.google.com/open?id=1H8uCT_3UAF83xbwTrfWGXXy-LpZhyygF 


The file called “soundfont1.sf2” needs to be placed inside the path MED3_Project -> RealMIDIPlayer -> RealMIDIPlayer.

----------------------------------
III. Running the Program:
----------------------------------
In order to get the program running properly, both the python code and the C++ code must be compiled and run. To connect the Python Client to the C++ server, press ‘W’ until the program says the client is connected. Then check the Python window called frame4 if two blobs are detected, indicated by the blob being surrounded by a red circle. Once two blobs are detected, press ‘L’ until you start seeing data being printed in the console. Now that the two programs are connected and calibrated, the user is able to play the MIDI by strumming with the right hand over the virtual string. The string covers the entire x coordinate of the window, and is placed at the y coordinate of the right hand at the time of calibration.


The volume is determined by the speed at which the string is stroken, and the tone is determined by the distance between the center of the two BLOBs. If the distance between the hands is higher than the 120% of distance between hands at time of calibration, a red line is displayed in the window, and a high pitch tone is played if the string is stroken.

----------------------------------
IV. Authors
----------------------------------
Hamzah Ziadeh
Louise Dørr Nielsen
Marcus Christensen
Rikke Juhl Kure Lyngbjerg
Steffen Lehmann
Thomas Kim Kromann Kjeldsen

----------------------------------
V. Credits
----------------------------------
Steve Folta (TinySoundFont)
Jesper Rindom Jensen (Supervisor)
David Gulyas
