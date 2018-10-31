  #include <VirtualWire.h>
  #include <string.h>
  byte message[VW_MAX_MESSAGE_LEN];
  byte messageLength = VW_MAX_MESSAGE_LEN; 
  void setup() {
    Serial.begin(9600);
    vw_set_ptt_inverted(true);
    vw_setup(2000);
    vw_set_rx_pin(52);
    vw_rx_start();
  }
  void loop() {
    if (vw_get_message(message, &messageLength)) {
       int command = processResponse((char*)message, 1); //Byte Array Response and Pin Code.
       if (command) {
         Serial.print("Received Command: ");
         Serial.print(command);      
         Serial.print("\n");
       }  
    }
  }
  int processResponse(char* message, int pinCode) {
      char *p = message;
      char *buf;
      int o = 0;
      int pin;
      int command;
      while ((buf = strtok_r(p, ".", &p)) != NULL)  {
         if (o == 0) {
           pin = atoi(buf);
         } else {
           command = atoi(buf);
         }
         o++;
      }
      if (pinCode == pin && command > 0) {
          return command;
      } else {
         return 0; 
      }
  }
