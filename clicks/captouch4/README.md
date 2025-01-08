
---
# Cap Touch 4 Click

> [Cap Touch 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6399) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6399&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Cap Touch 4 Click board by reading the proximity, touch, and movement events.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch4

### Example Key Functions

- `captouch4_cfg_setup` Config Object Initialization function.
```c
void captouch4_cfg_setup ( captouch4_cfg_t *cfg );
```

- `captouch4_init` Initialization function.
```c
err_t captouch4_init ( captouch4_t *ctx, captouch4_cfg_t *cfg );
```

- `captouch4_default_cfg` Click Default Configuration function.
```c
err_t captouch4_default_cfg ( captouch4_t *ctx );
```

- `captouch4_read_system_flags` This function reads the system flags register.
```c
err_t captouch4_read_system_flags ( captouch4_t *ctx, uint8_t *sysflags );
```

- `captouch4_read_cap_counts` This function reads the counts number directly proportional to capacitance. The system is calibrated to make the counts as sensitive as possible to changes in capacitance for relative measurements.
```c
err_t captouch4_read_cap_counts ( captouch4_t *ctx, uint16_t *cap_counts );
```

- `captouch4_read_lta` This function reads the long-term averate (LTA) value. The LTA is used as reference to compare with capacitance counts.
```c
err_t captouch4_read_lta ( captouch4_t *ctx, uint16_t *lta );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    captouch4_cfg_t captouch4_cfg;  /**< Click config object. */

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
    captouch4_cfg_setup( &captouch4_cfg );
    CAPTOUCH4_MAP_MIKROBUS( captouch4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == captouch4_init( &captouch4, &captouch4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CAPTOUCH4_ERROR == captouch4_default_cfg ( &captouch4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity, touch, and movement events and approximately displays the results on the USB UART every 200ms. The capacitance counts and the long-term average values are also displayed.

```c
void application_task ( void )
{
    uint8_t sys_flags = 0;
    uint8_t movement = 0;
    uint16_t cap_counts = 0;
    uint16_t lta = 0;
    if ( CAPTOUCH4_OK == captouch4_read_system_flags ( &captouch4, &sys_flags ) )
    {
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_PROX )
        {
            log_printf( &logger, " Proximity detected\r\n" );
        }
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_TOUCH )
        {
            log_printf( &logger, " Touch detected\r\n" );
        }
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_MOVEMENT )
        {
            if ( CAPTOUCH4_OK == captouch4_read_movement ( &captouch4, &movement ) )
            {
                log_printf( &logger, " Movement detected: %u\r\n", ( uint16_t ) movement );
            }
        }
        if ( ( sys_flags & CAPTOUCH4_SYSFLAGS0_MOVEMENT ) || 
             ( sys_flags & CAPTOUCH4_SYSFLAGS0_PROX ) || 
             ( sys_flags & CAPTOUCH4_SYSFLAGS0_TOUCH ) )
        {
            if ( CAPTOUCH4_OK == captouch4_read_cap_counts ( &captouch4, &cap_counts ) )
            {
                log_printf( &logger, " Capacitance counts: %u\r\n", cap_counts );
            }
            if ( CAPTOUCH4_OK == captouch4_read_lta ( &captouch4, &lta ) )
            {
                log_printf( &logger, " Long-term average: %u\r\n\n", lta );
            }
        }
        else
        {
            log_printf( &logger, " No detected events\r\n\n" );
        }
    }
    Delay_ms ( 200 );
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
