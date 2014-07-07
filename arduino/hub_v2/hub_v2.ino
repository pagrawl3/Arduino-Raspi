#include <Wire.h>
#include <LiquidCrystal.h>

#define SLAVE_ADDRESS   0x03
#define REDLITE         6
#define GREENLITE       9
#define BLUELITE        10

int number = 0;
int state = 0;
int brightness = 255;

LiquidCrystal lcd(4, 5, 7, 8, 12, 13);

void setup() {
    Serial.begin(115200);           // start serial for output
    Wire.begin(SLAVE_ADDRESS);      // initialize i2c as slave

    Wire.onReceive(receiveData);    // define callbacks for i2c communication
    Wire.onRequest(sendData);       // define callbacks for i2c communication

    lcd.begin(16,2);                //LCD Size
    lcd.print("Hello, World!");     //Sample Text

    pinMode(REDLITE, OUTPUT);
    pinMode(GREENLITE, OUTPUT);
    pinMode(BLUELITE, OUTPUT);

    //#f1c40f
    setBacklight(0, 255, 0);
    // setBacklight(0x00, 0x00, 0xff);
}

void loop() {
    delay(100);
}

// callback for received data
void receiveData(int byteCount){

    while(Wire.available()) {
        number = Wire.read();
        Serial.print("data received: ");
        Serial.println(number);

        if (number == 1){

            if (state == 0){
                digitalWrite(13, HIGH); // set the LED on
                state = 1;
            }
            else{
                digitalWrite(13, LOW); // set the LED off
                state = 0;
            }
         }
     }
}

// callback for sending data
void sendData(){
    Wire.write(number);
}

void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
    // normalize the red LED - its brighter than the rest!
//    r = map(r, 0, 255, 0, 255);
//    g = map(g, 0, 255, 0, 255);

    r = map(r, 0, 255, 0, brightness);
    g = map(g, 0, 255, 0, brightness);
    b = map(b, 0, 255, 0, brightness);

    // common anode so invert!
    r = map(r, 0, 255, 255, 0);
    g = map(g, 0, 255, 255, 0);
    b = map(b, 0, 255, 255, 0);
    
    analogWrite(REDLITE, r);
    analogWrite(GREENLITE, g);
    analogWrite(BLUELITE, b);
}



