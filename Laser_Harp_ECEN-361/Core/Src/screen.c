#include "screen.h"

uint8_t backlight_state = 1; // initialize backlight_state

void lcd_write_nibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = nibble << D4_BIT;
    data |= rs << RS_BIT;
    data |= backlight_state << BL_BIT;

    data |= 1 << EN_BIT;
    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR << 1, &data, 1, 100);
    HAL_Delay(1);
    data &= ~(1 << EN_BIT);
    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR << 1, &data, 1, 100);
}

void lcd_send_cmd(uint8_t cmd)
{
    uint8_t upper_nibble = cmd >> 4;
    uint8_t lower_nibble = cmd & 0x0F;
    lcd_write_nibble(upper_nibble, 0);
    lcd_write_nibble(lower_nibble, 0);
    if (cmd == 0x01 || cmd == 0x02)
    {
        HAL_Delay(2);
    }
}

void lcd_send_data(uint8_t data)
{
    uint8_t upper_nibble = data >> 4;
    uint8_t lower_nibble = data & 0x0F;
    lcd_write_nibble(upper_nibble, 1);
    lcd_write_nibble(lower_nibble, 1);
}

void lcd_init()
{
    HAL_Delay(50);
    lcd_write_nibble(0x03, 0);
    HAL_Delay(5);
    lcd_write_nibble(0x03, 0);
    HAL_Delay(1);
    lcd_write_nibble(0x03, 0);
    HAL_Delay(1);
    lcd_write_nibble(0x02, 0);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x0C);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_write_string(char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t column)
{
    uint8_t address;
    switch (row)
    {
        case 0:
            address = 0x00;
            break;
        case 1:
            address = 0x40;
            break;
        default:
            address = 0x00;
    }
    address += column;
    lcd_send_cmd(0x80 | address);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
}

void lcd_backlight(uint8_t state)
{
    if (state)
    {
        backlight_state = 1;
    }
    else
    {
        backlight_state = 0;
    }
}
