
---
# Charger 26 Click

> [Charger 26 Click](https://www.mikroe.com/?pid_product=MIKROE-5882) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5882&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Charger 26 Click board by enabling the device
  and then reading and displaying the charger status.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger26

### Example Key Functions

- `charger26_cfg_setup` Config Object Initialization function.
```c
void charger26_cfg_setup ( charger26_cfg_t *cfg );
```

- `charger26_init` Initialization function.
```c
err_t charger26_init ( charger26_t *ctx, charger26_cfg_t *cfg );
```

- `charger26_default_cfg` Click Default Configuration function.
```c
void charger26_default_cfg ( charger26_t *ctx );
```

- `charger26_set_vsel` Charger 26 select charger voltage function.
```c
void charger26_set_vsel ( charger26_t *ctx, uint8_t vout_sel );
```

- `charger26_set_isel` Charger 26 select charger current function.
```c
void charger26_set_isel ( charger26_t *ctx, uint8_t iout_sel );
```

- `charger26_get_chg_state` Charger 26 chg pin reading function.
```c
uint8_t charger26_get_chg_state ( charger26_t *ctx );
```

### Application Init

> Initializes the driver and enables the device, sets the output 
  voltage to 4.2 V and charging current to 100 mA.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger26_cfg_t charger26_cfg;  /**< Click config object. */

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
    charger26_cfg_setup( &charger26_cfg );
    CHARGER26_MAP_MIKROBUS( charger26_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger26_init( &charger26, &charger26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger26_default_cfg ( &charger26 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Connect input power and battery. \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Enableing output. \r\n" );
    charger26_enable_output ( &charger26, CHARGER26_ENABLE_OUTPUT );
    
    while ( CHARGER26_PIN_STATE_LOW != charger26_get_chg_state( &charger26 ) )
    {
        log_printf( &logger, " Check connection. \r\n" );
        Delay_ms ( 1000 );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Tracking charging status, as soon as charging stops, device output is disabled.

```c
void application_task ( void ) 
{
    if ( CHARGER26_PIN_STATE_LOW == charger26_get_chg_state( &charger26 ) )
    {
        log_printf( &logger, " Battery is charging. \r\n" );
    }
    else
    {
        log_printf( &logger, " Battery isn't charging, disabling output. \r\n" );
        charger26_enable_output ( &charger26, CHARGER26_DISABLE_OUTPUT );
        for ( ; ; );
    }
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
