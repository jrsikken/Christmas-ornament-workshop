
#include <Adafruit_TinyUSB.h>
#include <bluefruit.h>

const int rode_led   = 0;
const int groene_led = 1;
const int blauwe_led = 2;
const int ground     = 3;


uint32_t lastBlink = 0;

bool animationRunning = false;
uint32_t animationStart = 0;

// --------------------------------------------------
// RGB helper
// --------------------------------------------------

void setColor(bool r, bool g, bool b)
{
  digitalWrite(rode_led, r);
  digitalWrite(groene_led, g);
  digitalWrite(blauwe_led, b);
}

// --------------------------------------------------
// BLE callbacks
// --------------------------------------------------

void connect_callback(uint16_t conn_handle)
{
  Serial.println("Connected");

  animationRunning = true;
  animationStart = millis();
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  Serial.println("Disconnected");

  animationRunning = false;
  setColor(0, 0, 0);
}

// --------------------------------------------------
// Low power blink
// --------------------------------------------------

void lowPowerBlink()
{
  if (millis() - lastBlink >= 1000)
  {
    lastBlink = millis();

    digitalWrite(groene_led, HIGH);
    delay(15);
    digitalWrite(groene_led, LOW);
  }
}

// --------------------------------------------------
// Rainbow animation
// --------------------------------------------------

void rainbowAnimation()
{
  static uint32_t lastStep = 0;
  static uint8_t step = 0;

  if (millis() - lastStep < 100)
    return;

  lastStep = millis();

  switch (step)
  {
    case 0: setColor(1,0,0); break;
    case 1: setColor(1,1,0); break;
    case 2: setColor(0,1,0); break;
    case 3: setColor(0,1,1); break;
    case 4: setColor(0,0,1); break;
    case 5: setColor(1,0,1); break;
  }

  step++;

  if (step > 5)
    step = 0;
}

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup()
{
  Serial.begin(115200);

  pinMode(rode_led, OUTPUT);
  pinMode(groene_led, OUTPUT);
  pinMode(blauwe_led, OUTPUT);
    pinMode(ground, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);


  Serial.begin(115200);

  Bluefruit.begin();
  Bluefruit.setTxPower(-8);
  Bluefruit.setName("BeaconLED");

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  Bluefruit.Advertising.addFlags(
    BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

  Bluefruit.ScanResponse.addName();

  // ongeveer 2 seconden advertising interval
  Bluefruit.Advertising.setInterval(3200, 3200);
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
  Serial.println("Advertising...");

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(rode_led, LOW);
  digitalWrite(groene_led, LOW);
  digitalWrite(blauwe_led, LOW);
  digitalWrite(ground, LOW);

}

void loop()
{
digitalWrite(LED_BLUE, HIGH);
  if (animationRunning)
  {
    rainbowAnimation();

    if (millis() - animationStart > 10000)
    {
      animationRunning = false;

      setColor(0, 0, 0);

      if (Bluefruit.connected())
      {
        Bluefruit.disconnect(0);
      }
    }
  }
  else
  {
    lowPowerBlink();
  }

  waitForEvent();
}