# Temperature and Humidity Monitor with ST7735 Display
This project demonstrates how to use an ST7735 RGB IPS LCD display with an Arduino Uno to read and display temperature and humidity data from a DHT11 sensor. The project includes functionality to display a welcome message, show real-time temperature and humidity data, and visualize this data with a bar graph.

## Components Used
Arduino Uno: Microcontroller board.

DHT11 Sensor: Measures temperature and humidity.

ST7735 0.96-inch 80x160 RGB LCD Display: Displays data and graphical output.

Connecting Wires: To connect the components.
## Libraries Required
DHT: For interfacing with the DHT11 sensor.

Adafruit_GFX: Core graphics library used with Adafruit displays.

Adafruit_ST7735: Specific library for the ST7735 display.

Install these libraries via the Arduino Library Manager or download them from their respective repositories:

## DHT Library
Adafruit GFX Library
Adafruit ST7735 Library
Circuit Diagram

### Connect the DHT11 sensor and ST7735 display to the Arduino Uno as follows:
#### DHT11 Sensor

VCC to 5V

GND to GND

Data to Digital Pin 2

#### ST7735 Display

CS to Digital Pin 6

RST to Digital Pin 5

DC to Digital Pin 7

MOSI to Digital Pin 11

CLK to Digital Pin 13

GND to GND

VCC to 5V
