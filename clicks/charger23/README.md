
---
# Charger 23 Click

> [Charger 23 Click](https://www.mikroe.com/?pid_product=MIKROE-5573) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5573&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Charger 23 Click board by enabling the device and then reading and displaying the charger status.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger23

### Example Key Functions

- `charger23_cfg_setup` Config Object Initialization function.
```c
void charger23_cfg_setup ( charger23_cfg_t *cfg );
```

- `charger23_init` Initialization function.
```c
err_t charger23_init ( charger23_t *ctx, charger23_cfg_t *cfg );
```

- `charger23_enable_device` This function enables the device by setting the EN pin to HIGH logic state.
```c
void charger23_enable_device ( charger23_t *ctx );
```

- `charger23_disable_device` This function disables the device by setting the EN pin to LOW logic state.
```c
void charger23_disable_device ( charger23_t *ctx );
```

- `charger23_get_charger_state` This function returns the charger state.
```c
uint8_t charger23_get_charger_state ( charger23_t *ctx );
```

### Application Init

> Initializes the driver and enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger23_cfg_t charger23_cfg;  /**< Click config object. */

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
    charger23_cfg_setup( &charger23_cfg );
    CHARGER23_MAP_MIKROBUS( charger23_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger23_init( &charger23, &charger23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger23_enable_device ( &charger23 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the charger state and displays it on the USB UART on change.

```c
void application_task ( void )
{
    static uint8_t chg_state_old = CHARGER23_STATE_UNKNOWN;
    uint8_t chg_state = charger23_get_charger_state ( &charger23 );
    if ( chg_state_old != chg_state )
    {
        chg_state_old = chg_state;
        log_printf( &logger, "\r\n Charger state: " );
        switch ( chg_state )
        {
            case CHARGER23_STATE_IDLE:
            {
                log_printf( &logger, "Charge completed with no fault (Inhibit) or Standby\r\n" );
                break;
            }
            case CHARGER23_STATE_CHARGING:
            {
                log_printf( &logger, "Charging in one of the three modes\r\n" );
                break;
            }
            case CHARGER23_STATE_FAULT:
            {
                log_printf( &logger, "Fault\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, "Unknown\r\n" );
                break;
            }
        }
        Delay_ms ( 100 );
    }
}
```

### Note

> Depending on the CURR SEL onboard jumper position this Click board is able to charge batteries of 250mAh or 500mAh rated capacity.

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
