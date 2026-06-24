
---
# Hall Switch 6 Click

> [Hall Switch 6 Click](https://www.mikroe.com/?pid_product=MIKROE-7005) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7005&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Apr 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Hall Switch 6 Click board by
detecting which magnetic pole is present near the TMAG5230D5D sensor
and logging the result via UART. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallSwitch6

### Example Key Functions

- `hallswitch6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void hallswitch6_cfg_setup ( hallswitch6_cfg_t *cfg );
```

- `hallswitch6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t hallswitch6_init ( hallswitch6_t *ctx, hallswitch6_cfg_t *cfg );
```

- `hallswitch6_get_out1_pin` This function reads the state of the OUT1 pin, which goes LOW when positive flux exceeds the BOP threshold.
```c
uint8_t hallswitch6_get_out1_pin ( hallswitch6_t *ctx );
```

- `hallswitch6_get_out2_pin` This function reads the state of the OUT2 pin, which goes LOW when negative flux exceeds the BOP threshold.
```c
uint8_t hallswitch6_get_out2_pin ( hallswitch6_t *ctx );
```

- `hallswitch6_get_pole` This function reads both output pins and returns which magnetic pole is currently detected, if any.
```c
uint8_t hallswitch6_get_pole ( hallswitch6_t *ctx );
```

### Application Init

> Initializes the logger and the Hall Switch 6 Click driver.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallswitch6_cfg_t hallswitch6_cfg;  /**< Click config object. */

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
    hallswitch6_cfg_setup( &hallswitch6_cfg );
    HALLSWITCH6_MAP_MIKROBUS( hallswitch6_cfg, MIKROBUS_POSITION_HALLSWITCH6 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hallswitch6_init( &hallswitch6, &hallswitch6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
     
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads both sensor outputs every 100 ms and logs the detected magnetic
pole state. A message is logged only when the state changes.

```c
void application_task ( void ) 
{
    static uint8_t pole_old = HALLSWITCH6_POLE_UNINIT;
    uint8_t pole = hallswitch6_get_pole( &hallswitch6 );

    if ( pole != pole_old )
    {
        pole_old = pole;
        switch ( pole )
        {
            case HALLSWITCH6_SOUTH_POLE:
            {
                log_printf( &logger, " Magnetic pole: SOUTH\r\n" );
                break;
            }
            case HALLSWITCH6_NORTH_POLE:
            {
                log_printf( &logger, " Magnetic pole: NORTH\r\n" );
                break;
            }
            case HALLSWITCH6_NO_MAGNET:
            {
                log_printf( &logger, " No magnet detected\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, " Unknown state\r\n" );
                break;
            }
        }
    }

    Delay_ms ( 100 );
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
