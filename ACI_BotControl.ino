#include <WiFi.h>
#include <WebServer.h>
#include "motors.h"
#include "servos.h"

// WiFi AP credentials
const char* ssid     = "TeamACI";
const char* password = "Lancer123";

WebServer server(80);

// HTML PAGE (Multi-Touch D-Pads + Servo Buttons)
const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>TEAM ACI</title>

  <style>
    * {
      box-sizing: border-box;
    }

    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      text-align: center;
      margin: 0;
      padding: 20px;
      background: linear-gradient(180deg, #071224 0%, #081826 40%, #051018 100%);
      min-height: 100vh;
      color: #e9e3d6;
    }

    h2 {
      font-size: 32px;
      margin-bottom: 10px;
      color: #d4b46e;
      text-shadow: 0 2px 8px rgba(0, 0, 0, 0.7);
      letter-spacing: 1px;
    }

    h3 {
      font-size: 18px;
      margin: 15px 0 10px 0;
      color: #f3e7cf;
      text-shadow: 0 1px 4px rgba(0, 0, 0, 0.6);
      font-weight: 600;
    }

    .container {
      display: flex;
      justify-content: center;
      align-items: flex-start;
      flex-wrap: wrap;
      gap: 40px;
      margin: 30px 0;
    }

    .pad {
      display: grid;
      grid-template-columns: 70px 70px 70px;
      grid-template-rows: 70px 70px 70px;
      gap: 8px;
      padding: 20px;
      background: rgba(10, 15, 22, 0.6);
      border-radius: 16px;
      border: 1px solid rgba(212, 180, 110, 0.06);
      backdrop-filter: blur(6px);
      box-shadow: 0 8px 30px rgba(3, 6, 12, 0.7), inset 0 1px 0 rgba(255, 255, 255, 0.02);
    }

    .pad button {
      width: 70px;
      height: 70px;
      background: linear-gradient(180deg, #0f2230 0%, #091724 100%);
      border-radius: 12px;
      font-size: 20px;
      font-weight: 700;
      border: 1px solid rgba(212, 180, 110, 0.08);
      color: #e6d7b0;
      box-shadow: 0 6px 18px rgba(3, 6, 12, 0.6), 0 0 12px rgba(212, 180, 110, 0.03);
      cursor: pointer;
      transition: transform 0.08s ease, box-shadow 0.08s ease, background 0.08s ease;
      user-select: none;
      -webkit-user-select: none;
      touch-action: manipulation;
    }

    .pad button:active {
      background: linear-gradient(180deg, #d4b46e 0%, #b58f3b 100%);
      color: #061018;
      transform: scale(0.96);
      box-shadow: 0 4px 12px rgba(0, 0, 0, 0.6), 0 0 20px rgba(212, 180, 110, 0.18);
    }

    .empty {
      visibility: hidden;
    }

    .servo-btn {
      width: 200px;
      height: 70px;
      font-size: 18px;
      font-weight: 700;
      margin: 15px 10px;
      background: linear-gradient(180deg, #0f2230 0%, #091724 100%);
      border-radius: 12px;
      border: 1px solid rgba(212, 180, 110, 0.08);
      color: #e6d7b0;
      box-shadow: 0 8px 28px rgba(3, 6, 12, 0.6);
      cursor: pointer;
      transition: transform 0.08s ease, background 0.08s ease;
      user-select: none;
      -webkit-user-select: none;
      touch-action: manipulation;
    }

    .servo-btn:active {
      background: linear-gradient(180deg, #d4b46e 0%, #b58f3b 100%);
      color: #061018;
      transform: scale(0.98);
      box-shadow: 0 4px 12px rgba(0, 0, 0, 0.6), 0 0 18px rgba(212, 180, 110, 0.14);
    }

    #sliderBlue {
      width: 320px;               
      height: 14px;              
      -webkit-appearance: none;
      appearance: none;
      background: rgba(212,180,110,0.10);
      border-radius: 10px;
      outline: none;
      margin-top: 6px;
      cursor: pointer;
    }

    /* WebKit track */
    #sliderBlue::-webkit-slider-runnable-track {
      height: 10px;
      border-radius: 10px;
      background: rgba(212,180,110,0.18);
    }

    /* WebKit thumb (the handle) */
    #sliderBlue::-webkit-slider-thumb {
      -webkit-appearance: none;
      width: 34px;
      height: 34px;
      margin-top: -12px; 
      border-radius: 50%;
      background: #d4b46e;
      border: 2px solid #091724;
      box-shadow: 0 2px 6px rgba(0,0,0,0.45);
    }

    #sliderBlue::-moz-range-track {
      height: 10px;
      border-radius: 10px;
      background: rgba(212,180,110,0.18);
    }

    #sliderBlue::-moz-range-thumb {
      width: 28px;
      height: 28px;
      border-radius: 50%;
      background: #d4b46e;
      border: 2px solid #091724;
      box-shadow: 0 2px 6px rgba(0,0,0,0.45);
    }

    @media (max-width: 600px) {
      body {
        padding: 10px;
      }

      h2 {
        font-size: 26px;
      }

      .container {
        gap: 25px;
        margin: 20px 0;
      }

      .pad {
        padding: 12px;
      }

      #sliderBlue { width: 240px; }
    }
  </style>

  <script>
    let currentX = 0;   // steering
    let currentY = 0;   // throttle

    function sendXY() {
      fetch(`/move?x=${currentX}&y=${currentY}`);
    }

    function handlePointerDown(axis, value, e) {
      e.preventDefault();
      if (axis === 'y') currentY = value;
      if (axis === 'x') currentX = value;
      sendXY();
    }

    function handlePointerUp(axis, e) {
      e.preventDefault();
      if (axis === 'y') currentY = 0;
      if (axis === 'x') currentX = 0;
      sendXY();
    }

    function servoCmd(id) {
      if (id === 1) {
        fetch(`/servo?id=1`);
      }
    }

    // handler for Servo BLUE (id=2)
    function blueChanged(val) {
      document.getElementById('blueVal').textContent = val;
      fetch(`/servo?id=2&pos=${val}`);
    }
  </script>

