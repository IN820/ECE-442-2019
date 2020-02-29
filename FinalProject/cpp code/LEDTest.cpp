#include <iostream>
#include <wiringPi.h>
#include <csignal>

// flag used to exit from the main loop
bool RUNNING = true;

// FLash an LED
void blink_led(int led, int time) {
    digitalWrite(led, HIGH);
    delay(time);
    digitalWrite(led, LOW);
    delay(time);
}

// detect if CTRL-C signal is detected
void my_handler(int s) {
    std::cout << "Detected CTRL-C signal no. " << s << '\n';
    RUNNING = false;
}

int main() {
    // Define a callback function to be called if CTRL-C is detected
    std::signal(SIGINT, my_handler);

    // Initialize wiringPi to allow the use of pin numbering
    wiringPiSetupGpio();

    std::cout << "Controlling the GPIO pins\n";

    // Define the 3 pins
    int red = 17, yellow = 22, green = 6;

    // Setup the pins
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);

    int time = 1000;   // interval time setup
    while(RUNNING) {
        blink_led(red, time);
        blink_led(yellow, time);
        blink_led(green, time);
    }

    std::cout << "Program ends\n";
}
