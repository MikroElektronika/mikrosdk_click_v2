
---
# Hall Switch 2 Click

> [Hall Switch 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4788) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4788&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Hall Switch 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallSwitch2

### Example Key Functions

- `hallswitch2_cfg_setup` Config Object Initialization function.
```c
void hallswitch2_cfg_setup ( hallswitch2_cfg_t *cfg );
```

- `hallswitch2_init` Initialization function.
```c
err_t hallswitch2_init ( hallswitch2_t *ctx, hallswitch2_cfg_t *cfg );
```

- `hallswitch2_check_state` This function checks the S and N pin states, which indicates a magnetic field poles.
```c
uint8_t hallswitch2_check_state ( hallswitch2_t *ctx );
```

### Application Init

> Initializes the driver and logger and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    hallswitch2_cfg_t hallswitch2_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    hallswitch2_cfg_setup( &hallswitch2_cfg );
    HALLSWITCH2_MAP_MIKROBUS( hallswitch2_cfg, MIKROBUS_1 );
    if ( hallswitch2_init( &hallswitch2, &hallswitch2_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Displays the corresponding message on the USB UART based on the switches state, i.e. based on the magnetic field presence.

```c
void application_task ( void )
{
    switch ( hallswitch2_check_state( &hallswitch2 ) )
    {
        case HALLSWITCH2_NO_MAGNET_DETECTED:
        {
            if ( HALLSWITCH2_NO_MAGNET_DETECTED != print_state )
            {
                log_printf( &logger, " No magnet detected\r\n" );
                log_printf( &logger, " Switches - disabled\r\n\r\n" );
                print_state = HALLSWITCH2_NO_MAGNET_DETECTED;
            }
            break;
        }
        case HALLSWITCH2_S_POLE_DETECTED:
        {
            if ( HALLSWITCH2_S_POLE_DETECTED != print_state )
            {
                log_printf( &logger, " South pole detected\r\n" );
                log_printf( &logger, " Switch 1 - enabled\r\n\r\n" );
                print_state = HALLSWITCH2_S_POLE_DETECTED;
            }
            break;
        }
        case HALLSWITCH2_N_POLE_DETECTED:
        {
            if ( HALLSWITCH2_N_POLE_DETECTED != print_state )
            {
                log_printf( &logger, " North pole detected\r\n" );
                log_printf( &logger, " Switch 2 - enabled\r\n\r\n" );
                print_state = HALLSWITCH2_N_POLE_DETECTED;
            }
            break;
        }
        default:
        {
            break;
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
