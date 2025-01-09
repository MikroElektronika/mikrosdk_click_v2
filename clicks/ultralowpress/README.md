
---
# Ultra-Low Press Click

> [Ultra-Low Press Click](https://www.mikroe.com/?pid_product=MIKROE-4676) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4676&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads the serial number of the sensor. If there were 
no errors it continues reading temperature and pressure data from the sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UltraLowPress

### Example Key Functions

- `ultralowpress_cfg_setup` Config Object Initialization function.
```c
void ultralowpress_cfg_setup ( ultralowpress_cfg_t *cfg );
```

- `ultralowpress_init` Initialization function.
```c
err_t ultralowpress_init ( ultralowpress_t *ctx, ultralowpress_cfg_t *cfg );
```

- `ultralowpress_ready_to_read` Ready to read.
```c
uint8_t ultralowpress_ready_to_read ( ultralowpress_t *ctx )
```

- `ultralowpress_get_press` Read pressure.
```c
float ultralowpress_get_press ( ultralowpress_t *ctx )
```

- `ultralowpress_get_temp` Read temperature.
```c
float ultralowpress_get_temp ( ultralowpress_t *ctx )
```

### Application Init

> Initializes host communication(UART and I2C). Reads devices serial number and logs it.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultralowpress_cfg_t ultralowpress_cfg;  /**< Click config object. */

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
    ultralowpress_cfg_setup( &ultralowpress_cfg );
    ULTRALOWPRESS_MAP_MIKROBUS( ultralowpress_cfg, MIKROBUS_1 );
    err_t init_flag = ultralowpress_init( &ultralowpress, &ultralowpress_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    //Serial number of sensor read
    uint16_t temp_read = 0;
    uint32_t serial_read = 0;
    init_flag = ultralowpress_generic_read( &ultralowpress, ULTRALOWPRESS_REG_SERIAL_NUM_H, &temp_read );
    serial_read = temp_read;
    serial_read <<= 16;
    init_flag |= ultralowpress_generic_read( &ultralowpress, ULTRALOWPRESS_REG_SERIAL_NUM_L, &temp_read );
    serial_read |= temp_read;
    
    if ( init_flag < 0 )
    {
        log_error( &logger, " Read" );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, " > Serial number: 0x%.8LX\r\n", serial_read );
    }
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if data is available. When it's available it reads the temperature 
and pressure data from the sensor and logs it.

```c
void application_task ( void ) 
{
    if ( ultralowpress_ready_to_read( &ultralowpress ) )
    {
        ultralowpress_clear_status( &ultralowpress );
        float temp = ultralowpress_get_temp( &ultralowpress );
        float press = ultralowpress_get_press( &ultralowpress );
        log_printf( &logger, " > Temperature[ C ]: %.2f\r\n > Pressure[ Pa ]: %.2f\r\n", temp, press );
    }
    Delay_ms ( 100 );
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
