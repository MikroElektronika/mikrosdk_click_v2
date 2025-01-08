
---
# Joystick 3 Click

> [Joystick 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5378) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5378&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the joystick 3 Click board by reading
and displaying the raw ADC for X and Y axis, as well as the joystick angle and position
calculated from those ADC readings.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Joystick3

### Example Key Functions

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
