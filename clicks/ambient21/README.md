
---
# Ambient 21 Click

> [Ambient 21 Click](https://www.mikroe.com/?pid_product=MIKROE-5529) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5529&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 21 Click board by measuring the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient21

### Example Key Functions

- `ambient21_cfg_setup` Config Object Initialization function.
```c
void ambient21_cfg_setup ( ambient21_cfg_t *cfg );
```

- `ambient21_init` Initialization function.
```c
err_t ambient21_init ( ambient21_t *ctx, ambient21_cfg_t *cfg );
```

- `ambient21_default_cfg` Click Default Configuration function.
```c
err_t ambient21_default_cfg ( ambient21_t *ctx );
```

- `ambient21_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ambient21_get_int_pin ( ambient21_t *ctx );
```

- `ambient21_read_raw_data` This function checks if the data is ready and then reads the raw ADC data from two channels.
```c
err_t ambient21_read_raw_data ( ambient21_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );
```

- `ambient21_measure_light_level` This function reads the raw ADC data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient21_measure_light_level ( ambient21_t *ctx, uint16_t *lux );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient21_cfg_t ambient21_cfg;  /**< Click config object. */

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
    ambient21_cfg_setup( &ambient21_cfg );
    AMBIENT21_MAP_MIKROBUS( ambient21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient21_init( &ambient21, &ambient21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT21_ERROR == ambient21_default_cfg ( &ambient21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in Lux
and displays the results on the USB UART. By default, the data ready interrupt triggers
upon every ADC cycle which occurs every 200ms.

```c
void application_task ( void )
{
    uint16_t lux;
    if ( !ambient21_get_int_pin ( &ambient21 ) )
    {
        if ( AMBIENT21_OK == ambient21_measure_light_level ( &ambient21, &lux ) )
        {
            log_printf ( &logger, " Ambient light level [Lux]: %u\r\n\n", lux );
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
