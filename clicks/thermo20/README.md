
---
# Thermo 20 Click

> [Thermo 20 Click](https://www.mikroe.com/?pid_product=MIKROE-4316) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4316&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases the ability of Thermo 20 Click board to
 read it's serial number. It can read themperature and measure from -40degC to 120degC.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo20

### Example Key Functions

- `thermo20_cfg_setup` Config Object Initialization function.
```c
void thermo20_cfg_setup ( thermo20_cfg_t *cfg );
```

- `thermo20_init` Initialization function.
```c
err_t thermo20_init ( thermo20_t *ctx, thermo20_cfg_t *cfg );
```

- `thermo20_default_cfg` Click Default Configuration function.
```c
err_t thermo20_default_cfg ( thermo20_t *ctx );
```

- `thermo20_set_cmd` Send command function.
```c
err_t thermo20_set_cmd ( thermo20_t *ctx, uint8_t cmd );
```

- `thermo20_start_conversion` Start conversion function.
```c
void thermo20_start_conversion ( thermo20_t *ctx );
```

- `thermo20_get_temperature` Get temperature data function.
```c
float thermo20_get_temperature ( thermo20_t *ctx );
```

### Application Init

> Initialization communication modules(I2C, UART). Resets device and read Serial Number.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo20_cfg_t thermo20_cfg;  /**< Click config object. */

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
    thermo20_cfg_setup( &thermo20_cfg );
    THERMO20_MAP_MIKROBUS( thermo20_cfg, MIKROBUS_1 );
    err_t init_flag = thermo20_init( &thermo20, &thermo20_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    thermo20_default_cfg ( &thermo20 );
    
    uint32_t ser_numb = thermo20_get_serial_number( &thermo20 );
    log_printf( &logger, " > Serial Number: %lu\r\n", ser_numb );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In span of ~ 1000ms it sends command for adc conversion of temperature, reads ADC value,
 and calculates temperature in degrees C.

```c
void application_task ( void ) 
{
    thermo20_start_conversion( &thermo20 );
    float temperature = thermo20_get_temperature( &thermo20 );
    log_printf( &logger, " > Temperature[deg C]: %.2f\r\n", temperature );
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
