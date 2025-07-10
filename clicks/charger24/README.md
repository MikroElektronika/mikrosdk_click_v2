
---
# Charger 24 Click

> [Charger 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6653) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6653&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Charger 24 Click board. The application 
initializes the device, enables battery charging, and continuously monitors the 
charging and USB power status. It displays whether the battery is currently 
charging, fully charged, or if no input is detected, as well as whether the USB 
power is valid.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger24

### Example Key Functions

- `charger24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void charger24_cfg_setup ( charger24_cfg_t *cfg );
```

- `charger24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t charger24_init ( charger24_t *ctx, charger24_cfg_t *cfg );
```

- `charger24_enable_charging` This function enables battery charging on the Charger 24 Click board.
```c
void charger24_enable_charging ( charger24_t *ctx );
```

- `charger24_get_iok_pin` This function returns the logic state of the IOK pin.
```c
uint8_t charger24_get_iok_pin ( charger24_t *ctx );
```

- `charger24_get_status` This function checks the battery charging status by polling the STAT pin.
```c
uint8_t charger24_get_status ( charger24_t *ctx );
```

### Application Init

> Initializes the logger and the Charger 24 Click driver and enables charging while disabling boost mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger24_cfg_t charger24_cfg;  /**< Click config object. */

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
    charger24_cfg_setup( &charger24_cfg );
    CHARGER24_MAP_MIKROBUS( charger24_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger24_init( &charger24, &charger24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    charger24_disable_boost ( &charger24 );
    charger24_enable_charging ( &charger24 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads and logs the charging and USB power status.

```c
void application_task ( void )
{
    uint8_t status = charger24_get_status ( &charger24 );
    
    log_printf( &logger, "\r\n Charging status: " );
    switch ( status )
    {
        case CHARGER24_STATE_NO_INPUT:
        {
            log_printf( &logger, "No input or fault\r\n" );
            break;
        }
        case CHARGER24_STATE_CHARGING:
        {
            log_printf( &logger, "Trickle, precharge, fast charge\r\n" );
            break;
        }
        case CHARGER24_STATE_CHARGE_DONE:
        {
            log_printf( &logger, "Top-off and done\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, "Unknown\r\n" );
            break;
        }
    }

    log_printf( &logger, " USB status: " );
    if ( charger24_get_iok_pin( &charger24 ) )
    {
        log_printf( &logger, "No power\r\n" );
    }
    else
    {
        log_printf( &logger, "Power good\r\n" );
    }
}
```

### Note

> Ensure a valid USB input source and battery are connected to observe status transitions.

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
