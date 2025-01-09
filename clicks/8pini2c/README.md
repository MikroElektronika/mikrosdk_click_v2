
---
# 8-pin I2C Click

> [8-pin I2C Click](https://www.mikroe.com/?pid_product=MIKROE-4241) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4241&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo example reads temperature detected by Surface temp Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.8pinI2c

### Example Key Functions

- `c8pini2c_cfg_setup` Config Object Initialization function. 
```c
void c8pini2c_cfg_setup ( c8pini2c_cfg_t *cfg );
``` 
 
- `c8pini2c_init` Initialization function. 
```c
err_t c8pini2c_init ( c8pini2c_t *ctx, c8pini2c_cfg_t *cfg );
```

- `c8pini2c_generic_write` Generic write function. 
```c
void c8pini2c_generic_write ( c8pini2c_t *ctx, uint8_t slave_addr, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `c8pini2c_generic_read` Generic read function. 
```c
void c8pini2c_generic_read ( c8pini2c_t *ctx, uint8_t slave_addr, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initializes the driver and configures a Surface temp Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c8pini2c_cfg_t cfg;

    uint8_t status;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c8pini2c_cfg_setup( &cfg );
    C8PINI2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c8pini2c_init( &c8pini2c, &cfg );

    status = surfacetemp_setup( );
    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
}
```

### Application Task

> Reads the temperature detected by Surface temp Click board and logs it on the USB UART each second.

```c
void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( );
    log_printf( &logger, "> Temperature : %.2f Celsius\r\n", temperature );
    Delay_ms ( 1000 );
}
```

### Note

> In order to run this example successfully, a Surface temp Click board needs to be connected properly to an 8-pin I2C Click board.

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
