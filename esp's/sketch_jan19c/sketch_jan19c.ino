/*********
  Author: Jitesh Saini
  This code is built upon the example code in pubsubclient library 
  Complete project details at https://helloworld.co.in
*********/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

// Replace the SSID/Password details as per your wifi router
const char* ssid = "";
const char* password = "";
Servo myservo;  // create servo object to control a servo


// Replace your MQTT Broker IP address here:
const char* mqtt_server = "";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
int pos = 90;    // variable to store the servo position
#define ledPin 2
#define led_red D5
#define led_green D6


void blink_led(unsigned int times, unsigned int duration){
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(duration);
    digitalWrite(ledPin, LOW); 
    delay(200);
  }
}

void setup_wifi() {
  delay(50);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int c=0;
  while (WiFi.status() != WL_CONNECTED) {
    blink_led(2,200); //blink LED twice (for 200ms ON time) to indicate that wifi not connected
    delay(1000); //
    Serial.print(".");
    c=c+1;
    if(c>10){
        ESP.restart(); //restart ESP after 10 seconds
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void connect_mqttServer() {
  // Loop until we're reconnected
  while (!client.connected()) {

        //first check if connected to wifi
        if(WiFi.status() != WL_CONNECTED){
          //if not connected, then first connect to wifi
          setup_wifi();
        }

        //now attemt to connect to MQTT server
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP32_client3")) { // Change the name of client here if multiple ESP32 are connected
          //attempt successful
          Serial.println("connected");
          // Subscribe to topics here
          client.subscribe("rpi/broadcast");
          //client.subscribe("rpi/xyz"); //subscribe more topics here
          
        } 
        else {
          //attempt not successful
          Serial.print("failed, rc=");
          Serial.print(client.state());
          Serial.println(" trying again in 2 seconds");
    
          blink_led(3,200); //blink LED three times (200ms on duration) to show that MQTT server connection attempt failed
          // Wait 2 seconds before retrying
          delay(2000);
        }
  }
  
}

//this function will be executed whenever there is data available on subscribed topics
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Check if a message is received on the topic "rpi/broadcast"
  if (String(topic) == "rpi/broadcast") {
      if(messageTemp == "4"){
        Serial.println("Action: blink LED.    DOWN");
        blink_led(1,1250); //blink LED once (for 1250ms ON time)
        myservo.write(0);              // tell servo to go to position in variable 'pos'
        digitalWrite(led_red, HIGH); 
        digitalWrite(led_green, LOW);

      }

      if(messageTemp == "1"){
        Serial.println("Action: blink LED.    UP");
        blink_led(1,1250); //blink LED once (for 1250ms ON time)
        myservo.write(90);             // tell servo to go to position in variable 'pos'
        digitalWrite(led_green, HIGH);
        digitalWrite(led_red, LOW); 
      }

      if(messageTemp == "12"){
        Serial.println("Action: First run.   all UP");
        blink_led(1,1250); //blink LED once (for 1250ms ON time)
        myservo.write(90);             // tell servo to go to position in variable 'pos'
        digitalWrite(led_green, HIGH);
        digitalWrite(led_red, HIGH); 
      }
  }

  //Similarly add more if statements to check for other subscribed topics 
}

void setup() {
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  myservo.attach(D0);
  setup_wifi();
  client.setServer(mqtt_server,1883);//1883 is the default port for MQTT server
  client.setCallback(callback);
}

void loop() {
  
  if (!client.connected()) {
    connect_mqttServer();
  }

  client.loop();
  
  long now = millis();
  if (now - lastMsg > 4000) {
    lastMsg = now;

    client.publish("esp32/sensor3", "69"); //topic name (to which this ESP32 publishes its data). 88 is the dummy value.
    
    // myservo.write(pos);              // tell servo to go to position in variable 'pos'

  }
  
}