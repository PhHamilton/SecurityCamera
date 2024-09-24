#!bin/bash

sudo apt update && sudo apt upgrade -y

sudo apt-get install libatlas-base-dev
sudo apt-get install libjasper-dev
sudo apt-get install libqt5gui5 libqt5webkit5 libqt5test5
sudo apt-get install libhdf5-dev
sudo apt-get install mosquitto mosquitto-clients


sudo apt-get install python3-pip
sudo mv /usr/lib/python3.11/EXTERNALLY-MANAGED /usr/lib/python3.11/EXTERNALLY-MANAGED.old
sudo pip3 install flask
sudo pip3 install numpy
sudo pip3 install paho-mqtt
sudo pip3 install opencv-contrib-python
sudo pip3 install imutils
sudo pip3 install opencv-python
