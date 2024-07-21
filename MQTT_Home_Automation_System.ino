/*Name: Infant Regan
MQTT Home Automation System
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define ROOM1_LIGHT1          4
#define ROOM1_LIGHT2          5
#define ROOM2_LIGHT1          6
#define ROOM2_LIGHT2          7
#define ROOM1_TEMP_SENSOR     A0
#define ROOM2_TEMP_SENSOR     A1

/* Update these with values suitable for your network.*/
byte mac[]    = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);

/*broker address*/
IPAddress server(192,168,1,6); //My IP

/*create ethernet client instance*/
EthernetClient ethClient;
/*create pubsub client instance*/
PubSubClient client(ethClient);

/* Callback function header*/
void callback(char* topic, byte* payload, unsigned int length);

/* Callback function*/
void callback(char* topic, byte* payload, unsigned int length) 
{
  if (String(topic) == "home/room1/light1")
  {
    Serial.print("Message: ");
    
    /*turn the LED ON if the payload is '1' and publish to the MQTT server a confirmation message*/
    if(payload[0] == '1')
    {
      digitalWrite(ROOM1_LIGHT1, HIGH);
      client.publish("home/room1/light_feedback", "Room1 Light1 is turned ON");
    }
     /*turn the LED OFF if the payload is '0' and publish to the MQTT server a confirmation message*/
    if (payload[0] == '0')
    {
      digitalWrite(ROOM1_LIGHT1, LOW);
      client.publish("home/room1/light_feedback", "Room1 Light1 is turned OFF");
    }
  }

  if (String(topic) == "home/room1/light2")
  {
    Serial.print("Message: ");
    
    /*turn the LED ON if the payload is '1' and publish to the MQTT server a confirmation message*/
    if(payload[0] == '1')
    {
      digitalWrite(ROOM1_LIGHT2, HIGH);
      client.publish("home/room1/light_feedback", "Room1 Light2 is turned ON");
    }
     /*turn the LED OFF if the payload is '0' and publish to the MQTT server a confirmation message*/
    if (payload[0] == '0')
    {
      digitalWrite(ROOM1_LIGHT2, LOW);
      client.publish("home/room1/light_feedback", "Room1 Light2 is turned OFF");
    }
  }

  if (String(topic) == "home/room1/temp_sensor") 
  {
    // reads the temperature sensor value from A0 pin
    int tempValue = analogRead(ROOM1_TEMP_SENSOR);
    // convert the raw ADC reading to temperature in Celsius
    float temperature = (tempValue / 1024.0) * 5.0 * 100.0;
    // publish the temperature value back to the same topic
    client.publish("home/room1/temp_sensor", String(temperature).c_str());
  }

  if (String(topic) == "home/room2/temp_sensor") 
  {
    // reads the temperature sensor value from A1 pin
    int tempValue = analogRead(ROOM2_TEMP_SENSOR);
    // convert the raw ADC reading to temperature in Celsius
    float temperature = (tempValue / 1024.0) * 5.0 * 100.0;
    // publish the temperature value back to the same topic
    client.publish("home/room2/temp_sensor", String(temperature).c_str());
  }    
} 

void reconnect() 
{
  /* Loop until we're reconnected */
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    /* Create a random client ID */
    String clientId = "Home_automation_UNO";
    clientId += String(random(0xffff), HEX);
    /* Attempt to connect*/
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");
      /* Once connected, publish an announcement...*/
      //client.publish("home/room1/temp_sensor", "10");
      /* ... and resubscribe to all topics with 'home/' prefix*/
      client.subscribe("home/room1/light1");
      client.subscribe("home/room1/light2");
      client.subscribe("home/room2/light1");
      client.subscribe("home/room2/light2");
      //client.subscribe("home/#");   
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      /* Wait 5 seconds before retrying*/
      delay(5000);
    }
  }

  // read and publish room1 temperature every 5 seconds
  int tempValue = analogRead(ROOM1_TEMP_SENSOR);
  float temperature = (tempValue / 1024.0) * 5.0 * 100.0;
  client.publish("home/room1/temp_sensor", String(temperature).c_str());
  delay(5000);
  // read and publish room2 temperature every 5 seconds
  int tempValue2 = analogRead(ROOM2_TEMP_SENSOR);
  float temperature2 = (tempValue2 / 1024.0) * 5.0 * 100.0;
  client.publish("home/room2/temp_sensor", String(temperature2).c_str());
  delay(5000);
}

void setup()
{
  pinMode(ROOM1_LIGHT1, OUTPUT);
  digitalWrite(ROOM1_LIGHT1, LOW);

  pinMode(ROOM1_LIGHT2, OUTPUT);
  digitalWrite(ROOM1_LIGHT2, LOW);

  pinMode(ROOM2_LIGHT1, OUTPUT);
  digitalWrite(ROOM2_LIGHT1, LOW);

  pinMode(ROOM2_LIGHT2, OUTPUT);
  digitalWrite(ROOM2_LIGHT2, LOW);

  pinMode(ROOM1_TEMP_SENSOR, INPUT);       // Setting Room 1 Temperature Sensor as Input
  pinMode(ROOM2_TEMP_SENSOR, INPUT);       // Setting Room 2 Temperature Sensor as Input
  
  Serial.begin(9600);
  Serial.println("MQTT Home Automation Project");
  Ethernet.begin(mac, ip);
  /* Add the server details to connect*/
  client.setServer(server, 1883);
  /* Subscribe the message to the respective topics*/
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    /*attempting to connect loop*/
    reconnect();
  }
  client.loop(); 
}
