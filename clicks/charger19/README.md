
---
# Charger 19 Click

> [Charger 19 Click](https://www.mikroe.com/?pid_product=MIKROE-5899) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5899&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Charger 19 Click board by enabling the device
  and then reading and displaying the battery voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger19

### Example Key Functions

- `charger19_cfg_setup` Config Object Initialization function.
```c
void charger19_cfg_setup ( charger19_cfg_t *cfg );
```

- `charger19_init` Initialization function.
```c
err_t charger19_init ( charger19_t *ctx, charger19_cfg_t *cfg );
```

- `charger19_default_cfg` Click Default Configuration function.
```c
err_t charger19_default_cfg ( charger19_t *ctx );
```

- `charger19_set_vout` Charger 19 set output voltage function.
```c
err_t charger19_set_vout ( charger19_t *ctx, uint8_t vout_sel );
```

- `charger19_set_ship_mode` Charger 19 set Ship mode function.
```c
void charger19_set_ship_mode ( charger19_t *ctx, uint8_t ship_sel );
```

- `charger19_get_vbat` Charger 19 get battery voltage function.
```c
err_t charger19_get_vbat ( charger19_t *ctx, float *vbat );
```

### Application Init

> Initializes the driver and enables the device, sets the output 
  voltage to 3 V.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    charger19_cfg_t charger19_cfg;  /**< Click config object. */

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
    charger19_cfg_setup( &charger19_cfg );
    CHARGER19_MAP_MIKROBUS( charger19_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == charger19_init( &charger19, &charger19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER19_ERROR == charger19_default_cfg ( &charger19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Tracking charging status, reading battery voltage.

```c
void application_task ( void ) 
{
    float voltage = 0;
    if ( CHARGER19_OK == charger19_get_vbat ( &charger19, &voltage ) ) 
    {
        log_printf( &logger, " Battery Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms ( 1000 );
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
