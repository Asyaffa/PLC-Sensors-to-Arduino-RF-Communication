#include <SPI.h>
#include <RF24.h>
#include <nRF24l01.h>

RF24 radio (14, 15);

/*
 Pin A2     = IN1 L298N
 Pin A3     = IN2 L298N
 Pin A4     = IN3 L298N
 Pin A5     = IN4 L298N
 Pin D9     = ENA L298N
 Pin D10    = ENB L298N
 
 Pin D5     = PWM Servo 1
 Pin D6     = PWM Servo 2
 
 Pin D7     = IR Input (RIGHT)
 Pin D8     = IR Input (LEFT)
 
 Pin A0/D14 = CE "CHIP ENABLE"
 Pin A1/D15 = CSN "CHIP SELECT NOT"
 Pin D11    = MOSI "MASTER OUT SLAVE IN"
 Pin D12    = MISO "MASTER IN SLAVE OUT"
 Pin D13    = SCK  "SERIAL CLOCK"
*/

const byte address [6] = "00001";
int sensorOptoValue [4];

void setup() 
{
    Serial.begin (9600);
    
    radio.begin ();
    radio.openReadingPipe (0, address);
    radio.setPALevel (RF24_PA_MIN);
    radio.startListening ();

}

void loop() 
{
    if (radio.available ())
    {
        radio.read (sensorOptoValue, sizeof (sensorOptoValue));
        int PE1Value = sensorOptoValue [0];
        int IPValue = sensorOptoValue [1];
        int PE2Value = sensorOptoValue [2];
        int PE3Value = sensorOptoValue [3];

        Serial.print ("Sensor 1 : ");
        Serial.print (PE1Value);
        Serial.print ("\t");
        Serial.print ("Sensor 2 : ");
        Serial.print (IPValue);
        Serial.print ("\t");
        Serial.print ("Sensor 3 : ");
        Serial.print (PE2Value);
        Serial.print ("\t");
        Serial.print ("Sensor 4 : ");
        Serial.println (PE3Value);
    }
}
