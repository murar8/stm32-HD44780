# stm32-HD44780

This is a peripheral driver library for interfacing stm32 microcontrollers with the HD44780 display driver. The implementation uses the stm32 HAL to maximise device compatibility.

## Features

-   Pure C implementation.
-   Only depends on the stm32 HAL include file.
-   4 bit and 8 bit operation.
-   5x8 dots and 5x10 dots symbol generation.
-   Accurate software delays.

## Installation

This library is meant to be used in projects that employ the stm32 HAL library. The easiest way to include the library in your project is to simply copy `HD44780.h` to your include directory and `HD44780.c` to your source directory. The aforementioned files can be downloaded from the [releases](https://github.com/murar8/stm32-HD44780/releases) page.

## API documentation

Documentation for the latest version is available at https://murar8.github.io/stm32-HD44780/latest

If you want to read the documentation for a specific version you can append the version tag to the base url. Example: https://murar8.github.io/stm32-HD44780/v0.1.0

## Usage examples

Some common usage scenarios are listed below.

### Initialization, 4 bit mode, 2 lines, 5x8 character font

```cpp
HD44780 lcd = {
    .rs_gpio = LCD_RS_GPIO_Port,
    .rw_gpio = LCD_RW_GPIO_Port,
    .en_gpio = LCD_EN_GPIO_Port,
    .d4_gpio = LCD_D4_GPIO_Port,
    .d5_gpio = LCD_D5_GPIO_Port,
    .d6_gpio = LCD_D6_GPIO_Port,
    .d7_gpio = LCD_D7_GPIO_Port,
    .rs_pin = LCD_RS_Pin,
    .rw_pin = LCD_RW_Pin,
    .en_pin = LCD_EN_Pin,
    .d4_pin = LCD_D4_Pin,
    .d5_pin = LCD_D5_Pin,
    .d6_pin = LCD_D6_Pin,
    .d7_pin = LCD_D7_Pin,
};

HD44780_init(&lcd);
```

### Initialization, 8 bit mode, single line, 5x10 character font

```cpp
HD44780 lcd = {
    .rs_gpio = LCD_RS_GPIO_Port,
    .rw_gpio = LCD_RW_GPIO_Port,
    .en_gpio = LCD_EN_GPIO_Port,
    .d0_gpio = LCD_D0_GPIO_Port,
    .d1_gpio = LCD_D1_GPIO_Port,
    .d2_gpio = LCD_D2_GPIO_Port,
    .d3_gpio = LCD_D3_GPIO_Port,
    .d4_gpio = LCD_D4_GPIO_Port,
    .d5_gpio = LCD_D5_GPIO_Port,
    .d6_gpio = LCD_D6_GPIO_Port,
    .d7_gpio = LCD_D7_GPIO_Port,
    .rs_pin = LCD_RS_Pin,
    .rw_pin = LCD_RW_Pin,
    .en_pin = LCD_EN_Pin,
    .d0_pin = LCD_D0_Pin,
    .d1_pin = LCD_D1_Pin,
    .d2_pin = LCD_D2_Pin,
    .d3_pin = LCD_D3_Pin,
    .d4_pin = LCD_D4_Pin,
    .d5_pin = LCD_D5_Pin,
    .d6_pin = LCD_D6_Pin,
    .d7_pin = LCD_D7_Pin,
    .interface_8_bit = true,
    .single_line = true,
    .font_5x10 = true,
};

HD44780_init(&lcd);
```

### Printing a string on the lcd

```cpp
HD44780_put_str(&lcd, "Hello, world!");
```

### Generating and printing a new 5x8 symbol

```cpp
uint8_t skull[8] = {
    0b00000,
    0b01110,
    0b10001,
    0b11011,
    0b10001,
    0b01110,
    0b01110,
    0b00000
};

HD44780_create_symbol(&lcd, 0x04, false, skull);
HD44780_put_str(&lcd, "\x04");
```

### Enable cursor and blinking

```cpp
HD44780_Config lcd_config = { .enable_cursor = true, .enable_blink = true };
HD44780_configure(&lcd, &lcd_config);
```

### Update the text in a specific position

```cpp
HD44780_put_str(&lcd, "Temperature: 21C");
HD44780_cursor_to(&lcd, 13, 0);
HD44780_put_str(&lcd, "30");
```

## Donations

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=WW7VLKVE9YP8Q&source=url)

I do not expect to make any money from this project but if you would like to buy me a coffee or something you are welcome to do so :)

## License

Copyright (c) 2021 Lorenzo Murarotto <lnzmrr@gmail.com>

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
