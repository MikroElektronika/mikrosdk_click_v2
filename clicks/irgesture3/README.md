
---
# IR Gesture 3 Click

> [IR Gesture 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5742) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5742&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of IR Gesture 3 Click board by processing the incoming gestures and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGesture3

### Example Key Functions

- `irgesture3_cfg_setup` Config Object Initialization function.
```c
void irgesture3_cfg_setup ( irgesture3_cfg_t *cfg );
```

- `irgesture3_init` Initialization function.
```c
err_t irgesture3_init ( irgesture3_t *ctx, irgesture3_cfg_t *cfg );
```

- `irgesture3_default_cfg` Click Default Configuration function.
```c
err_t irgesture3_default_cfg ( irgesture3_t *ctx );
```

- `irgesture3_set_mode` This function sets the device operating mode.
```c
err_t irgesture3_set_mode ( irgesture3_t *ctx, uint8_t mode );
```

- `irgesture3_set_adc_fsample` This function sets the sample frequency of the device.
```c
err_t irgesture3_set_adc_fsample ( irgesture3_t *ctx, uint16_t freq_hz );
```

- `irgesture3_get_gesture` This function waits up to IRGESTURE3_MAX_NUM_SAMPLES for an object to be detected and then calculates its gesture.
```c
err_t irgesture3_get_gesture ( irgesture3_t *ctx, uint8_t *gesture );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgesture3_cfg_t irgesture3_cfg;  /**< Click config object. */

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
    irgesture3_cfg_setup( &irgesture3_cfg );
    IRGESTURE3_MAP_MIKROBUS( irgesture3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgesture3_init( &irgesture3, &irgesture3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGESTURE3_ERROR == irgesture3_default_cfg ( &irgesture3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and processes all the incoming gestures and displays them on the USB UART.

```c
void application_task ( void )
{
    uint8_t gesture = 0;
    if ( IRGESTURE3_OK == irgesture3_get_gesture ( &irgesture3, &gesture ) )
    {
        log_printf( &logger, "\r\n Gesture: " );
        switch ( gesture )
        {
            case IRGESTURE3_GESTURE_CLICK:
            {
                log_printf( &logger, "CLICK\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_UP:
            {
                log_printf( &logger, "SWIPE UP\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_DOWN:
            {
                log_printf( &logger, "SWIPE DOWN\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_LEFT:
            {
                log_printf( &logger, "SWIPE LEFT\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_RIGHT:
            {
                log_printf( &logger, "SWIPE RIGHT\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, "UNKNOWN\r\n" );
                break;
            }
        }
    }
    else
    {
        log_printf( &logger, "\r\n No gesture detected!\r\n" );
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
