
---
# Joystick 4 Click

> [Joystick 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6279) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6279&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Joystick 4 Click board by reading and displaying the joystick position.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Joystick4

### Example Key Functions

- `joystick4_cfg_setup` Config Object Initialization function.
```c
void joystick4_cfg_setup ( joystick4_cfg_t *cfg );
```

- `joystick4_init` Initialization function.
```c
err_t joystick4_init ( joystick4_t *ctx, joystick4_cfg_t *cfg );
```

- `joystick4_default_cfg` Click Default Configuration function.
```c
err_t joystick4_default_cfg ( joystick4_t *ctx );
```

- `joystick4_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t joystick4_get_int_pin ( joystick4_t *ctx );
```

- `joystick4_get_pins` This function reads all input pins logic state.
```c
err_t joystick4_get_pins ( joystick4_t *ctx, uint8_t *pin_mask );
```

- `joystick4_get_position` This function returns the joystick position flag extracted from the input pins state mask.
```c
uint8_t joystick4_get_position ( uint8_t pin_mask );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    joystick4_cfg_t joystick4_cfg;  /**< Click config object. */

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
    joystick4_cfg_setup( &joystick4_cfg );
    JOYSTICK4_MAP_MIKROBUS( joystick4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == joystick4_init( &joystick4, &joystick4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( JOYSTICK4_ERROR == joystick4_default_cfg ( &joystick4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    if ( JOYSTICK4_PIN_STATE_HIGH == joystick4_get_int_pin ( &joystick4 ) )
    {
        log_printf ( &logger, " Joystick position: IDLE\r\n\n" );
    }
}
```

### Application Task

> Waits for the input change interrupt, reads the input pins mask, extracts the joystick position from those readings, and displays it on the USB UART.

```c
void application_task ( void )
{
    uint8_t pin_mask = 0;
    if ( JOYSTICK4_PIN_STATE_LOW == joystick4_get_int_pin ( &joystick4 ) )
    {
        if ( JOYSTICK4_OK == joystick4_get_pins ( &joystick4, &pin_mask ) )
        {
            log_printf ( &logger, " Joystick position: " );
            switch ( joystick4_get_position ( pin_mask ) )
            {
                case JOYSTICK4_POSITION_IDLE:
                {
                    log_printf ( &logger, "IDLE" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER:
                {
                    log_printf ( &logger, "CENTER" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_UP:
                {
                    log_printf ( &logger, "CENTER-UP" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_RIGHT:
                {
                    log_printf ( &logger, "CENTER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_DOWN:
                {
                    log_printf ( &logger, "CENTER-DOWN" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_LEFT:
                {
                    log_printf ( &logger, "CENTER-LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_UP:
                {
                    log_printf ( &logger, "UP" );
                    break;
                }
                case JOYSTICK4_POSITION_UPPER_RIGHT:
                {
                    log_printf ( &logger, "UPPER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_RIGHT:
                {
                    log_printf ( &logger, "RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_LOWER_RIGHT:
                {
                    log_printf ( &logger, "LOWER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_DOWN:
                {
                    log_printf ( &logger, "DOWN" );
                    break;
                }
                case JOYSTICK4_POSITION_LOWER_LEFT:
                {
                    log_printf ( &logger, "LOWER-LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_LEFT:
                {
                    log_printf ( &logger, "LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_UPPER_LEFT:
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
        }
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
