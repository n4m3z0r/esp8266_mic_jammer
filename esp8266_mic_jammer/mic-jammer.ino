#include <Arduino.h>

// PIN - PORT ASSIGNMENT DEFINITION FOR OUTPUT
#define OUTPUT_PIN_1 D4
#define OUTPUT_PIN_2 D3

// Created in Excel / Libreoffice - will randomly 
// swing pulse width to achieve noise effect around the center 25kHz frequency
const uint8_t randomized[] = 
{
    20, 50, 60, 69, 44, 24, 49, 27, 36, 58, 45, 47, 68, 53, 63, 62, 46, 66, 70, 19, 41, 32, 67, 19, 38, 35, 55, 60, 22, 68, 29, 24, 64,
    29, 55, 19, 12, 30, 32, 36, 21, 46, 63, 32, 42, 11, 58, 38, 21, 46, 40, 39, 65, 28, 16, 42, 54, 63, 24, 19, 40, 18, 40, 19, 36, 16,
    40, 43, 37, 41, 58, 25, 52, 40, 61, 70, 65, 16, 28, 50, 30, 11, 19, 31, 10, 23, 30, 10, 68, 30, 36, 59, 66, 38, 47, 68, 23, 46, 51,
    39, 46, 25, 31, 45, 64, 49, 22, 21, 13, 51, 19, 64, 69, 21, 59, 22, 40, 32, 67, 28, 31, 37, 10, 61, 39, 41, 48, 17, 70, 53, 11, 39,
    19, 66, 29, 60, 49, 24, 46, 27, 64, 56, 33, 66, 70, 51, 49, 38, 14, 60, 58, 39, 65, 67, 34, 48, 34, 14, 26, 21, 47, 58, 57, 38, 36,
    37, 21, 17, 47, 63, 63, 63, 44, 54, 12, 48, 29, 57, 70, 35, 10, 59, 22, 20, 23, 26, 48, 22, 64, 70, 23, 40, 17, 51, 16, 46, 13, 51,
    53, 22, 17, 59, 52, 59, 36, 53, 47, 25, 30, 63, 19, 20, 10, 19, 51, 65, 22, 41, 47, 55, 23, 51, 68, 32, 34, 70, 10, 69, 41, 20, 42,
    30, 49, 70, 60, 70, 64, 18, 37, 65, 61, 38, 58, 43, 23, 54, 67, 51, 30, 28, 14, 25, 24, 46, 35, 26, 50, 67, 18, 57, 45, 18, 11, 64,
    61, 68, 54, 47, 61, 54, 13, 17, 14, 12, 56, 58, 16, 33, 54, 55, 54, 35, 65, 15, 26, 18, 69, 37, 67, 64, 33, 53, 53, 38, 49, 32, 16,
    68, 61, 69, 56, 26, 59, 48, 10, 44, 63, 17, 19, 18, 22, 18, 51, 54, 39, 11, 65, 40, 50, 10, 30, 15, 64, 69, 68, 34, 18, 48, 41, 56,
    35, 19, 50, 66, 10, 64, 58, 13, 56, 42, 17, 27, 40, 14, 60, 67, 33, 50, 26, 61, 44, 65, 24, 43, 41, 55, 56, 59, 41, 40, 58, 19, 56,
    68, 65, 18, 19, 37, 58, 34, 48, 14, 14, 12, 15, 66, 69, 33, 64, 47, 62, 65, 30, 26, 21, 53, 12, 45, 50, 38, 10, 30, 23, 40, 40, 51,
    37, 43, 13, 27, 60, 54, 24, 64, 21, 66, 60, 57, 19, 58, 13, 43, 63, 52, 23, 24, 46, 54, 39, 49, 25, 35, 15, 25, 34, 22, 32, 66, 21,
    19, 52, 51, 33, 49, 18, 50, 23, 43, 48, 67, 41, 21, 46, 14, 40, 24, 12, 51, 46, 17, 46, 25, 24, 13, 36, 15, 18, 28, 62, 28, 28, 63,
    59, 58, 64, 66, 54, 19, 42, 63, 64, 23, 41, 67, 10, 11, 65, 39, 15, 33, 16, 55, 10, 50, 50, 43, 70, 55, 34, 29, 50, 32, 56, 16, 35,
    45, 20, 52, 29, 45, 53, 23, 26, 35, 33, 56, 40, 28, 59, 59, 46, 17, 45, 48, 68, 62, 44, 29, 52, 11, 31, 41, 39, 56, 64, 26, 23, 20,
    15, 63, 63, 22, 17, 36, 22, 37, 19, 24, 42, 51, 56, 69, 64, 31, 56, 29, 26, 53, 29, 53, 39, 11, 27, 41, 32, 63, 40, 20, 52, 69, 15,
    36, 54, 61, 27, 23, 56, 49, 59, 14, 64, 11, 53, 27, 21, 31, 14, 62, 14, 57, 32, 46, 68, 63, 38, 65, 46, 60, 14, 57, 50, 12, 20, 30,
    39, 25, 50, 23, 34, 56, 23, 54, 24, 47, 58, 54, 36, 27, 30, 55, 50, 51, 12, 34, 11, 35, 46, 30, 15, 34, 15, 65, 15, 11, 60, 41, 54,
    12, 41, 27, 13, 53, 54, 54, 51, 62, 47, 23, 31, 25, 24, 45, 69, 38, 53, 32, 51, 67, 67, 35, 25, 48, 55, 55, 68, 21, 51, 51, 35, 32,
    37, 47, 51, 47, 69, 37, 54, 32, 32, 37, 27, 44, 54, 29, 61, 45, 52, 54, 36, 44, 69, 65, 68, 18, 31, 36, 31, 57, 69, 64, 18, 37, 34,
    36, 54, 66, 36, 16, 13, 19, 65, 29, 56, 45, 38, 40, 57, 61, 65, 24, 56, 32, 55, 44, 46, 28, 37, 29, 61, 63, 60, 49, 23, 10, 21, 13,
    23, 38, 24, 36, 41, 11, 12, 37, 70, 67, 67, 38, 31, 56, 48, 39, 31, 65, 38, 66, 30, 63, 29, 10, 65, 28, 23, 54, 46, 61, 34, 29, 11,
    52, 15, 15, 34, 28, 40, 16, 29, 36, 39, 52, 37, 53, 23, 27, 66, 57, 57, 25, 37, 57, 37, 28, 44, 64, 34, 30, 17, 41, 51, 15, 47, 36,
    67, 59, 68, 48,
};

void setup() {
    // Initialize digital pin OUTPUT_PIN_1 and OUTPUT_PIN_2 as output.
    pinMode(OUTPUT_PIN_1, OUTPUT);
    pinMode(OUTPUT_PIN_2, OUTPUT);

    // Start PWM on OUTPUT_PIN_1 and OUTPUT_PIN_2 at 25kHz (approx. frequency)
    analogWriteFreq(25000);
}

void loop() {
    for (int i = 0; i < sizeof(randomized); i++) {
        // Read the next random value
        uint8_t pulseWidth = pgm_read_byte(&randomized[i]);
        analogWrite(OUTPUT_PIN_1, pulseWidth);
        analogWrite(OUTPUT_PIN_2, pulseWidth);
        delayMicroseconds(40); // adjust this value to get the desired frequency and duty cycle
    }
}