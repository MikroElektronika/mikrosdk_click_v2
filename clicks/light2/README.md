
---
# Light 2 Click

> [Light 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6022) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6022&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Light 2 Click board by measuring 
  the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Light2

### Example Key Functions

- `light2_cfg_setup` Config Object Initialization function.
```c
void light2_cfg_setup ( light2_cfg_t *cfg );
```

- `light2_init` Initialization function.
```c
err_t light2_init ( light2_t *ctx, light2_cfg_t *cfg );
```

- `light2_default_cfg` Click Default Configuration function.
```c
err_t light2_default_cfg ( light2_t *ctx );
```

- `light2_read_raw_data` This function reads raw data from the ADC of Light 2 Click board.
```c
err_t light2_read_raw_data ( light2_t *ctx, uint16_t *data_out );
```

- `light2_get_cal_const` This function is used to get a calculation constant depending on Light 2 Click board configuration.
```c
err_t light2_get_cal_const ( light2_t *ctx );
```

- `light2_get_light_data` This function is used to read light data of Light 2 Click board configuration.
```c
err_t light2_get_light_data ( light2_t *ctx, float *light_data );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light2_cfg_t light2_cfg;  /**< Click config object. */

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
    light2_cfg_setup( &light2_cfg );
    LIGHT2_MAP_MIKROBUS( light2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light2_init( &light2, &light2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT2_ERROR == light2_default_cfg ( &light2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ADC voltage and then calculates the illuminance from it.
  The calculated value of illuminance in lux is being displayed on the USB UART approximately once per second. 

```c
void application_task ( void ) 
{
    float lux_data = 0;

    light2_get_light_data( &light2, &lux_data );
    log_printf( &logger, " LUX data: %.2f LUX \r\n", lux_data );

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
