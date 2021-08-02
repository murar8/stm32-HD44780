/**
 * @file HD44780.h %HD44780 peripheral library for stm32 microcontrollers. More information is available at the
 * project's home page: https://github.com/murar8/stm32-HD44780
 *
 * @version 0.1.3
 *
 * @author Lorenzo Murarotto <lnzmrr@gmail.com>
 *
 * @copyright Copyright 2021 Lorenzo Murarotto. This project is released under the MIT license.
 */

#ifndef __HD44780_H__
#define __HD44780_H__

#include <stdbool.h>
#include <stdlib.h>

#if !defined(STM32F0) && !defined(STM32F1) && !defined(STM32F2) && !defined(STM32F3) && !defined(STM32F4) &&           \
    !defined(STM32F7) && !defined(STM32H7) && !defined(STM32G0) && !defined(STM32G4) && !defined(STM32L0) &&           \
    !defined(STM32L1) && !defined(STM32L4) && !defined(STM32L5) && !defined(STM32WB) && !defined(STM32WL)
#include "HD44780_conf.h"
#endif

#if defined(STM32F0)
#include <stm32f0xx_hal.h>
#elif defined(STM32F1)
#include <stm32f1xx_hal.h>
#elif defined(STM32F2)
#include <stm32f2xx_hal.h>
#elif defined(STM32F3)
#include <stm32f3xx_hal.h>
#elif defined(STM32F4)
#include <stm32f4xx_hal.h>
#elif defined(STM32F7)
#include <stm32f7xx_hal.h>
#elif defined(STM32H7)
#include <stm32h7xx_hal.h>
#elif defined(STM32G0)
#include <stm32g0xx_hal.h>
#elif defined(STM32G4)
#include <stm32g4xx_hal.h>
#elif defined(STM32L0)
#include <stm32l0xx_hal.h>
#elif defined(STM32L1)
#include <stm32l1xx_hal.h>
#elif defined(STM32L4)
#include <stm32l4xx_hal.h>
#elif defined(STM32L5)
#include <stm32l5xx_hal.h>
#elif defined(STM32WB)
#include <stm32wbxx_hal.h>
#elif defined(STM32WL)
#include <stm32wlxx_hal.h>
#else
#error No MPU architecture selected.
#endif

/**
 * %HD44780 controller instance.
 * Contains all the information on the hardware configuration of the controller,
 * and some required initialization settings.
 */
typedef struct
{
    GPIO_TypeDef *rs_gpio; /**< GPIO port of the mcu pin connected to the controller's RS line. */
    GPIO_TypeDef *rw_gpio; /**< GPIO port of the mcu pin connected to the controller's RW line. */
    GPIO_TypeDef *en_gpio; /**< GPIO port of the mcu pin connected to the controller's EN line. */
    GPIO_TypeDef *d0_gpio; /**< GPIO port of the mcu pin connected to the controller's D0 line. */
    GPIO_TypeDef *d1_gpio; /**< GPIO port of the mcu pin connected to the controller's D1 line. */
    GPIO_TypeDef *d2_gpio; /**< GPIO port of the mcu pin connected to the controller's D2 line. */
    GPIO_TypeDef *d3_gpio; /**< GPIO port of the mcu pin connected to the controller's D3 line. */
    GPIO_TypeDef *d4_gpio; /**< GPIO port of the mcu pin connected to the controller's D4 line. */
    GPIO_TypeDef *d5_gpio; /**< GPIO port of the mcu pin connected to the controller's D5 line. */
    GPIO_TypeDef *d6_gpio; /**< GPIO port of the mcu pin connected to the controller's D6 line. */
    GPIO_TypeDef *d7_gpio; /**< GPIO port of the mcu pin connected to the controller's D7 line. */

    uint16_t rs_pin; /**< Pin number of the mcu pin connected to the controller's RS line. */
    uint16_t rw_pin; /**< Pin number of the mcu pin connected to the controller's RW line. */
    uint16_t en_pin; /**< Pin number of the mcu pin connected to the controller's EN line. */
    uint16_t d0_pin; /**< Pin number of the mcu pin connected to the controller's D0 line. */
    uint16_t d1_pin; /**< Pin number of the mcu pin connected to the controller's D1 line. */
    uint16_t d2_pin; /**< Pin number of the mcu pin connected to the controller's D2 line. */
    uint16_t d3_pin; /**< Pin number of the mcu pin connected to the controller's D3 line. */
    uint16_t d4_pin; /**< Pin number of the mcu pin connected to the controller's D4 line. */
    uint16_t d5_pin; /**< Pin number of the mcu pin connected to the controller's D5 line. */
    uint16_t d6_pin; /**< Pin number of the mcu pin connected to the controller's D6 line. */
    uint16_t d7_pin; /**< Pin number of the mcu pin connected to the controller's D7 line. */

    /**
     * Use 8 physical data lines (DB7-DB0) for communication with the controller instead of the default 4 lines
     * (DB7-DB4).
     */
    bool interface_8_bit;

    /**
     * Display a single taller line on the display instead of the default 2 lines.
     */
    bool single_line;

    /**
     * Use the 5x10 dots character font instead of the default 5x8 dots font.
     *
     * @warning The 5x10 dots font only supports single line operation ( @ref single_line = true ).
     */
    bool font_5x10;
} HD44780;

