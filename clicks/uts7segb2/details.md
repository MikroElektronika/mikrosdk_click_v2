
---
# UT-S 7-SEG B 2 Click

> UT-S 7-SEG B 2 Click is a compact add-on board that presents an easy solution for adding a numeric or hexadecimal display to your application. This board features the TLC5947, a constant-current sink LED driver from Texas Instruments, alongside six ultra-thin blue single-digit numeric displays, the JSS-3011BUB-21. The displays are small in size (0.39 inches in height) and can display letters, numbers, and symbols in a highly readable form. The host MCU can control the light intensity of the blue segments of the display.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uts7segb2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ut-s-7-seg-b-2-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Nov 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the UT-S 7-SEG B 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UT-S 7-SEG B 2 Click driver.

#### Standard key functions :

- `uts7segb2_cfg_setup` Config Object Initialization function.
```c
void uts7segb2_cfg_setup ( uts7segb2_cfg_t *cfg );
```

- `uts7segb2_init` Initialization function.
```c
err_t uts7segb2_init ( uts7segb2_t *ctx, uts7segb2_cfg_t *cfg );
```

- `uts7segb2_default_cfg` Click Default Configuration function.
```c
err_t uts7segb2_default_cfg ( uts7segb2_t *ctx );
```

#### Example key functions :

- `uts7segb2_display_number` This function displays the desired number and brightness on the selected segments.
```c
err_t uts7segb2_display_number ( uts7segb2_t *ctx, uts7segb2_number_cfg_t number );
```

- `uts7segb2_display_character` This function displays the desired characters and brightness on the selected segments.
```c
err_t uts7segb2_display_character ( uts7segb2_t *ctx, uts7segb2_character_cfg_t ascii_char );
```

- `uts7segb2_set_led_output` This function sets the LED driver output.
```c
err_t uts7segb2_set_led_output ( uts7segb2_t *ctx, uts7segb2_seg_sel_t seg_sel, 
                                 uint32_t seg_bit_mask, uint16_t brightness );
```

## Example Description

> This example demonstrates the use of the UT-S 7-SEG B 2 Click board
> by writing and displaying the desired numbers on the screen.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uts7segb2_cfg_t uts7segb2_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    uts7segb2_cfg_setup( &uts7segb2_cfg );
    UTS7SEGB2_MAP_MIKROBUS( uts7segb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uts7segb2_init( &uts7segb2, &uts7segb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UTS7SEGB2_ERROR == uts7segb2_default_cfg ( &uts7segb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    number.brightness_top = UTS7SEGB2_BRIGHTNESS_DEFAULT;
    number.brightness_bottom = UTS7SEGB2_BRIGHTNESS_DEFAULT;
    number.base = UTS7SEGB2_BASE_NUM_SYS_HEXADECIMAL;
    number.dot_bit_mask = UTS7SEGB2_TOP_SEG_NO_DOT | UTS7SEGB2_BOTTOM_SEG_NO_DOT;
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application draws numbers, in hexadecimal format, 
> from 0h to FFFh on the top segment group and from FFFh to 0h on the bottom segment group.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    for ( uint16_t num_cnt = 0; num_cnt <= UTS7SEGB2_HEXADECIMAL_NUM_MAX; num_cnt++ )
    {
        number.num_top = num_cnt;
        number.num_bottom = UTS7SEGB2_HEXADECIMAL_NUM_MAX - num_cnt;
        if ( UTS7SEGB2_OK == uts7segb2_display_number( &uts7segb2, number ) )
        {
            log_printf( &logger, " %.3X\r\n", number.num_top );
            log_printf( &logger, " %.3X\r\n\n", number.num_bottom );
            Delay_ms ( 100 );
        }
    }
    log_printf( &logger, " --------------\r\n\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UTS7SEGB2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