</head>

<body>

  <h2>Team ACI</h2>

  <div class="container">

    <!-- FORWARD / BACK PAD -->
    <div>
      <h3>Forward / Back</h3>
      <div class="pad">
        <div class="empty"></div>
        <button onpointerdown="handlePointerDown('y',-1,event)" onpointerup="handlePointerUp('y',event)">FWD</button>
        <div class="empty"></div>

        <div class="empty"></div>
        <div class="empty"></div>
        <div class="empty"></div>

        <div class="empty"></div>
        <button onpointerdown="handlePointerDown('y',1,event)" onpointerup="handlePointerUp('y',event)">BCK</button>
        <div class="empty"></div>
      </div>
    </div>

    <!-- LEFT / RIGHT PAD -->
    <div>
      <h3>Left / Right</h3>
      <div class="pad">
        <div class="empty"></div>
        <div class="empty"></div>
        <div class="empty"></div>

        <button onpointerdown="handlePointerDown('x',-1,event)" onpointerup="handlePointerUp('x',event)">L</button>

        <div class="empty"></div>

        <button onpointerdown="handlePointerDown('x',1,event)" onpointerup="handlePointerUp('x',event)">R</button>

        <div class="empty"></div>
        <div class="empty"></div>
        <div class="empty"></div>
      </div>
    </div>

  </div>

  <h3>Servo Controls</h3>
  <button class="servo-btn" onclick="servoCmd(1)">Servo BLACK</button>
  <!-- Servo BLUE slider: 5 degree steps -->
  <div style="display:flex;flex-direction:column;align-items:center;gap:8px;margin-top:12px;">
    <label for="sliderBlue" style="color:#f3e7cf;font-weight:700;">Servo BLUE: <span id="blueVal">0</span></label>
    <input id="sliderBlue" type="range" min="0" max="180" step="5" value="0"
           oninput="blueChanged(this.value)" />
  </div>

</body>

</html>

)=====";

// HANDLE MOVEMENT REQUESTS
void handleMove() {
  int x = server.hasArg("x") ? server.arg("x").toInt() : 0;
  int y = server.hasArg("y") ? server.arg("y").toInt() : 0;

  int leftDir = y;
  int rightDir = y;

  if (x == -1) { leftDir--; rightDir++; }
  if (x == 1)  { leftDir++; rightDir--; }

  leftDir  = constrain(leftDir, -1, 1);
  rightDir = constrain(rightDir, -1, 1);

  setMotors(rightDir, leftDir); // reversed logic (leftDir, rightDir)
  server.send(200, "text/plain", "OK");
}

void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

void setup() {
  Serial.begin(115200);
  
  // Initializations
  initMotors();
  initServos();

  setMotors(0,0);

  // WiFi AP
  WiFi.softAP(ssid, password);
  Serial.println("ESP32 AP Started");
  Serial.println(WiFi.softAPIP());

  // Routes
  server.on("/", handleRoot);
  server.on("/move", handleMove);
  server.on("/servo", handleServo);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}