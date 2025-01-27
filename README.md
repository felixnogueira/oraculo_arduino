# Oráculo with Arduino and NeoPixel

## Description
This Arduino sketch controls an 82-LED NeoPixel strip with 6 buttons to trigger various lighting effects. Each button activates a different pattern on the NeoPixel strip. Its visual setup is an approximately 1 meter engine-like cut in wood with the LED strip placed inside the cut, with 6 touch buttons around it. It integrates with a [user interface](https://https://github.com/felixnogueira/oraculo_panel) placed in the middle of this engine through a touchscreen, and the buttons call through serial communication each of them when pressed.

### Components Used
- Adafruit NeoPixel library (`Adafruit_NeoPixel.h`)
- Arduino Thread library (`Thread.h`, `ThreadController.h`)

### Disclaimer
Some parts of this code were written as part of a learning process and may not follow best practices. There are TODOs marked to review and improve the code. This was tested and sent to production. Its accompannying user interface was also written by me using .NET WPF with C# and XAML, but will be rewritten later as it is right now set to private for confidentiality about the client company.

## Setup
### Libraries
- `Adafruit_NeoPixel.h`: Controls the NeoPixel strip.
- `Thread.h`, `ThreadController.h`: Handles multitasking with threads (not fully utilized in current code).

### Pin Configuration
- `NUM_LEDS`: Number of LEDs in the NeoPixel strip.
- `DATA_PIN`: Pin connected to the data input of the NeoPixel strip.
- Buttons (`s1` to `s6`): Digital pins for the buttons.

### Variables
- **Brightness Levels**: Defines different brightness levels (`fullBrightness`, `mediumBrightness`, `lowBrightness`, `noBrightness`).
- **Colors**: Predefined colors (`redC`, `greenC`, `blueC`, `blackC`, `whiteC`) for NeoPixel LEDs.
- **Delays**: Various delay durations (`delayOn`, `delayOff`, `btnEffectOn`, `btnEffectOff`, `delayE`, `requiredDuration`).

## Functions
- **`setup()`**: Initializes serial communication, sets up pins, initializes NeoPixel strip, and sets initial strip color (`red` for LEDs 0-63).
- **Button Activation Functions (`btn1Active()` to `btn6Active()`)**:
  - Each function turns off button LEDs (`lightoffBtns()`), turns on strip LEDs (`lightup()`), and creates specific visual effects.
  - They handle button presses (`s1` to `s6`) with unique patterns and timings on the NeoPixel strip.

- **`closeApp()`**: Function that handles the user interface shutdown logic, as it is a TV screen partially hidden by the engine's round interior, making close buttons as we usually see in windows inaccessible. To actually close the app the user must touch specific sensor buttons for a specific time, and the Arduino sends the signal through this function to terminate the application.

## Loop
- **Serial Communication**: Checks for "Restart" command to reset the NeoPixel strip. This command is sent by the user interface after 30 seconds of inactivity, which is read also from the serial through the button state handling mentioned below.
- **Button State Handling**: Monitors button states (`s1` to `s6`) and triggers corresponding `btnActive()` functions based on button press detection.
- **Auto Shutdown**: Monitors simultaneous press of `s3` and `s5` buttons for 3 seconds to initiate application shutdown (`closeApp()`).

### Notes
- The code uses delays (`delay()`) for timing, which may affect responsiveness to button presses and overall performance.
- It initializes button pins with `INPUT_PULLUP` mode for internal pull-up resistors.
- Serial output (`Serial.println()`), in this case, does not provide debugging information. It is strictly used for communication with the UI.

## TODO
- Review and optimize code for better performance and readability.
- Implement proper use of threads for multitasking, as intended with `Thread` and `ThreadController` libraries.
