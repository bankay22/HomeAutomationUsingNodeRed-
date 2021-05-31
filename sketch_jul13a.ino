#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
SoftwareSerial s(3,1);

const char* ssid = "Linksys19039";
const char* password = "npnftfpd8r";
const char* mqtt_server = "192.168.1.149";



WiFiClient espClient;
PubSubClient client(espClient);

const int switch1=16; //data pin d0
const int switch2=5; //data pin d1
const int switch3=4; //data pin d2
const int switch4= 0;//data pin d3


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (topic == "room/switch1") {
    Serial.print("Changing Room switch to ");
    if (messageTemp == "on") {
      digitalWrite(switch1, LOW);
      Serial.print("switch1 on");
    }
else if (messageTemp == "off"){
  digitalWrite(switch1,HIGH);
  Serial.print("switch off");
}
}

if (topic == "room/switch2") {
    Serial.print("Changing Room switch to ");
    if (messageTemp == "on") {
      digitalWrite(switch2, LOW);
      Serial.print("switch2 on");
    }
else if (messageTemp == "off"){
  digitalWrite(switch2,HIGH);
  Serial.print("switch2 off");
}
}

if (topic == "room/switch3") {
    Serial.print("Changing auto switch to ");
    if (messageTemp == "on") {
      digitalWrite(switch3, LOW);
      Serial.print("switch3 on");
    }
else if (messageTemp == "off"){
  digitalWrite(switch3,HIGH);
  Serial.print("switch3 off");
}
}

if (topic == "room/switch4") {
    Serial.print("Changing auto switch to ");
    if (messageTemp == "on") {
      digitalWrite(switch4, LOW);
      Serial.print("switch4 on");
    }
else if (messageTemp == "off"){
  digitalWrite(switch4,HIGH);
  Serial.print("switch4 off");
}
}  


  if (topic == "room/fan") {
    Serial.print("Changing Room lamp to ");
    if (messageTemp == "0") {
      //digitalWrite(fan, HIGH);
      Serial.print("fan off");
      s.write(0x00);
    }

  
  else if (messageTemp == "1") {
    Serial.print("speed 64");
    s.write(0x40);

  }

  else if (messageTemp == "2") {
    Serial.print("speed 80");
    s.write(0x50);
  }
  
  else if (messageTemp == "3") {
    Serial.print("speed 100");
    s.write(0x64);

  } else if (messageTemp == "4") {
    Serial.print("speed 100");
    s.write(0x96);

  }
  else if (messageTemp == "5") {
    Serial.print("speed 50");
    s.write(0xA0);
  }
  else if (messageTemp == "6") {
    Serial.print("speed 50");
    s.write(0xB4);
  }
  else if (messageTemp == "7") {
    Serial.print("speed 50");
    s.write(0xDC);
  }
  else if (messageTemp == "8") {
    Serial.print("speed 50");
    s.write(0xE6);
  }
  else if (messageTemp == "9") {
    Serial.print("speed 50");
    s.write(0xFA);
  }
  else if (messageTemp == "10") {   
    Serial.print("speed 50");
    s.write(0xFF);
  }


  }


  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("room/switch1");
      client.subscribe("room/switch2");
      client.subscribe("room/switch3");
      client.subscribe("room/switch4");
      client.subscribe("room/fan");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setup() {
  pinMode(switch1, OUTPUT);
  pinMode(switch2, OUTPUT);
  pinMode(switch3, OUTPUT);
  pinMode(switch4, OUTPUT);

  digitalWrite(switch1,HIGH);
  digitalWrite(switch2,HIGH);
  digitalWrite(switch3,HIGH);
  digitalWrite(switch4,HIGH);
  
  

  Serial.begin(115200);
  Serial1.begin(115200);
  s.begin(9600);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP8266Client");
}
