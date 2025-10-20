
---
# Thumbstick 2 Click

> [Thumbstick 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6655) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6655&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Thumbstick 2 Click board which 
features a 2-axis joystick with push button and vibration feedback. 
The joystick's angle and position are calculated based on raw ADC values, 
while the push button status controls the vibration motor through PWM output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thumbstick2

### Example Key Functions

- `thumbstick2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void thumbstick2_cfg_setup ( thumbstick2_cfg_t *cfg );
```

- `thumbstick2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t thumbstick2_init ( thumbstick2_t *ctx, thumbstick2_cfg_t *cfg );
```

- `thumbstick2_read_raw_adc` This function reads the raw ADC for X and Y axis by using SPI serial interface.
```c
err_t thumbstick2_read_raw_adc ( thumbstick2_t *ctx, uint16_t *raw_x, uint16_t *raw_y );
```

- `thumbstick2_get_angle` This function calculates and returns joystick angle in degrees from raw ADC values for X and Y axis.
```c
float thumbstick2_get_angle ( uint16_t raw_x, uint16_t raw_y );
```

- `thumbstick2_get_position` This function calculates and returns joystick position flag from raw ADC values for X and Y axis.
```c
uint8_t thumbstick2_get_position ( uint16_t raw_x, uint16_t raw_y );
```

### Application Init

> Initializes the logger and the Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thumbstick2_cfg_t thumbstick2_cfg;  /**< Click config object. */

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
    thumbstick2_cfg_setup( &thumbstick2_cfg );
    THUMBSTICK2_MAP_MIKROBUS( thumbstick2_cfg, MIKROBUS_1 );
    if ( THUMBSTICK2_OK != thumbstick2_init( &thumbstick2, &thumbstick2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the raw ADC values from the joystick axes, calculates the 
joystick's position and angle, and logs the results. It also checks the state 
of the joystick push button and activates vibration feedback accordingly.

```c
void application_task ( void )
{
    float angle = 0;
    uint16_t raw_x = 0;
    uint16_t raw_y = 0;
    uint8_t position = 0;
    if ( THUMBSTICK2_OK == thumbstick2_read_raw_adc ( &thumbstick2, &raw_x, &raw_y ) )
    {
        angle = thumbstick2_get_angle ( raw_x, raw_y );
        position = thumbstick2_get_position ( raw_x, raw_y );
        log_printf ( &logger, " RAW X: %u\r\n RAW Y: %u\r\n", raw_x, raw_y );
        log_printf ( &logger, " Joystick angle: %.1f degrees\r\n", angle );
        log_printf ( &logger, " Joystick position: " );
        switch ( position )
        {
            case THUMBSTICK2_POSITION_NEUTRAL:
            {
                log_printf ( &logger, "NEUTRAL" );
                break;
            }
            case THUMBSTICK2_POSITION_UP:
            {
                log_printf ( &logger, "UP" );
                break;
            }
            case THUMBSTICK2_POSITION_UPPER_LEFT:
            {
                log_printf ( &logger, "UPPER-LEFT" );
                break;
            }
            case THUMBSTICK2_POSITION_LEFT:
            {
                log_printf ( &logger, "LEFT" );
                break;
            }
            case THUMBSTICK2_POSITION_LOWER_LEFT:
            {
                log_printf ( &logger, "LOWER-LEFT" );
                break;
            }
            case THUMBSTICK2_POSITION_DOWN:
            {
                log_printf ( &logger, "DOWN" );
                break;
            }
            case THUMBSTICK2_POSITION_LOWER_RIGHT:
            {
                log_printf ( &logger, "LOWER-RIGHT" );
                break;
            }
            case THUMBSTICK2_POSITION_RIGHT:
            {
                log_printf ( &logger, "RIGHT" );
                break;
            }
            case THUMBSTICK2_POSITION_UPPER_RIGHT:
            {
                log_printf ( &logger, "UPPER-RIGHT" );
                break;
            }
            default:
            {
                log_printf ( &logger, "UNKNOWN" );
                break;
            }
        }
        log_printf ( &logger, "\r\n" );
        if ( thumbstick2_get_sw_pin ( &thumbstick2 ) )
        {
            log_printf ( &logger, " Button: Idle\r\n" );
            log_printf ( &logger, " Vibro: Idle\r\n\n" );
            thumbstick2_set_duty_cycle ( &thumbstick2, THUMBSTICK2_PWM_MIN_DUTY );
        }
        else
        {
            log_printf ( &logger, " Button: Active\r\n" );
            log_printf ( &logger, " Vibro: Active\r\n\n" );
            thumbstick2_set_duty_cycle ( &thumbstick2, THUMBSTICK2_PWM_MAX_DUTY );
        }
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
