
---
# Magneto 13 Click

> [Magneto 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5643) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5643&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the Magneto 13 Click driver.
> The demo application reads and displays 
> the magnet's angular position in degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto13

### Example Key Functions

- `magneto13_cfg_setup` Config Object Initialization function.
```c
void magneto13_cfg_setup ( magneto13_cfg_t *cfg );
```

- `magneto13_init` Initialization function.
```c
err_t magneto13_init ( magneto13_t *ctx, magneto13_cfg_t *cfg );
```

- `magneto13_default_cfg` Click Default Configuration function.
```c
err_t magneto13_default_cfg ( magneto13_t *ctx );
```

- `magneto13_get_angle` Magneto 13 gets the angular position function.
```c
err_t magneto13_get_angle ( magneto13_t *ctx, float *angle );
```

- `magneto13_get_field_strength` Magneto 13 gets the magnetic field strength function.
```c
err_t magneto13_get_field_strength ( magneto13_t *ctx, uint8_t *field_strength );
```

- `magneto13_set_mag_field_thd` Magneto 13 sets the magnetic field threshold function.
```c
err_t magneto13_set_mag_field_thd ( magneto13_t *ctx, uint8_t mglt, uint8_t mght );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto13_cfg_t magneto13_cfg;  /**< Click config object. */

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
    magneto13_cfg_setup( &magneto13_cfg );
    MAGNETO13_MAP_MIKROBUS( magneto13_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneto13_init( &magneto13, &magneto13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO13_ERROR == magneto13_default_cfg ( &magneto13 ) )
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

> This example demonstrates the use of the Magneto 13 Click board&trade;.
> Reads and displays the magnet's angular position in degrees.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t field_strength = 0;
    static float angle = 0;
    if ( MAGNETO13_OK == magneto13_get_field_strength( &magneto13, &field_strength ) )
    {
        if ( ( MAGNETO13_FLD_ST_OK == field_strength ) && ( MAGNETO13_OK == magneto13_get_angle( &magneto13, &angle ) ) )
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
