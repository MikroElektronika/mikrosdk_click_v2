
---
# Light 3 Click

> [Light 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5994) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5994&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Light 3 Click board by measuring the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Light3

### Example Key Functions

- `light3_cfg_setup` Config Object Initialization function.
```c
void light3_cfg_setup ( light3_cfg_t *cfg );
```

- `light3_init` Initialization function.
```c
err_t light3_init ( light3_t *ctx, light3_cfg_t *cfg );
```

- `light3_default_cfg` Click Default Configuration function.
```c
err_t light3_default_cfg ( light3_t *ctx );
```

- `light3_sw_reset` This function is used to perform software reset.
```c
err_t light3_sw_reset ( light3_t *ctx );
```

- `light3_write_reg` This function writes a desired data into the selected register by using I2C serial interface.
```c
err_t light3_write_reg ( light3_t *ctx, uint8_t reg, uint16_t data_in );
```

- `light3_get_ch0_data` This function reads ambient light data from the Channel 0 and performs the calculatios from raw data to Lux.
```c
err_t light3_get_ch0_data ( light3_t *ctx, float *lux );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light3_cfg_t light3_cfg;  /**< Click config object. */

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
    light3_cfg_setup( &light3_cfg );
    LIGHT3_MAP_MIKROBUS( light3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light3_init( &light3, &light3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT3_ERROR == light3_default_cfg ( &light3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reading channel 0 ambient light level in lux as soon as it is available ( once in 1.6 seconds ) and displaying it on the UART terminal.

```c
void application_task ( void ) 
{
    float lux_data = 0;
    if ( LIGHT3_PIN_STATE_LOW == light3_get_int_pin( &light3 ) )
    { 
        light3_get_ch0_data( &light3, &lux_data );
        log_printf( &logger, "Light level: %f lux \r\n", ( float ) lux_data );
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
