//include libraries and WiFi & MQTT setting
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = “SSID";
const char* password = “PASSWORD"; 
const char* mqtt_server = “BrokerIP"; 
WiFiClient espClient; //define variable
PubSubClient client(espClient); 
unsigned long lastMsg = 0; 
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE]; 
int value = 0;

//create setup_wifi function
void setup_wifi() {
  delay(10);
  //start by connecting to a WiFi network 
  Serial.println();
  Serial.print("Connecting to "); 
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); 
  }

  randomSeed(micros()); 
  Serial.println(""); 
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");   
  Serial.println(WiFi.localIP());
}

//create callback() function
void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) { 
  }
  
  //switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    Serial.write("LEDon"); //send message to turn the LED on
  } else {
    Serial.write("LEDoff"); //turn the LED off by making the voltage HIGH
  } 
}

//create reconnect() function
void reconnect() {
  //loop until we're reconnected 
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    //create a random client ID
    String clientId = "ESP8266Client-"; 
    clientId += String(random(0xffff), HEX); 
    //attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //once connected, publish an announcement...
      client.publish("TOPIC", "connected"); 
      //... and resubscribe 
      client.subscribe("TOPIC");
    } else {
      Serial.print("failed, rc="); 
      Serial.print(client.state()); 
      Serial.println(" try again in 5 seconds"); 
      //wait 5 seconds before retrying 
      delay(1000);
    } 
  }
}

//create loop() function
void loop() {
  if (!client.connected()) {
    reconnect(); 
  }
  client.loop();
  unsigned long now = millis(); 
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value); 
  }

  //create strings of payload with JSON format
  //publish payload to Broker
  int i=0;
  String readString;
  while (Serial.available()) {
    delay(2); //delay to allow byte to arrive in input buffer
    char c = Serial.read(); 
    readString += c;
    i=1;
  }
  if (i==1){
    byte arrsize = readString.length()+1; 
    Serial.println(arrsize);
    char attributes[arrsize]; 
    readString.toCharArray(attributes, arrsize);
    client.publish("TOPIC", attributes); 
    client.subscribe("TOPIC");
  }
}
