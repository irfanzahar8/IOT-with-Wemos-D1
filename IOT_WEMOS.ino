/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsMicroESP8266.h"

#define TOKEN  "A1E-2VvLM7o0LWkbbzhinfcSBY8zTj2Z6k"
#define WIFISSID "TCS_2"
#define PASSWORD "P@s5w0rd!"
#define VIBRATION_SENSOR_PIN 3

const int buttonPin = 4;
int LED_Pin = 13;

int buttonState = 0;
int flag = 0;
int motion_detected = LOW;

Ubidots client(TOKEN);

void setup(){
    client.setDataSourceName("Machine1");
    Serial.begin(115200);
    client.wifiConnection(WIFISSID, PASSWORD);
    //client.setDebug(true); // Uncomment this line to set DEBUG on

    pinMode(LED_Pin, OUTPUT);
    pinMode(VIBRATION_SENSOR_PIN,INPUT); // set input for measurment
    pinMode(buttonPin, INPUT_PULLUP);
}
void loop(){
    //Read button state (pressed or not pressed?)
    buttonState = digitalRead(buttonPin);

   //If button pressed...
    if (buttonState == LOW) {
    if ( flag == 0){
      digitalWrite(LED_Pin, HIGH);
      flag=1; //change flag variable
    }
    else if ( flag == 1){
      digitalWrite(LED_Pin, LOW);
      flag=0; //change flag variable again 
    }}    
    long measurement =TP_init();
    delay(50);
    // Serial.print("measurment = ");
    Serial.println(measurement);
    if (measurement > 1000){  
      digitalWrite(LED_Pin, HIGH);
    }
    else{
      digitalWrite(LED_Pin, LOW); 
    }
    client.add("Vibration", motion_detected);
    
    client.sendAll(true);
    delay(6000);
}
long TP_init(){
    delay(10);
    long measurement=pulseIn (VIBRATION_SENSOR_PIN, HIGH);  //wait for the pin to get HIGH and returns measurement
    return measurement;
}
