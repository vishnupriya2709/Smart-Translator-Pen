/*
  Project: Smart Translator Pen
  Author: Vishnupriya Seshadri
  Description:
    A smart pen designed to help visually impaired people translate
    written or braille text into their preferred language and listen
    to it through a built-in speaker. The system uses OCR (Optical Character Recognition),
    translation APIs, and text-to-speech (TTS) output.

  Components:
    - ESP32 or Arduino + Wi-Fi Module
    - Camera or OCR sensor module
    - DFPlayer Mini (Audio module)
    - Speaker
    - Buttons for selecting output language
    - Small projector or OLED (optional)
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>

// --- WiFi Credentials ---
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

// --- Define Pins ---
#define LANGUAGE_BUTTON_PIN 4
#define SPEAKER_TX 16
#define SPEAKER_RX 17

// --- Global Variables ---
String inputText = "";
String translatedText = "";
String targetLanguage = "ta";  // Default: Tamil (you can change this)

// --- Initialize Speaker (DFPlayer Mini) ---
SoftwareSerial mySerial(SPEAKER_RX, SPEAKER_TX);
int buttonState = 0;

// --- Setup Function ---
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(LANGUAGE_BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Smart Translator Pen Initializing...");
  connectToWiFi();
  Serial.println("Ready to Scan!");
}

// --- Connect to WiFi ---
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

// --- Main Loop ---
void loop() {
  // Step 1: Check for button press to change language
  buttonState = digitalRead(LANGUAGE_BUTTON_PIN);
  if (buttonState == LOW) {
    changeLanguage();
  }

  // Step 2: Simulate scanning text from OCR
  inputText = scanText();

  // Step 3: Translate the scanned text
  translatedText = translateText(inputText, targetLanguage);

  // Step 4: Convert translated text to speech
  playSpeech(translatedText);

  delay(10000); // Wait before next scan
}

// --- Function to simulate text scanning ---
String scanText() {
  // In actual hardware, OCR module or camera reads printed text
  Serial.println("\n[Scanning text...]");
  delay(2000);
  String scanned = "Hello world";
  Serial.print("Detected text: ");
  Serial.println(scanned);
  return scanned;
}

// --- Function to handle translation (simulation) ---
String translateText(String input, String language) {
  Serial.println("[Translating text...]");
  delay(2000);

  // In real case, use a Translation API (e.g., Google or Microsoft)
  if (language == "ta") return "வணக்கம் உலகம்";     // Tamil
  if (language == "hi") return "नमस्ते दुनिया";       // Hindi
  if (language == "fr") return "Bonjour le monde";   // French
  if (language == "jp") return "こんにちは世界";        // Japanese
  return "Hello World"; // Default English
}

// --- Function to simulate speech output ---
void playSpeech(String text) {
  Serial.print("[Speaking: ");
  Serial.print(text);
  Serial.println("]");
  delay(3000);
  Serial.println("Playback complete.\n");
}

// --- Function to change translation language ---
void changeLanguage() {
  Serial.println("\nLanguage button pressed!");

  if (targetLanguage == "ta") {
    targetLanguage = "hi";
    Serial.println("Language changed to Hindi");
  } else if (targetLanguage == "hi") {
    targetLanguage = "fr";
    Serial.println("Language changed to French");
  } else if (targetLanguage == "fr") {
    targetLanguage = "jp";
    Serial.println("Language changed to Japanese");
  } else {
    targetLanguage = "ta";
    Serial.println("Language changed to Tamil");
  }

  delay(1000);
}
