#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 0;
bool startLyrics = false;
//ini buat lirik nya 
String lyrics[] = {
  "Sudah Terbiasa", "Terjadi", "Tantee",
  "Teman Datang", "Ketika", "Lagi",
  "Butuh Saja", "Coba", "Kalau",
  "Lagi Susah", "Mereka Semuaaa", "Menghilangg",
  "Apakah Spek Standar", "Seperti Ini", "Yang Para",
  "Pemirsa Inginkan?"
};

// Buat atur waktu teks nya berapa lama muncul nya
int durations[] = {
  1600, 1200, 1000,
  1500, 1000, 1000,
  1500, 1000, 900,
  1400, 1000, 1200,
  1600, 1100, 800,
  1800
};

int lyricCount = sizeof(lyrics) / sizeof(lyrics[0]);
int currentIndex = 0;
unsigned long previousMillis = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 25);
  display.println("Pincit");
  display.display();
}

void loop() {
  if (!startLyrics) {
    if (digitalRead(buttonPin) == LOW) {
      startLyrics = true;
      display.clearDisplay();
      delay(500);
    } else {
      return;
    }
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= durations[currentIndex]) {
    previousMillis = currentMillis;

    String kata = lyrics[currentIndex];

    display.clearDisplay();
    int16_t x1, y1;
    uint16_t w, h;
    display.setTextSize(1);
    display.getTextBounds(kata, 0, 0, &x1, &y1, &w, &h);
    int16_t x = (SCREEN_WIDTH - w) / 2;
    int16_t y = (SCREEN_HEIGHT - h) / 2;

    display.setCursor(x, y);
    display.println(kata);
    display.display();

    currentIndex++;
    if (currentIndex >= lyricCount) {
      currentIndex = 0;
    }
  }
}
