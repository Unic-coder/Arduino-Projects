#include <PubSubClient.h>
#include <WiFi.h>
#include <stdio.h>


#define WIFISSID "YOUR WIFI NAME" 
#define PASSWORD "WIFI PASSWORD" 
#define TOKEN "TOKEN" // Ubidots' TOKEN

#define VARIABLE_LABEL_SUB_1 "relay1" 
#define VARIABLE_LABEL_SUB_2 "relay2" 
#define VARIABLE_LABEL_SUB_3 "relay3" 
#define VARIABLE_LABEL_SUB_4 "relay4" 


#define DEVICE_LABEL "esp32"
#define MQTT_CLIENT_NAME "testing" 

#define R1 14
#define R2 25
#define R3 27
#define R4 26


char mqttBroker[] = "industrial.api.ubidots.com";

const int ERROR_VALUE = 65535;  

const uint8_t NUMBER_OF_VARIABLES = 4; 
char * variable_labels[NUMBER_OF_VARIABLES] = {"relay1", "relay2", "relay3", "relay4"}; 

float CONTROL1; 
float CONTROL2;
float CONTROL3; 
float CONTROL4;

float value; 
uint8_t variable; 


WiFiClient ubidots;
PubSubClient client(ubidots);


void callback(char* topic, byte* payload, unsigned int length) {
  char* variable_label = (char *) malloc(sizeof(char) * 30);;
  get_variable_label_topic(topic, variable_label);
  value = btof(payload, length);
  set_state(variable_label);
  execute_cases();
  free(variable_label);
}

void get_variable_label_topic(char * topic, char * variable_label) {
  Serial.print("topic:");
  Serial.println(topic);
  sprintf(variable_label, "");
  for (int i = 0; i < NUMBER_OF_VARIABLES; i++) {
    char * result_lv = strstr(topic, variable_labels[i]);
    if (result_lv != NULL) {
      uint8_t len = strlen(result_lv);
      char result[100];
      uint8_t i = 0;
      for (i = 0; i < len - 3; i++) {
        result[i] = result_lv[i];
      }
      result[i] = '\0';
      Serial.print("Label is: ");
      Serial.println(result);
      sprintf(variable_label, "%s", result);
      break;
    }
  }
}

// cast from an array of chars to float value.
float btof(byte * payload, unsigned int length) {
  char * demo_ = (char *) malloc(sizeof(char) * 10);
  for (int i = 0; i < length; i++) {
    demo_[i] = payload[i];
  }
  return atof(demo_);
}

// State machine to use switch case
void set_state(char* variable_label) {
  variable = 0;
  for (uint8_t i = 0; i < NUMBER_OF_VARIABLES; i++) {
    if (strcmp(variable_label, variable_labels[i]) == 0) {
      break;
    }
    variable++;
  }
  if (variable >= NUMBER_OF_VARIABLES) variable = ERROR_VALUE; // Not valid
}


void execute_cases() {
  switch (variable) {
    case 0:
      CONTROL1 = value;
      digitalWrite(R1,value);
      Serial.print("CONTROL1: ");
      Serial.println(CONTROL1);
      Serial.println();
      break;
    case 1:
      CONTROL2 = value;
        digitalWrite(R2,value);
      Serial.print("CONTROL2: ");
      Serial.println(CONTROL2);
      Serial.println();
      break;
    case 2:
      CONTROL3 = value;
        digitalWrite(R3,value);
      Serial.print("CONTROL3: ");
      Serial.println(CONTROL3);
      Serial.println();
      break;
    case 3:
      CONTROL4 = value;
        digitalWrite(R4,value);
      Serial.print("CONTROL4: ");
      Serial.println(CONTROL4);
      Serial.println();
      break;
 
    case ERROR_VALUE:
      Serial.println("error");
      Serial.println();
      break;
    default:
      Serial.println("default");
      Serial.println();
  }

}

void reconnect() {

    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("connected");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");

    }
}


void setup() {
  Serial.begin(115200);
  //pinMode(A0, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  WiFi.begin(WIFISSID, PASSWORD);
  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();

    char topicToSubscribe_variable_1[200];
    sprintf(topicToSubscribe_variable_1, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_1, "%s/%s/lv", topicToSubscribe_variable_1, VARIABLE_LABEL_SUB_1);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_1);
    client.subscribe(topicToSubscribe_variable_1);

    char topicToSubscribe_variable_2[200];
    sprintf(topicToSubscribe_variable_2, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_2, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_2, "%s/%s/lv", topicToSubscribe_variable_2, VARIABLE_LABEL_SUB_2);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_2);
    client.subscribe(topicToSubscribe_variable_2);

    char topicToSubscribe_variable_3[200];
    sprintf(topicToSubscribe_variable_3, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_3, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_3, "%s/%s/lv", topicToSubscribe_variable_3, VARIABLE_LABEL_SUB_3);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_3);
    client.subscribe(topicToSubscribe_variable_3);

    char topicToSubscribe_variable_4[200];
    sprintf(topicToSubscribe_variable_4, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_4, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_4, "%s/%s/lv", topicToSubscribe_variable_4, VARIABLE_LABEL_SUB_4);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_4);
    client.subscribe(topicToSubscribe_variable_4);

   
  }
 
  delay(1);
}
