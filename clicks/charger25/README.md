
---
# Charger 25 Click

> [Charger 25 Click](https://www.mikroe.com/?pid_product=MIKROE-5839) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5839&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Charger 25 Click board&trade; 
> by enabling battery charging and displaying battery voltage and charging status.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger25

### Example Key Functions

- `charger25_cfg_setup` Config Object Initialization function.
```c
void charger25_cfg_setup ( charger25_cfg_t *cfg );
```

- `charger25_init` Initialization function.
```c
err_t charger25_init ( charger25_t *ctx, charger25_cfg_t *cfg );
```

- `charger25_default_cfg` Click Default Configuration function.
```c
err_t charger25_default_cfg ( charger25_t *ctx );
```

- `charger25_get_vbat` Charger 25 get VBAT function.
```c
err_t charger25_get_vbat ( charger25_t *ctx, uint16_t *vbat );
```

- `charger25_get_status` Charger 25 get charging status function.
```c
err_t charger25_get_status ( charger25_t *ctx, charger25_status_t *status );
```

- `charger25_get_vbat_lim` Charger 25 get battery voltage limit function.
```c
err_t charger25_get_vbat_lim ( charger25_t *ctx, uint16_t *vtg_lim );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger25_cfg_t charger25_cfg;  /**< Click config object. */

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
    charger25_cfg_setup( &charger25_cfg );
    CHARGER25_MAP_MIKROBUS( charger25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger25_init( &charger25, &charger25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER25_ERROR == charger25_default_cfg ( &charger25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the results of the battery voltage, 
> minimal system voltage, battery voltage limit and charging status.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static uint16_t vtg_data = 0;
    if ( CHARGER25_OK == charger25_get_status ( &charger25, &status ) )
    {
        charger25_display_status( );
    }
    Delay_ms ( 100 );
    
    if ( CHARGER25_OK == charger25_get_vbat( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VBAT: %u [mV]\r\n", vtg_data );
    }
    Delay_ms ( 100 );
    
    if ( CHARGER25_OK == charger25_get_vsys_min( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VMIN: %u [mV]\r\n", vtg_data );
    }
    Delay_ms ( 100 );
    
    if ( CHARGER25_OK == charger25_get_vbat_lim( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VLIM: %u [mV]\r\n", vtg_data );
    }
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms ( 1000 );
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
