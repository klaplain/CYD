// ##################################################################################
// USER DEFINED SETTINGS FOR ELEGOO / CYD 2.8" ESP32-2432S028R
// ##################################################################################

#define USER_SETUP_INFO "Elegoo_CYD_2.8"

// Section 1: Display Driver
#define ILI9341_DRIVER     1  // Defines the display driver used by this hardware

// Section 2: SPI Pin Mapping
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data/Command control pin
#define TFT_RST  33// Set to -1 if connected to ESP32 RESET button

// Touch Screen SPI Pin Mapping
#define TOUCH_CS 33  // Chip select pin (T_CS) of touch screen

// Backlight Pin Configuration
#define TFT_BL   21  // LED back-light GPIO pin
#define TFT_BACKLIGHT_ON HIGH  // Level to turn ON backlight

// Section 3: Fonts to Load (Optional but recommended for examples)
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font
#define LOAD_FONT2  // Font 2. Small 16 pixel font
#define LOAD_FONT4  // Font 4. Medium 26 pixel font
#define LOAD_FONT6  // Font 6. Large 48 pixel font
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font
#define LOAD_FONT8  // Font 8. Large 75 pixel font
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts

// Section 4: SPI Frequency
#define SPI_FREQUENCY  55000000 // SPI clock frequency for display (55MHz)
#define SPI_TOUCH_FREQUENCY  2500000 // SPI clock frequency for touch (2.5MHz)

