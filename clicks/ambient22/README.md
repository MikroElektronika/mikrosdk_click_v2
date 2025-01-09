
---
# Ambient 22 Click

> [Ambient 22 Click](https://www.mikroe.com/?pid_product=MIKROE-5647) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5647&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 22 Click board by measuring the ambient light level in lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient22

### Example Key Functions

- `ambient22_cfg_setup` Config Object Initialization function.
```c
void ambient22_cfg_setup ( ambient22_cfg_t *cfg );
```

- `ambient22_init` Initialization function.
```c
err_t ambient22_init ( ambient22_t *ctx, ambient22_cfg_t *cfg );
```

- `ambient22_default_cfg` Click Default Configuration function.
```c
err_t ambient22_default_cfg ( ambient22_t *ctx );
```

- `ambient22_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ambient22_get_int_pin ( ambient22_t *ctx );
```

- `ambient22_read_lux` This function checks for a conversion ready flag bit and then reads the ambient light level in lux.
```c
err_t ambient22_read_lux ( ambient22_t *ctx, float *lux );
```

- `ambient22_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t ambient22_write_register ( ambient22_t *ctx, uint8_t reg, uint16_t data_in );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient22_cfg_t ambient22_cfg;  /**< Click config object. */

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
    ambient22_cfg_setup( &ambient22_cfg );
    AMBIENT22_MAP_MIKROBUS( ambient22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient22_init( &ambient22, &ambient22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT22_ERROR == ambient22_default_cfg ( &ambient22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in lux and displays the results on the USB UART. By default, the data ready interrupt triggers every 800ms.

```c
void application_task ( void )
{
    float lux;
    // Wait for a data ready interrupt
    while ( ambient22_get_int_pin ( &ambient22 ) );
    
    if ( AMBIENT22_OK == ambient22_read_lux ( &ambient22, &lux ) )
    {
        log_printf( &logger, " Ambient light: %.2f lux\r\n\n", lux );
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
