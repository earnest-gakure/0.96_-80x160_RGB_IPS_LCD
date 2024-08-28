#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define PIN_DHT 2
DHT dht(PIN_DHT, DHT11); // Creating an object for DHT11 sensor

#define TFT_CS     6
#define TFT_RST    5
#define TFT_DC     7

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  tft.initR(INITR_MINI160x80);  // Initialize the display
  tft.fillScreen(ST7735_BLACK);
  
  dht.begin();
  welcome_msg();
  
  
}

void loop() {
  tft.fillRect(0, 0, 160, 80, ST7735_BLUE);  // Draw a filled rectangle as a background
  
  display_data();
  delay(5000);
  tft.fillScreen(ST7735_BLACK);
  drawBarGraph();
  
  delay(5000);
  tft.fillScreen(ST7735_BLACK);
}

void welcome_msg() {
  tft.setRotation(1);
  tft.setTextSize(3);
  printWrappedText("WELCOME", ST7735_WHITE, 3, 30, 30);
  delay(2000);
  tft.fillScreen(ST7735_BLACK);

  tft.setTextSize(2);
  printWrappedText("TEMERATURE AND HUMIDITY DISPLAY SYSTEM", ST7735_WHITE, 2, 5, 5);
  delay(2000);
  tft.fillScreen(ST7735_BLACK);

  tft.setTextSize(2);
  printWrappedText("LET'S GO!", ST7735_WHITE, 2, 30, 30);
  delay(2000);
  tft.fillScreen(ST7735_BLACK);
}

void display_data() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  String Temperature = String(temp, 1) + "C";
  String Humidity = String(humidity, 1) + "%";

  printWrappedText("TEMP:", ST7735_WHITE,3, 5, 10);
  printWrappedText(Temperature, ST7735_WHITE, 3, 65, 10);
  printWrappedText("HUM:", ST7735_WHITE,3, 5, 40);
  printWrappedText(Humidity, ST7735_WHITE, 3, 65, 40);

  Serial.print("temp = ");
  Serial.print(temp);
  Serial.print(" C   ");
  Serial.print("humidity = ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.println();
}

// Function to draw a bar graph
void drawBarGraph() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Normalize values to fit within the graph height (60 pixels max)
  int tempBarHeight = map(temp, 0, 50, 0, 60);  // Assuming max temperature of 50°C
  int humidityBarHeight = map(humidity, 0, 100, 0, 60);  // Assuming max humidity of 100%

  // Draw temperature bar (red)
  tft.fillRect(40, 80 - tempBarHeight, 20, tempBarHeight, ST7735_RED);
  tft.drawRect(40, 20, 20, 60, ST7735_WHITE);  // Draw the border
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(40, 5);
  tft.print("Temp");

  // Draw humidity bar (blue)
  tft.fillRect(100, 80 - humidityBarHeight, 20, humidityBarHeight, ST7735_BLUE);
  tft.drawRect(100, 20, 20, 60, ST7735_WHITE);  // Draw the border
  tft.setCursor(100, 5);
  tft.print("Humid");

  // Draw labels for calibration
  tft.setTextSize(1);
  for (int i = 0; i <= 5; i++) {
    int y = 80 - i * 12;
    tft.setCursor(20, y - 4);
    tft.print(i * 10);  // Temperature scale
    tft.setCursor(140, y - 4);
    tft.print(i * 20);  // Humidity scale
    tft.drawFastHLine(38, y, 5, ST7735_WHITE);  // Tick mark for temperature
    tft.drawFastHLine(120, y, 5, ST7735_WHITE);  // Tick mark for humidity
  }
}

int getTextWidth(String text, int textSize) {
  int textWidth = 0;
  int charWidth = 6; // Approximate width of a character in pixels for text size 1

  for (int i = 0; i < text.length(); i++) {
    textWidth += charWidth;
  }

  return textWidth * textSize;
}

//The function splits the input text into words and calculates whether each word fits on the current line. If not, it wraps to the next line.
void printWrappedText(String text, uint16_t color, int textSize, int CursorX, int CursorY) {
  int cursorX = CursorX;
  int cursorY = CursorY;
  int lineHeight = 8 * textSize;

  String word = "";
  for (int i = 0; i < text.length(); i++) {
    char c = text[i];

    if (c == ' ' || i == text.length() - 1) {
      if (i == text.length() - 1) word += c;

      int wordWidth = getTextWidth(word, textSize);

      if (cursorX + wordWidth > tft.width()) {
        cursorX = 0;
        cursorY += lineHeight;
      }

      tft.setCursor(cursorX, cursorY);
      tft.print(word);
      cursorX += wordWidth + getTextWidth(" ", textSize);

      word = "";
    } else {
      word += c;
    }
  }
}
