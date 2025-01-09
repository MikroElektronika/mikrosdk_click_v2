
---
# VCP Monitor 3 Click

> [VCP Monitor 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4222) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4222&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Oct 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> VCP Monitor 3 Click show it's full usage by reading current, voltage, power, die temperature and voltage at DVCC using SPI or I2C communication protocol.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor3

### Example Key Functions

- `vcpmonitor3_cfg_setup` Config Object Initialization function.
```c
void vcpmonitor3_cfg_setup ( vcpmonitor3_cfg_t *cfg );
```

- `vcpmonitor3_init` Initialization function.
```c
err_t vcpmonitor3_init ( vcpmonitor3_t *ctx, vcpmonitor3_cfg_t *cfg );
```

- `vcpmonitor3_default_cfg` Click Default Configuration function.
```c
err_t vcpmonitor3_default_cfg ( vcpmonitor3_t *ctx );
```

- `vcpmonitor3_rd_page_0` Read Data From Page 0 function.
```c
void vcpmonitor3_rd_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes );
```

- `vcpmonitor3_set_op_mode` Set Operation Mode function.
```c
void vcpmonitor3_set_op_mode ( vcpmonitor3_t *ctx, uint8_t op_mode );
```

- `vcpmonitor3_read_p` Read Power in Watts function.
```c
float vcpmonitor3_read_p ( vcpmonitor3_t *ctx );
```

### Application Init

> Initalizes SPI or I2C driver and sets up the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor3_cfg_t vcpmonitor3_cfg;  /**< Click config object. */

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
    vcpmonitor3_cfg_setup( &vcpmonitor3_cfg );
    VCPMONITOR3_MAP_MIKROBUS( vcpmonitor3_cfg, MIKROBUS_1 );
    err_t init_flag  = vcpmonitor3_init( &vcpmonitor3, &vcpmonitor3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VCPMONITOR3_ERROR == vcpmonitor3_default_cfg ( &vcpmonitor3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example shows capabilities of VCP Monitor 3 Click board by reading current, voltage, power, die temperature and 
> voltage at DVCC and displaying the results via USART terminal.

```c
void application_task ( void )
{
    volt_data = vcpmonitor3_read_v( &vcpmonitor3 );
    log_printf( &logger, " Voltage :         %.2f V \r\n", volt_data );
    
    cur_data = vcpmonitor3_read_i( &vcpmonitor3 );
    log_printf( &logger, " Current :         %.2f A \r\n", cur_data );
    
    pow_data = vcpmonitor3_read_p( &vcpmonitor3 );
    log_printf( &logger, " Power :           %.2f W \r\n", pow_data );
   
    die_temp = vcpmonitor3_read_temp( &vcpmonitor3 );
    log_printf( &logger, " Die Temperature : %.2f C \r\n", die_temp );

    volt_vcc = vcpmonitor3_read_vcc( &vcpmonitor3 );
    log_printf( &logger, " Voltage at DVCC : %.2f V \r\n", volt_vcc );

    log_printf( &logger, " ------------------------------- \r\n" );
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
