
---
# Magneto 14 Click

> [Magneto 14 Click](https://www.mikroe.com/?pid_product=MIKROE-5751) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5751&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the Magneto 14 Click driver.
> The demo application reads and displays 
> the magnet's angular position in degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto14

### Example Key Functions

- `magneto14_cfg_setup` Config Object Initialization function.
```c
void magneto14_cfg_setup ( magneto14_cfg_t *cfg );
```

- `magneto14_init` Initialization function.
```c
err_t magneto14_init ( magneto14_t *ctx, magneto14_cfg_t *cfg );
```

- `magneto14_default_cfg` Click Default Configuration function.
```c
err_t magneto14_default_cfg ( magneto14_t *ctx );
```

- `magneto14_get_angle` Magneto 14 gets the angular position function.
```c
err_t magneto14_get_angle ( magneto14_t *ctx, float *angle );
```

- `magneto14_get_field_strength` Magneto 14 gets the magnetic field strength function.
```c
err_t magneto14_get_field_strength ( magneto14_t *ctx, uint8_t *field_strength );
```

- `magneto14_get_mgh` Magneto 14 gets the MGH function.
```c
uint8_t magneto14_get_mgh ( magneto14_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto14_cfg_t magneto14_cfg;  /**< Click config object. */

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
    magneto14_cfg_setup( &magneto14_cfg );
    MAGNETO14_MAP_MIKROBUS( magneto14_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneto14_init( &magneto14, &magneto14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO14_ERROR == magneto14_default_cfg ( &magneto14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Magneto 14 Click board&trade;.
> Reads and displays the magnet's angular position in degrees.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t field_strength = 0;
    static float angle = 0;
    if ( MAGNETO14_OK == magneto14_get_field_strength( &magneto14, &field_strength ) )
    {
        if ( ( MAGNETO14_FLD_ST_OK == field_strength ) && 
             ( MAGNETO14_MGH_ST_OK == magneto14_get_mgh( &magneto14 ) ) && 
             ( MAGNETO14_OK == magneto14_get_angle( &magneto14, &angle ) ) )
        {
            log_printf( &logger, " Angle: %.2f [deg]\r\n", angle );
            log_printf( &logger, " -------------------- \r\n" );
            Delay_ms ( 1000 );
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
