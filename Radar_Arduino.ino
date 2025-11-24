#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG_PIN 10
#define ECHO_PIN 11
#define SERVO_PIN 12

Servo radarServo;
long duration;
int distance;

void setup() {

  Serial.begin(9600);

  radarServo.attach(SERVO_PIN);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // OLED Setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 30);
  display.print("Radar System Starting...");
  display.display();
  delay(1500);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) return -1;

  return (duration * 0.034 / 2);
}

void loop() {

  for (int angle = 15; angle <= 165; angle++) {
    runRadar(angle);
  }

  for (int angle = 165; angle >= 15; angle--) {
    runRadar(angle);
  }
}

void runRadar(int angle) {
  radarServo.write(angle);
  distance = getDistance();

  display.clearDisplay();

  // Radar arc
  display.drawCircle(64, 64, 60, WHITE);
  display.drawCircle(64, 64, 45, WHITE);
  display.drawCircle(64, 64, 30, WHITE);

  // Convert angle to screen coords
  float rad = radians(angle);
  int x = 64 + 60 * cos(rad);
  int y = 64 - 60 * sin(rad);

  // Sweep line
  display.drawLine(64, 64, x, y, WHITE);

  // Object dot
  if (distance > 0 && distance < 200) {
    int r = map(distance, 0, 200, 5, 60);
    int objX = 64 + r * cos(rad);
    int objY = 64 - r * sin(rad);
    display.fillCircle(objX, objY, 3, WHITE);
  }

  // Text info
  display.setCursor(0, 0);
  display.print("Angle: ");
  display.print(angle);

  display.setCursor(0, 10);
  display.print("Dist: ");
  display.print(distance);
  display.print("cm");

  display.display();
  delay(40);
}
