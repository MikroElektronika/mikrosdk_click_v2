
---
# PAC1720 Click

> [PAC1720 Click](https://www.mikroe.com/?pid_product=MIKROE-4905) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4905&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PAC1720 Click board by reading the voltage, current, and power from both available channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1720

### Example Key Functions

- `pac1720_cfg_setup` Config Object Initialization function.
```c
void pac1720_cfg_setup ( pac1720_cfg_t *cfg );
```

- `pac1720_init` Initialization function.
```c
err_t pac1720_init ( pac1720_t *ctx, pac1720_cfg_t *cfg );
```

- `pac1720_default_cfg` Click Default Configuration function.
```c
err_t pac1720_default_cfg ( pac1720_t *ctx );
```

- `pac1720_set_vsource_config` This function sets the Voltage Source configuration (sample time and average samples) for the selected channel.
```c
err_t pac1720_set_vsource_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, pac1720_sample_time_t stime, pac1720_avg_t avg );
```

- `pac1720_set_vsense_config` This function sets the Voltage Sense configuration (sample time, average samples, and sampling range) for the selected channel.
```c
err_t pac1720_set_vsense_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, pac1720_sample_time_t stime, pac1720_avg_t avg, pac1720_cs_rng_t cs_rng );
```

- `pac1720_get_measurements` This function reads voltage, current, and power from the selected channel.
```c
err_t pac1720_get_measurements ( pac1720_t *ctx, pac1720_ch_sel_t ch, float *voltage, float *current, float *power );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pac1720_cfg_t pac1720_cfg;  /**< Click config object. */

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
    pac1720_cfg_setup( &pac1720_cfg );
    PAC1720_MAP_MIKROBUS( pac1720_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pac1720_init( &pac1720, &pac1720_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PAC1720_ERROR == pac1720_default_cfg ( &pac1720 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage, current, and power from both channels and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float voltage = 0, current = 0, power = 0;
    
    if ( PAC1720_OK == pac1720_get_measurements ( &pac1720, PAC1720_CHANNEL_1, &voltage, &current, &power ) )
    {
        log_printf( &logger, " Channel 1:\r\n" );
        log_printf( &logger, " U: %.3fV, I: %.3fA, P: %.3fW\r\n", voltage, current, power );
    }
    
    if ( PAC1720_OK == pac1720_get_measurements ( &pac1720, PAC1720_CHANNEL_2, &voltage, &current, &power ) )
    {
        log_printf( &logger, " Channel 2:\r\n" );
        log_printf( &logger, " U: %.3fV, I: %.3fA, P: %.3fW\r\n\n", voltage, current, power  );
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
