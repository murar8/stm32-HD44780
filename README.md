# stm32-HD44780

This is a peripheral driver library for interfacing stm32 microcontrollers with the HD44780 display driver. The implementation uses the stm32 HAL to maximise device compatibility.

## Features

-   Pure C implementation.
-   Only dependency is the `stm32f1xx_hal.h` HAL include file.
-   8 bit and 4 bit operation.
-   5x8 dots and 5x10 dots symbol generation.
-   Accurate software delays.

## Installation

The easiest way to include the library in your project is to simply copy `inc/HD44780.h` in your include directory, and `src/HD44780.c` in your source directory. A fancier way to install the library could be to clone the library into your project as a submodule, then you could add the `inc/` and `src/` folder to the compiler source paths.

## Example projects

An example STM32CubeIDE project is included in the examples directory. The project is configured for the stm32f103c8, tested using the "blue pill" develpment board. The controller should be wired up in the following way:

| Function | MCU pin |
| -------- | ------- |
| LCD D4   | PB6     |
| LCD D5   | PB7     |
| LCD D6   | PB8     |
| LCD D7   | PB9     |
| LCD EN   | B15     |
| LCD RS   | B13     |
| LCD RW   | B14     |

## Usage examples

Some common usage scenarios are listed below. If you want more detatils the API is documented in `inc/HD44780.h`.

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

I do not expect to make any money from this extension but if you would like to buy me a coffee or something you are welcome to do so :)

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
