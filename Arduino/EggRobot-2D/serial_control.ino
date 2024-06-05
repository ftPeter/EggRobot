// PicoSerialTest.ino
// Peter F. Klemperer
// June 5, 2024
//
// The purpose of this code is to test serial parsing on the 
// Raspberry Pi Pico for manually controlling the 2D EggBot
//
// Expected Commands
// <R,+15.0> - move right leg to 15 degrees
// <L,-15.0> - move left leg to -15 degrees
// <P,0.0>  - move pendulum to 0 degrees
//
// Substantially lifted from 
// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
// Example 5 - Receive with start- and end-markers combined with parsing

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

boolean newData = false;

void serial_control_loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

    strtokIndx = strtok(NULL, ",");
    floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Movement Angle ");
    Serial.println(floatFromPC);

    if(strcmp(messageFromPC,"Clear") == 0) {
      Serial.println("Resetting motor positions");
      positionPendulum(0.0);
      positionLeftLeg(0.0);
      positionRightLeg(0.0);
    } else if(strcmp(messageFromPC,"R") == 0) {
      positionRightLeg(floatFromPC);
    } else if(strcmp(messageFromPC,"L") == 0) {
      positionLeftLeg(floatFromPC);
    } else if(strcmp(messageFromPC,"P") == 0) {
      positionPendulum(floatFromPC);
    } else if(strcmp(messageFromPC,"Step") == 0) {
      step();
    }   
}