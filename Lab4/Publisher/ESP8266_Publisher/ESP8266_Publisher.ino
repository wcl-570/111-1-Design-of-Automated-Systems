//include libraries and declare variable
//include function libraries
#include <ESP8266WiFi.h> 
#include <PubSubClient.h>

//update these with values suitable for your network
const char* ssid = “WiFi name";
const char* password = “WiFi password"; 
const char* mqtt_server = “BrokerIP";

WiFiClient espClient; 
PubSubClient client(espClient); 
unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50) 
char msg[MSG_BUFFER_SIZE]; 
int value = 0;

//create setup_wifi() function
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
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
      // Once connected, publish an announcement...
      client.publish(“Topic", "connected");
      //... and resubscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state()); 
      Serial.println(" try again in 5 seconds"); 
      //wait 5 seconds before retrying 
      delay(1000);
    }
  }
}

//create setup() function
void setup() { 
  pinMode(BUILTIN_LED, OUTPUT);//initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
}

//create loop() function
void loop() {
  if (!client.connected()) {
  reconnect(); 
  }
  client.loop();
  
  unsigned long now = millis();
  int i=0;
  String readString;
  while (Serial.available()) {
    delay(2);//delay to allow byte to arrive in input buffer
    char c = Serial.read();
    readString += c; 
    i=1;
  }

  if (i==1) {
  byte arrsize = readString.length()+1;
  Serial.println(arrsize);
  char attributes[arrsize]; 
  readString.toCharArray( attributes, arrsize); 
  client.publish(“Topic", attributes);
  }
}