/**
 * %HD44780 controller configuration.
 * Use in conjunction with HD44780_configure() to enable/disable the different features of the lcd.
 */
typedef struct
{
    /**
     * Disable the display.
     * Data can still be written with the lcd unpowered and displayed at a later moment.
     */
    bool disable_display;

    /**
     * Make the cursor visible.
     * The cursor is displayed using 5 dots in the 8th line for 5×8 dots font and in the 11th line for 5×10 dots font.
     */
    bool enable_cursor;

    /**
     * Make the character indicated by the cursor blink.
     * The blinking is displayed as switching between all blank dots and displayed character.
     */
    bool enable_blink;

    /**
     * Shift the display when data is entered instead of shifting only the cursor.
     */
    bool shift_display;

    /**
     * Shift the display (depending on the @ref shift_display parameter) and/or cursor in right to left direction
     * instead of left to right when a character is entered.
     */
    bool shift_rtl;
} HD44780_Config;

/**
 * Initialize the necessary hardware peripherals, then configure the controller itself.
 * The initial configuration will be the same as calling HD44780_configure() with all the config flags set to false.
 *
 * @param lcd Controller instance.
 */
void HD44780_init(const HD44780 *lcd);

/**
 * Update the configuration of the controller.
 *
 * @param lcd Controller instance.
 *
 * @param config New controller configuration.
 */
void HD44780_configure(const HD44780 *lcd, const HD44780_Config *config);

/**
 * Clear the display and move the cursor to position 0 of the first line.
 *
 * @param lcd Controller instance.
 */
void HD44780_clear(const HD44780 *lcd);

/**
 * Reset display shift to the initial position and move the cursor to position 0 of the first line.
 *
 * @param lcd Controller instance.
 */
void HD44780_return_home(const HD44780 *lcd);

/**
 * Move the cursor to the desired position.
 *
 * @param lcd Controller instance.
 *
 * @param column Index of the desired cursor position in the line. Must be less than 0x50 in single line mode, and less
 * than 0x28 in two lines mode, or the cursor will wrap to the next line causing undefined behaviour.
 *
 * @param row Index of the desired row. Must be 0 if the controller is configured for single line mode, and 0 or 1 when
 * the controller is in two lines mode.
 */
void HD44780_cursor_to(const HD44780 *lcd, uint8_t column, uint8_t row);

/**
 * Shift the contents of the display right or left by n positions.
 * The first and second line will shift at the same time.
 *
 * @note The execution time of this function will increase linearly with the numbers of positions shifted (~37us /
 * position shifted).
 *
 * @param lcd Controller instance.
 *
 * @param n Number of positions to shift. When the value is positive the diplay will shift left to right,
 * when negative the shift operation will advance right to left.
 */
void HD44780_shift_display(const HD44780 *lcd, int8_t n);

/**
 * Create a user defined character to display in the LCD.
 * The controller memory can store up to 8 5x8 symbols, and up to 4 5x10 symbols.
 *
 * @warning 5x10 symbols need 2 CGRAM slots, so after defining a 5x10 symbol at address n, the next symbol should be
 * defined at address n+2.
 *
 * @param lcd Controller instance.
 *
 * @param address ASCII code of the new symbol, must be in the range from 0 to 7 inclusive.
 *
 * @param font_5x10 Wheteher the new symbol will be a 5x10 character.
 *
 * @param symbol Array of 5 bit values where each bit will determine whether the corresponding pixel is lit up in its
 * corresponding row.
 */
void HD44780_create_symbol(const HD44780 *lcd, uint8_t address, bool font_5x10, const uint8_t symbol[]);

/**
 * Write a single character to the lcd, then advance the cursor.
 * When the character is '\\n' the cursor will advance to the next line, wrapping around from last to first.
 * When the character is '\\t' 4 spaces will be written to the display.
 *
 * @param lcd Controller instance.
 *
 * @param chr Character to be printed to the lcd.
 */
void HD44780_put_char(const HD44780 *lcd, uint8_t chr);

/**
 * Write a string to the lcd, then advance the cursor.
 * The same considerations for special characters from HD44780_put_char() apply to this function.
 *
 * @warning The string must be null terminated.
 *
 * @param lcd Controller instance.
 *
 * @param str String to be printed to the lcd.
 */
void HD44780_put_str(const HD44780 *lcd, const char *str);

#endif /* __HD44780_H__ */
