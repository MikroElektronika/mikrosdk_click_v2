
---
# Boost 8 Click

> [Boost 8 Click](https://www.mikroe.com/?pid_product=MIKROE-5468) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5468&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2022.
- **Type**          : GPIO type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Boost 8 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost8

### Example Key Functions

- `boost8_cfg_setup` Config Object Initialization function.
```c
void boost8_cfg_setup ( boost8_cfg_t *cfg );
```

- `boost8_init` Initialization function.
```c
err_t boost8_init ( boost8_t *ctx, boost8_cfg_t *cfg );
```

- `boost8_default_cfg` Click Default Configuration function.
```c
void boost8_default_cfg ( boost8_t *ctx );
```

- `boost8_enable_positive_voltage` Enable positive voltage output function.
```c
void boost8_enable_positive_voltage( boost8_t *ctx );
```

- `boost8_disable_positive_voltage` Disable positive voltage output function.
```c
void boost8_disable_positive_voltage( boost8_t *ctx );
```

- `boost8_enable_negative_voltage` Enable negative voltage output function.
```c
void boost8_enable_negative_voltage( boost8_t *ctx );
```

### Application Init

> Initializes EN+ and EN- pins, UART log, and performs default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost8_cfg_t boost8_cfg;  /**< Click config object. */

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
    boost8_cfg_setup( &boost8_cfg );
    BOOST8_MAP_MIKROBUS( boost8_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == boost8_init( &boost8, &boost8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    boost8_default_cfg ( &boost8 );
    
    log_info( &logger, " Application Task " );
    boost8_list_of_commands();
}
```

### Application Task

> Waits for user input in order to determine what output should be enabled.

```c
void application_task ( void ) 
{
    char inx;
    
    // Waiting for the user input and performing actions based on a selected command.
    if ( log_read( &logger, &inx, 1 ) != BOOST8_ERROR )
    {
        switch(inx)
        {
            case '1' :
            {
                log_printf( &logger, "Turning on positive output \r\n" );
                boost8_enable_positive_voltage( &boost8 );
                break;
            }
            case '2' :
            {
                log_printf( &logger, "Turning off positive output \r\n" );
                boost8_disable_positive_voltage( &boost8 );
                break;
            }
            case '3' :
            {
                log_printf( &logger, "Turning on negative output \r\n" );
                boost8_enable_negative_voltage( &boost8 );
                break;
            }
            case '4':
            {
                log_printf( &logger, "Turning off negative output \r\n" );
                boost8_disable_negative_voltage( &boost8 );
                break;
            }
            case '5' :
            {
                log_printf( &logger, "Turning on both outputs \r\n" );
                boost8_enable_both_outputs( &boost8 );
                break;
            }
            case '6' :
            {
                log_printf( &logger, "Turning off both outputs \r\n" );
                boost8_disable_both_outputs( &boost8 );
                break;
            }
            default:
            {
                log_printf( &logger, "> Invalid command \r\n" );
                boost8_list_of_commands();
                break;
            }
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
