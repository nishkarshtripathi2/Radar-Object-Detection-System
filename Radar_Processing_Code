import processing.serial.*;

Serial myPort;

String data = "";
float angle = 0;
float distance = 0;  // incoming in cm

int maxRange = 200; // cm

// HISTORY STORAGE
int historySize = 700;
float[] hx = new float[historySize];
float[] hy = new float[historySize];
int[] hColor = new int[historySize];
int index = 0;

// SMOOTH FILTER VALUES
float smoothDistance = 0;
float filterStrength = 0.25; 

void setup() {
  size(950, 650);
  smooth();

  println(Serial.list());
  myPort = new Serial(this, "COM3", 9600); // Change COM port
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);

  translate(width/2, height);

  drawRadarGrid();
  drawSweepLine();
  drawHistory();
  drawCurrentPoint();
  drawText();
  drawWarning();
}

// ---------------- GRID ----------------
void drawRadarGrid() {
  stroke(0, 255, 0);
  noFill();

  for (int r = 50; r <= maxRange; r += 25) {
    arc(0, 0, r * 4, r * 4, PI, TWO_PI);
  }

  stroke(0, 255, 0, 120);
  line(-400, 0, 400, 0);
}

// ---------------- SWEEP LINE ----------------
void drawSweepLine() {
  stroke(0, 255, 0);
  float rad = radians(angle);
  line(0, 0, maxRange * 2 * cos(rad), -maxRange * 2 * sin(rad));
}

// ---------------- HISTORY ----------------
void drawHistory() {
  for(int i=0; i<historySize; i++){
    if(hx[i] != 0 && hy[i] != 0){
      fill(hColor[i], 200);
      noStroke();
      ellipse(hx[i], hy[i], 10, 10);
    }
  }
}

// ---------------- CURRENT TARGET ----------------
void drawCurrentPoint() {

  smoothDistance = lerp(smoothDistance, distance, filterStrength);
  float meters = smoothDistance / 100.0;

  if(smoothDistance > 0 && smoothDistance < maxRange){
    float rad = radians(angle);

    float scaledDist = constrain(map(smoothDistance, 0, maxRange, 0, maxRange * 2), 0, maxRange * 2);
    float x = scaledDist * cos(rad);
    float y = -scaledDist * sin(rad);

    int c;

    // Color based on METERS
    if(meters < 0.30){
      c = color(0, 255, 0);   // Close → Green
    } 
    else if(meters < 1.00){
      c = color(255, 255, 0); // Mid → Yellow
    }
    else {
      c = color(255, 0, 0);   // Far → Red
    }

    fill(c);
    noStroke();
    ellipse(x, y, 18, 18);

    // Glow effect if far
    if(meters > 1.0){
      stroke(255,0,0,150);
      strokeWeight(2);
      noFill();
      ellipse(x, y, 30, 30);
    }

    hx[index] = x;
    hy[index] = y;
    hColor[index] = c;
    index = (index + 1) % historySize;
  }
}

// ---------------- HUD TEXT ----------------
void drawText() {
  resetMatrix();
  fill(0, 255, 0);
  textSize(25);

  // Show distance in meters
  text("Angle: " + angle + "°", 50, 60);
  text("Distance: " + nf(distance/100.0,1,2) + " m", 50, 95);
}

// ---------------- ALERT SYSTEM ----------------
void drawWarning() {
  float meters = smoothDistance / 100.0;

  if(meters > 1.0){
    fill(255, 0, 0);
    textSize(28);
    text("⚠ FAR OBJECT (>1m)", width/2 - 220, 60);
  }
  else if(meters > 0.30){
    fill(255, 255, 0);
    textSize(24);
    text("Object in Mid Range (0.3m - 1m)", width/2 - 250, 60);
  }
  else if(meters > 0){
    fill(0, 255, 0);
    textSize(22);
    text("Object Very Close (<0.3m)", width/2 - 200, 60);
  }
}

// ---------------- SERIAL ----------------
void serialEvent(Serial p) {
  data = p.readStringUntil('\n');

  if(data != null){
    data = trim(data);
    String[] arr = split(data, ',');

    if(arr.length == 2){
      try {
        angle = float(arr[0]);
        distance = float(arr[1]); 
      } catch(Exception e){}
    }
  }
}
