# CheckinForSlackthroughMFRC522
This is a check in system for company.where employee swap their rfid tag to post message on slack.

# Here we are using three things-:
# 1.MFRC522
![download 2](https://user-images.githubusercontent.com/19189211/40733320-ed195134-6452-11e8-973b-717f98d1b387.jpg)
# 2.ESP8266 NODEMCU
![download](https://user-images.githubusercontent.com/19189211/40733692-e3bfd01c-6453-11e8-9acf-67defa649430.jpg)
# 3.SLACK (software)
![slack_icon](https://user-images.githubusercontent.com/19189211/40733764-1abf01be-6454-11e8-857e-25b51367020d.png)


# wiring configuration between ESP8266 NODEMCU And MFRC522

MFRC522 -> NODEMCU
RST     -> GPIO5 D1
SDA(SS) -> GPIO4 D2
MOSI    -> GPIO13 D7
MISO    -> GPIO12 D6
SCK     -> GPIO14 D5
GND     -> GND
3.3V    -> 3.3V



# library that has to installed on arduino
1. library for NODEMCU (is you have never used it try to simply connect it to the wifi google some simple project)
2. library for MFRC522


# how to configure slack to get message from MFRC522
1. go to -: https://slack.com/ 
 Create a Slack Workspace and go to any channel
2. go to -: https://yourslackworkspace.com/apps/manage/custom-integrations
 enable incoming web hook for your channel( any channel you want to post message just enable incoming webhook)
 ![image1](https://user-images.githubusercontent.com/19189211/40734355-cca192c4-6455-11e8-86b4-8e92017a6131.png)
3. get incoming webhook url to post message on slack channel
![image2](https://user-images.githubusercontent.com/19189211/40734896-600e2562-6457-11e8-83e6-cd0ad0641639.png)


at this point you have installed libraries for NODEMCU,MFRC522 and enable incoming webhook of your slack channel.hip hip hurray
connect things,run ino file and scan the rfid tag to see your message on slack channel.



i am big fan of anime.one piece is one of my favorite.you can mail me to get help in iot things - namansisodia619@gmail.com
![thumb-1920-319163](https://user-images.githubusercontent.com/19189211/40735178-2516d1d8-6458-11e8-8f81-ef2e0c0ef47a.png)
