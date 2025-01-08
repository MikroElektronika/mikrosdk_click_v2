
---
# Ambient 17 Click

> [Ambient 17 Click](https://www.mikroe.com/?pid_product=MIKROE-5106) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5106&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 17 Click board by measuring the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient17

### Example Key Functions

- `ambient17_cfg_setup` Config Object Initialization function.
```c
void ambient17_cfg_setup ( ambient17_cfg_t *cfg );
```

- `ambient17_init` Initialization function.
```c
err_t ambient17_init ( ambient17_t *ctx, ambient17_cfg_t *cfg );
```

- `ambient17_default_cfg` Click Default Configuration function.
```c
err_t ambient17_default_cfg ( ambient17_t *ctx );
```

- `ambient17_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ambient17_get_int_pin ( ambient17_t *ctx );
```

- `ambient17_set_atime` This function sets the ATIME register for the selected ALS integration time.
```c
err_t ambient17_set_atime ( ambient17_t *ctx, float atime_ms );
```

- `ambient17_measure_light_level` This function reads the raw ADC data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient17_measure_light_level ( ambient17_t *ctx, uint16_t *lux );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient17_cfg_t ambient17_cfg;  /**< Click config object. */

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
    ambient17_cfg_setup( &ambient17_cfg );
    AMBIENT17_MAP_MIKROBUS( ambient17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient17_init( &ambient17, &ambient17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT17_ERROR == ambient17_default_cfg ( &ambient17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in Lux and displays the results on the USB UART. By default, the data ready interrupt triggers 
upon every ADC cycle which will be performed every 200ms.

```c
void application_task ( void )
{
    if ( !ambient17_get_int_pin ( &ambient17 ) )
    {
        uint16_t lux;
        if ( AMBIENT17_OK == ambient17_measure_light_level ( &ambient17, &lux ) )
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
