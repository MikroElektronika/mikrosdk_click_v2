
---
# Diff Press 2 Click

> [Diff Press 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4894) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4894&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example application showcases ability for device
to read and calculate mass flow or diff press pressure
in Pascals and temperature in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress2

### Example Key Functions

- `diffpress2_cfg_setup` Config Object Initialization function.
```c
void diffpress2_cfg_setup ( diffpress2_cfg_t *cfg );
```

- `diffpress2_init` Initialization function.
```c
err_t diffpress2_init ( diffpress2_t *ctx, diffpress2_cfg_t *cfg );
```

- `diffpress2_default_cfg` Click Default Configuration function.
```c
err_t diffpress2_default_cfg ( diffpress2_t *ctx );
```

- `diffpress2_get_id` Reads device ID's
```c
err_t diffpress2_get_id ( diffpress2_t *ctx );
```

- `diffpress2_reset` Reset device
```c
err_t diffpress2_reset ( diffpress2_t *ctx );
```

- `diffpress2_trigger_measurement` Pressure and temperature reading
```c
err_t diffpress2_trigger_measurement ( diffpress2_t *ctx, uint16_t trigger_type, 
                                       float *diff_press, float *temperature );
```

### Application Init

> Initialization of module communication(I2C, UART) and 
additional interrupt pin. Resets device and reads
serial and product ID's and logs them.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress2_cfg_t diffpress2_cfg;  /**< Click config object. */

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
    diffpress2_cfg_setup( &diffpress2_cfg );
    DIFFPRESS2_MAP_MIKROBUS( diffpress2_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress2_init( &diffpress2, &diffpress2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( diffpress2_default_cfg ( &diffpress2 ) ) 
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " > Product ID: 0x%.8LX\r\n", diffpress2.product_id );
    log_printf( &logger, " > Serial ID: 0x%.8LX%.8LX\r\n", 
                diffpress2.serial_id[ 0 ], diffpress2.serial_id[ 1 ] );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Read and calculate differential in Pascal and temperature 
in degrees Celsius every 300ms.

```c
void application_task ( void )
{
    float pressure;
    float temperature;

    if ( diffpress2_trigger_measurement( &diffpress2, DIFFPRESS2_CMD_TRIGGER_MEAS_DIFF_PRESS, 
                                         &pressure, &temperature ) )
    {
        log_error( &logger, " Read data." );
    }
    else
    {
        log_printf( &logger, " > Pressure[Pa]: %.2f\r\n", pressure );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
        log_printf( &logger, "*************************************\r\n" );
    }

    Delay_ms ( 300 );
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
