
---
# Pac1934 Click

> [Pac1934 Click](https://www.mikroe.com/?pid_product=MIKROE-2735) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2735&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures the voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pac1934

### Example Key Functions

- `pac1934_cfg_setup` Config Object Initialization function. 
```c
void pac1934_cfg_setup ( pac1934_cfg_t *cfg );
``` 
 
- `pac1934_init` Initialization function. 
```c
err_t pac1934_init ( pac1934_t *ctx, pac1934_cfg_t *cfg );
```

- `pac1934_write_byte` Write one byte function. 
```c
void pac1934_write_byte ( pac1934_t *ctx, uint8_t wr_addr, uint8_t wr_data );
```
 
- `pac1934_read_byte` Read one byte function. 
```c
uint8_t pac1934_read_byte ( pac1934_t *ctx, uint8_t rd_addr );
```

- `pac1934_send_command` Send command function. 
```c
void pac1934_send_command ( pac1934_t *ctx, uint8_t wr_cmd );
```

### Application Init

> Initalizes device, enables the device and makes an initial log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pac1934_cfg_t cfg;

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

    pac1934_cfg_setup( &cfg );
    PAC1934_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pac1934_init( &pac1934, &cfg );
}
```

### Application Task

> This is an example that shows the most important
> functions that PAC1934 Click has, it mesures voltage, current, power and energy.

```c
void application_task ( void )
{
    float read_value;
    
    pac1934_dev_reset( &pac1934 );
    pac1934_write_byte( &pac1934, PAC1934_CHANNEL_DIS, PAC1934_CHANNEL_DIS_ALL_CHA );
    pac1934_write_byte( &pac1934, PAC1934_CTRL_REG, PAC1934_CTRL_SAMPLE_RATE_8 | PAC1934_CTRL_SINGLE_SHOT_MODE );
    Delay_ms ( 100 );
    pac1934_send_command( &pac1934, PAC1934_REFRESH_CMD );
    
    read_value = pac1934_measure_voltage( &pac1934, 1 );
    log_printf( &logger, "Voltage : %.2f V\r\n", read_value );

    read_value = pac1934_measure_current( &pac1934, 1 );
    log_printf( &logger, "Amperage :  %.2f mA\r\n", read_value );

    read_value = pac1934_measure_power( &pac1934, 1 );
    log_printf( &logger, "Power : %.2f W\r\n", read_value );
    
    read_value = pac1934_measure_energy( &pac1934, 1, 8 );
    log_printf( &logger, "Energy :  %.2f J \r\n", read_value );
    log_printf( &logger, "--------------------- \r\n" );
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
