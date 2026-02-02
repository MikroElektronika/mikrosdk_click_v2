
---
# Gesture Click

> [Gesture Click](https://www.mikroe.com/?pid_product=MIKROE-6517) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6517&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the usage of the Gesture Click board for detecting hand gestures.
The board is initialized, and the application continuously monitors and logs detected gestures.
Supported gestures include: UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD, CLOCKWISE, COUNTER-CLOCKWISE, and WAVE.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gesture

### Example Key Functions

- `gesture_cfg_setup` Config Object Initialization function.
```c
void gesture_cfg_setup ( gesture_cfg_t *cfg );
```

- `gesture_init` Initialization function.
```c
err_t gesture_init ( gesture_t *ctx, gesture_cfg_t *cfg );
```

- `gesture_default_cfg` Click Default Configuration function.
```c
err_t gesture_default_cfg ( gesture_t *ctx );
```

- `gesture_get_detected_gesture` This function detects a gesture based on the interrupt flags and assigns the corresponding gesture code.
```c
err_t gesture_get_detected_gesture ( gesture_t *ctx, uint8_t *gesture, uint32_t timeout );
```

### Application Init

> Initializes the Gesture Click board by configuring the logger, setting up the board, and applying the default configuration to enable gesture detection.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gesture_cfg_t gesture_cfg;  /**< Click config object. */

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
    gesture_cfg_setup( &gesture_cfg );
    GESTURE_MAP_MIKROBUS( gesture_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == gesture_init( &gesture, &gesture_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GESTURE_ERROR == gesture_default_cfg ( &gesture ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously checks for gestures within a timeout period and logs the detected gesture to USB UART.

```c
void application_task ( void )
{
    uint8_t detected_gesture = GESTURE_UNKNOWN;
    err_t error_flag = gesture_get_detected_gesture ( &gesture, &detected_gesture, GESTURE_TIMEOUT_5S );
    if ( GESTURE_OK == error_flag )
    {
        log_printf ( &logger, "Gesture - " );
        switch ( detected_gesture )
        {
            case GESTURE_UP:
            {
                log_printf ( &logger, "UP" );
                break;
            }
            case GESTURE_DOWN:
            {
                log_printf ( &logger, "DOWN" );
                break;
            }
            case GESTURE_LEFT:
            {
                log_printf ( &logger, "LEFT" );
                break;
            }
            case GESTURE_RIGHT:
            {
                log_printf ( &logger, "RIGHT" );
                break;
            }
            case GESTURE_FORWARD:
            {
                log_printf ( &logger, "FORWARD" );
                break;
            }
            case GESTURE_BACKWARD:
            {
                log_printf ( &logger, "BACKWARD" );
                break;
            }
            case GESTURE_CLOCKWISE:
            {
                log_printf ( &logger, "CLOCKWISE" );
                break;
            }
            case GESTURE_COUNTER_CLOCKWISE:
            {
                log_printf ( &logger, "COUNTER-CLOCKWISE" );
                break;
            }
            case GESTURE_WAVE:
            {
                log_printf ( &logger, "WAVE" );
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
    else if ( GESTURE_ERROR_TIMEOUT == error_flag )
    {
        log_printf ( &logger, "TIMEOUT - no gesture detected!\r\n\n" );
    }
    else
    {
        log_printf ( &logger, "ERROR - no communication!\r\n\n" );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The Click board communication protocol wake up is issued at the first communication check
after power-up where the IC responds with NACK, which blocks the I2C bus on some MCUs. 
Re-running the program (without power cycling the Click board power supply) should unlock
the communication and solve this issue.

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
