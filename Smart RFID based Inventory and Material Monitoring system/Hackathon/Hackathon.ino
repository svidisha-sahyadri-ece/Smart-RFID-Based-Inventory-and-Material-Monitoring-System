#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP_Mail_Client.h>

// WiFi credentials
const char* ssid = "Your username";
const char* password = "password";

// Email credentials
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "xxxx@gmail.com"
#define AUTHOR_PASSWORD "xxxxxxxx"
#define RECIPIENT_EMAIL "xxxxxxx"

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RFID
#define SS_PIN 5
#define RST_PIN 4
MFRC522 rfid(SS_PIN, RST_PIN);

// Email client objects
Session_Config config;
SMTP_Message message;
SMTPSession smtp;

// Item details
struct Item {
  String name;
  String uid;
  int count;
  bool lowNotified = false;
};

Item items[] = {
  {"iPhone", "53 74 A6 A3", 100},
  {"Lava", "73 60 DE 11", 100},
  {"Infinix", "83 8E 7C 11", 100}
};

const int NUM_ITEMS = sizeof(items) / sizeof(items[0]);

void setup() {
  Serial.begin(115200);

  // OLED init
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Shelf Init...");
  display.display();

  // RFID init
  SPI.begin(18, 19, 23);
  rfid.PCD_Init();

  // WiFi init
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  updateDisplay();
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  String scannedUID = getTagUID();
  Serial.println("Scanned UID: " + scannedUID);

  for (int i = 0; i < NUM_ITEMS; i++) {
    if (scannedUID == items[i].uid) {
      if (items[i].count > 0) {
        items[i].count--;
        Serial.println(items[i].name + " count: " + items[i].count);
        updateDisplay();

        if (items[i].count <= 95 && !items[i].lowNotified) {
          sendEmailAlert(items[i].name, items[i].count);
          items[i].lowNotified = true;
        }
      }
      break;
    }
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);
}

String getTagUID() {
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uid += " ";
  }
  uid.toUpperCase();
  return uid;
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  for (int i = 0; i < NUM_ITEMS; i++) {
    display.print(items[i].name);
    display.print(": ");
    display.println(items[i].count);
  }
  display.display();
}

void sendEmailAlert(String itemName, int count) {
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "";

  message.sender.name = "Smart Shelf";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Low Stock Alert: " + itemName;
  message.addRecipient("User", RECIPIENT_EMAIL);
  message.text.content = "Alert: " + itemName + " stock is low.\nRemaining: " + String(count);
  message.text.charSet = "utf-8";
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;

  smtp.callback([](SMTP_Status status) {
    if (status.success()) {
      Serial.println("Email sent successfully.");
    } else {
      Serial.print("Email failed: ");
      Serial.println(status.info());
    }
  });

  Serial.println("Sending email...");
  if (!smtp.connect(&config)) {
    Serial.print("SMTP connection failed: ");
    Serial.println(smtp.errorReason());
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.print("Sending failed: ");
    Serial.println(smtp.errorReason());
  }

  smtp.closeSession();
}