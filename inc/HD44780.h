#ifndef __HD44780_H__
#define __HD44780_H__

#include <stdbool.h>
#include <stm32f1xx_hal.h>

/*
 * Constants
 */

#define HD44780_FIRST_LINE_ADDRESS 0x00
#define HD44780_SECOND_LINE_ADDRESS 0x40

#define HD44780_LINE_LENGTH_1_LINE 0x4F
#define HD44780_LINE_LENGTH_2_LINE 0x27

#define HD44780_TAB_SIZE 4

/*
 * Commands
 */

#define HD44780_CMD_CLEAR_DISPLAY 0X01

#define HD44780_CMD_RETURN_HOME 0X02

#define HD44780_CMD_ENTRY_MODE_SET 0x04
#define HD44780_FLG_DIR_LTR 0x00
#define HD44780_FLG_DIR_RTL 0x02
#define HD44780_FLG_DISPLAY_NOSHIFT 0x00
#define HD44780_FLG_DISPLAY_SHIFT 0x01

#define HD44780_CMD_DISPLAY_CONTROL 0x08
#define HD44780_FLG_DISPLAY_OFF 0x00
#define HD44780_FLG_DISPLAY_ON 0x04
#define HD44780_FLG_CURSOR_OFF 0x00
#define HD44780_FLG_CURSOR_ON 0x02
#define HD44780_FLG_BLINK_OFF 0x00
#define HD44780_FLG_BLINK_ON 0x01

#define HD44780_CMD_CURSOR_DISPLAY_SHIFT 0x10
#define HD44780_FLG_SHIFT_CURSOR 0x00
#define HD44780_FLG_SHIFT_DISPLAY 0x08
#define HD44780_FLG_SHIFT_LTR 0x00
#define HD44780_FLG_SHIFT_RTL 0x04

#define HD44780_CMD_FUNCTION_SET 0x20
#define HD44780_FLG_DATA_LEN_4BIT 0x00
#define HD44780_FLG_DATA_LEN_8BIT 0x10
#define HD44780_FLG_1_LINE 0x00
#define HD44780_FLG_2_LINE 0x08
#define HD44780_FLG_FONT_5X8 0x00
#define HD44780_FLG_FONT_5X10 0x04

#define HD44780_CMD_SET_CGRAM_ADDRESS 0x40

#define HD44780_CMD_SET_DDRAM_ADDRESS 0x80

#define HD44780_CMD_READ_BUSYFLAG_AND_ADDRESS 0X07

/*
 * Data structures
 */

typedef struct
{
    /*
     * GPIO ports of the mcu pins connected to the controller's data lines.
     */
    GPIO_TypeDef *rs_gpio, *rw_gpio, *en_gpio, *d0_gpio, *d1_gpio, *d2_gpio, *d3_gpio, *d4_gpio, *d5_gpio, *d6_gpio,
        *d7_gpio;
    /*
     * Pin numbers of the mcu pins connected to the controller's data lines.
     */
    uint16_t rs_pin, rw_pin, en_pin, d0_pin, d1_pin, d2_pin, d3_pin, d4_pin, d5_pin, d6_pin, d7_pin;
    /*
     *
     * Number of physical data lines connected to the controller.
     * true -> 8 bit interface (DB7-DB0) | false -> 4 bit interface (DB7-DB4)
     */
    bool interface_8_bit;
    /*
     * Number of displayed lines.
     * true -> 2 lines | false -> 1 line
     */
    bool two_lines;
    /*
     * Character font. Note that the 5x10 dots font only supports 1 line operation (two_lines = false).
     * true -> 5x10 dots | false -> 5x8 dots
     */
    bool font_5x10;
} HD44780;

typedef struct
{
    /*
     * Enable the display.
     * Data can still be written with the lcd unpowered and displayed at a later moment.
     * true -> enabled | false -> disabled
     */
    bool enable_display;
    /*
     * Make the cursor visible.
     * The cursor is displayed using 5 dots in the 8th line for 5×8 dots font and in the 11th line for 5×10 dots font.
     * true -> enabled | false -> disabled
     */
    bool enable_cursor;
    /*
     * Make the character indicated by the cursor blink.
     * The blinking is displayed as switching between all blank dots and displayed character.
     * true -> enabled | false -> disabled
     */
    bool enable_blink;
    /*
     * Shift the display instead of the cursor when data is entered.
     * true -> shift display | false -> shift cursor
     */
    bool shift_display;
    /*
     * Shift the display/cursor (depending on the shift_display parameter) in right to left direction.
     * true -> right to left | false -> left to right
     */
    bool shift_rtl;
} HD44780_Config;

/*
 * Functions
 */

/*
 * Initialize the necessary hardware peripherals, then configure the display itself.
 */
void HD44780_init(HD44780 *lcd, HD44780_Config *config);

/*
 * Update the configuration of the controller.
 */
void HD44780_update_config(HD44780 *lcd, HD44780_Config *config);

/*
 * Clear the display and move the cursor to position 0 of the first line.
 */
void HD44780_clear(HD44780 *lcd);

/*
 * Move the cursor to the desired position.
 */
void HD44780_goto(HD44780 *lcd, uint8_t row, uint8_t column);

/*
 * Create a user defined character to display in the LCD.
 * The controller memory can store up to 8 5x8 symbols, and up to 4 5x10 symbols.
 * Please note that 5x10 characters needs 2 CGRAM slots,
 * so after defining a 5x10 symbol at address n, next symbol should be defined at address n+2.
 *
 * address: ASCII code of the new symbol, must be in the range from 0 to 7 inclusive.
 *
 * font_5x10: Wheteher the new symbol will be a 5x10 character.
 *
 * symbol: Array of 5 bit values where each bit will determine whether the corresponding pixel is lit up in the row.
 */
void HD44780_create_symbol(HD44780 *lcd, uint8_t address, bool font_5x10, uint8_t symbol[]);

/*
 * Write a single character to the lcd, then advance the cursor.
 * If the character is '\n' the cursor will advance to the next line, wrapping around from last to first.
 * If the character is '\t' 4 spaces will be written.
 */
void HD44780_put_char(HD44780 *lcd, uint8_t chr);

/*
 * Write a string to the lcd, then advance the cursor.
 * Note that the string has be null terminated.
 */
void HD44780_put_str(HD44780 *lcd, char *str);

#endif /* __HD44780_H__ */
