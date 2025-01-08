
---
# Illuminance Click

> [Illuminance Click](https://www.mikroe.com/?pid_product=MIKROE-1688) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1688&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Illuminance Click board by reading and displaying the RAW channels data measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Illuminance

### Example Key Functions

- `illuminance_cfg_setup` Config Object Initialization function.
```c
void illuminance_cfg_setup ( illuminance_cfg_t *cfg );
```

- `illuminance_init` Initialization function.
```c
err_t illuminance_init ( illuminance_t *ctx, illuminance_cfg_t *cfg );
```

- `illuminance_default_cfg` Click Default Configuration function.
```c
err_t illuminance_default_cfg ( illuminance_t *ctx );
```

- `illuminance_set_atime` This function sets the timing register for the selected integration time.
```c
err_t illuminance_set_atime ( illuminance_t *ctx, float atime_ms );
```

- `illuminance_set_gain` This function sets the gain level.
```c
err_t illuminance_set_gain ( illuminance_t *ctx, uint8_t gain );
```

- `illuminance_read_raw_data` This function checks if the data is ready and then reads the raw ADC data from two channels.
```c
err_t illuminance_read_raw_data ( illuminance_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    illuminance_cfg_t illuminance_cfg;  /**< Click config object. */

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
    illuminance_cfg_setup( &illuminance_cfg );
    ILLUMINANCE_MAP_MIKROBUS( illuminance_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == illuminance_init( &illuminance, &illuminance_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ILLUMINANCE_ERROR == illuminance_default_cfg ( &illuminance ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the RAW channels data measurements
and displays the results on the USB UART. By default, the data ready interrupt triggers 
upon every ADC cycle which will be performed every 200ms.

```c
void application_task ( void )
{
    if ( !illuminance_get_int_pin ( &illuminance ) )
    {
        uint16_t ch0 = 0;
        uint16_t ch1 = 0;
        if ( ILLUMINANCE_OK == illuminance_read_raw_data ( &illuminance, &ch0, &ch1 ) )
        {
            log_printf ( &logger, " CH0: %u\r\n", ch0 );
            log_printf ( &logger, " CH1: %u\r\n\n", ch1 );
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
