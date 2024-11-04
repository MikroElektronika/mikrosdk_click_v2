\mainpage Main Page

---
# UT-L 7-SEG B Click

> UT-L 7-SEG B Click is a compact add-on board that presents an easy solution for adding a numeric or hexadecimal display to your application. This board features two blue JSS-5611BUB-21s, ultra-thin single-digit numeric displays from Ningbo Junsheng Electronics. The displays are medium (0.56 inches in height) and can display letters, numbers, and symbols in a highly readable form. The host MCU can control the light intensity of the red segments of the display.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/utl7segb_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ut-l-7-seg-b-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the UT-L 7-SEG B Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UT-L 7-SEG B Click driver.

#### Standard key functions :

- `utl7segb_cfg_setup` Config Object Initialization function.
```c
void utl7segb_cfg_setup ( utl7segb_cfg_t *cfg );
```

- `utl7segb_init` Initialization function.
```c
err_t utl7segb_init ( utl7segb_t *ctx, utl7segb_cfg_t *cfg );
```

- `utl7segb_default_cfg` Click Default Configuration function.
```c
err_t utl7segb_default_cfg ( utl7segb_t *ctx );
```

#### Example key functions :

- `utl7segb_display_number` UT-L 7-SEG B display number function.
```c
err_t utl7segb_display_number ( utl7segb_t *ctx, uint8_t base, uint8_t num, uint8_t dot_pos );
```

- `utl7segb_enable`  UT-L 7-SEG B enable function.
```c
void utl7segb_enable ( utl7segb_t *ctx );
```

## Example Description

> This example demonstrates the use of the UT-L 7-SEG B Click board™ 
> by writing and displaying the desired numbers on the screen.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    utl7segb_cfg_t utl7segb_cfg;  /**< Click config object. */

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
    utl7segb_cfg_setup( &utl7segb_cfg );
    UTL7SEGB_MAP_MIKROBUS( utl7segb_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == utl7segb_init( &utl7segb, &utl7segb_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UTL7SEGB_ERROR == utl7segb_default_cfg ( &utl7segb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application draws numbers, in hexadecimal format, from 0h to FFh on the display.

```c
void application_task ( void )
{
    for ( uint8_t hex_num = 0x00; hex_num < 0xFF; hex_num++ ) 
    {
        if ( UTL7SEGB_OK == utl7segb_display_number( &utl7segb, 
                                                     UTL7SEGB_BASE_NUM_SYS_HEXADECIMAL, 
                                                     hex_num, 
                                                     UTL7SEGB_NO_DOT ) )
        {
            log_printf( &logger, " --- %.2X ---\r\n", ( uint16_t ) hex_num );
            Delay_ms ( 500 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UTL7SEGB

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
