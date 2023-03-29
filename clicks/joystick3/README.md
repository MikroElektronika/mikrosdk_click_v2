\mainpage Main Page

---
# Joystick 3 click

> Joystick 3 Click is a compact add-on board that can fulfill your directional analog input needs. This board features 2765, a high-quality mini 2-axis analog output thumbstick from Adafruit Industries. This small joystick is a 'self-centering' analog-type with a black rocker cap similar to the PSP joysticks. It comprises two 10kΩ potentiometers, one for up/down and another for left/right direction. Knowing that this joystick represents an analog type, it connects with mikroBUS™ through the SPI interface through the MCP3204 12-bit A/D converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/joystick3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/joystick-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Joystick 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Joystick 3 Click driver.

#### Standard key functions :

- `joystick3_cfg_setup` Config Object Initialization function.
```c
void joystick3_cfg_setup ( joystick3_cfg_t *cfg );
```

- `joystick3_init` Initialization function.
```c
err_t joystick3_init ( joystick3_t *ctx, joystick3_cfg_t *cfg );
```

- `joystick3_default_cfg` Click Default Configuration function.
```c
err_t joystick3_default_cfg ( joystick3_t *ctx );
```

#### Example key functions :

- `joystick3_read_raw_adc` This function reads the raw ADC for X and Y axis by using SPI serial interface.
```c
err_t joystick3_read_raw_adc ( joystick3_t *ctx, uint16_t *raw_x, uint16_t *raw_y );
```

- `joystick3_get_angle` This function calculates and returns joystick angle in degrees from raw ADC values for X and Y axis.
```c
float joystick3_get_angle ( uint16_t raw_x, uint16_t raw_y );
```

- `joystick3_get_position` This function calculates and returns joystick position flag from raw ADC values for X and Y axis.
```c
uint8_t joystick3_get_position ( uint16_t raw_x, uint16_t raw_y );
```

## Example Description

> This example demonstrates the use of the joystick 3 click board by reading
and displaying the raw ADC for X and Y axis, as well as the joystick angle and position
calculated from those ADC readings.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    joystick3_cfg_t joystick3_cfg;  /**< Click config object. */

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
    joystick3_cfg_setup( &joystick3_cfg );
    JOYSTICK3_MAP_MIKROBUS( joystick3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == joystick3_init( &joystick3, &joystick3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the raw ADC measurements for X and Y axis, and calculates the joystick angle and position
from those readings. The results will be displayed on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    uint16_t raw_x, raw_y;
    if ( JOYSTICK3_OK == joystick3_read_raw_adc ( &joystick3, &raw_x, &raw_y ) )
    {
        log_printf ( &logger, " RAW X: %u\r\n RAW Y: %u\r\n", raw_x, raw_y );
        log_printf ( &logger, " Joystick angle: %.1f degrees\r\n", joystick3_get_angle ( raw_x, raw_y ) );
        log_printf ( &logger, " Joystick position: " );
        switch ( joystick3_get_position ( raw_x, raw_y ) )
        {
            case JOYSTICK3_POSITION_NEUTRAL:
            {
                log_printf ( &logger, "NEUTRAL" );
                break;
            }
            case JOYSTICK3_POSITION_UP:
            {
                log_printf ( &logger, "UP" );
                break;
            }
            case JOYSTICK3_POSITION_UPPER_RIGHT:
            {
                log_printf ( &logger, "UPPER-RIGHT" );
                break;
            }
            case JOYSTICK3_POSITION_RIGHT:
            {
                log_printf ( &logger, "RIGHT" );
                break;
            }
            case JOYSTICK3_POSITION_LOWER_RIGHT:
            {
                log_printf ( &logger, "LOWER-RIGHT" );
                break;
            }
            case JOYSTICK3_POSITION_DOWN:
            {
                log_printf ( &logger, "DOWN" );
                break;
            }
            case JOYSTICK3_POSITION_LOWER_LEFT:
            {
                log_printf ( &logger, "LOWER-LEFT" );
                break;
            }
            case JOYSTICK3_POSITION_LEFT:
            {
                log_printf ( &logger, "LEFT" );
                break;
            }
            case JOYSTICK3_POSITION_UPPER_LEFT:
            {
                log_printf ( &logger, "UPPER-LEFT" );
                break;
            }
            default:
            {
                log_printf ( &logger, "UNKNOWN" );
                break;
            }
        }
        log_printf ( &logger, "\r\n\n" );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Joystick3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
