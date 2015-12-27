#include <IRremote.h>

const int IRRECV_PIN = 11;
const int SIGNAL_PIN = 3;

IRrecv irrecv(IRRECV_PIN);
decode_results results;

void handle_ir(decode_results *results) {
  if (results->decode_type == MAGIQUEST) {
    Serial.print(" 0x");
    Serial.print(results->value, HEX);
    Serial.print(" 0x");
    Serial.print(results->magnitude, HEX);
    Serial.println();

    // TODO: for now, latch the program until we finish LED'ing
    if (results->value == 0x0024F95B) {
      digitalWrite(SIGNAL_PIN, HIGH);
      delay(500);
      digitalWrite(SIGNAL_PIN, LOW);
    }
    else {
      digitalWrite(SIGNAL_PIN, HIGH);
      delay(100);
      digitalWrite(SIGNAL_PIN, LOW);
      delay(100);
      digitalWrite(SIGNAL_PIN, HIGH);
      delay(100);
      digitalWrite(SIGNAL_PIN, LOW);
      delay(100);
      digitalWrite(SIGNAL_PIN, HIGH);
      delay(100);
      digitalWrite(SIGNAL_PIN, LOW);
    }
  }
}

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn();

  // signal that we're ready
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, HIGH);
  delay(200);
  digitalWrite(SIGNAL_PIN, LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    handle_ir(&results);
    irrecv.resume();
  }
}
