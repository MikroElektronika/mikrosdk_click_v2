
---
# Ambient 20 Click

> [Ambient 20 Click](https://www.mikroe.com/?pid_product=MIKROE-5469) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5469&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 20 Click board by measuring the ambient light level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient20

### Example Key Functions

- `ambient20_cfg_setup` Config Object Initialization function.
```c
void ambient20_cfg_setup ( ambient20_cfg_t *cfg );
```

- `ambient20_init` Initialization function.
```c
err_t ambient20_init ( ambient20_t *ctx, ambient20_cfg_t *cfg );
```

- `ambient20_default_cfg` Click Default Configuration function.
```c
err_t ambient20_default_cfg ( ambient20_t *ctx );
```

- `ambient20_sw_reset` Software reset function.
```c
err_t ambient20_sw_reset ( ambient20_t *ctx );
```

- `ambient20_set_gain` Set data gain function.
```c
err_t ambient20_set_gain ( ambient20_t *ctx, uint8_t data0_gain, uint8_t data1_gain );
```

- `ambient20_read_data0` Read data0 function.
```c
err_t ambient20_read_data0 ( ambient20_t *ctx, uint16_t *data0_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient20_cfg_t ambient20_cfg;  /**< Click config object. */

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
    ambient20_cfg_setup( &ambient20_cfg );
    AMBIENT20_MAP_MIKROBUS( ambient20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient20_init( &ambient20, &ambient20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT20_ERROR == ambient20_default_cfg ( &ambient20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t id;
    ambient20_get_manufacturer_id( &ambient20, &id );
    
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Part ID = 0x%.2X \r\n", ( uint16_t ) id );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
}
```

### Application Task

> Measuring ambient light level by reading DATA0 and DATA1 channels of the Ambient 20 Click board and displaying it using UART Serial terminal.

```c
void application_task ( void ) 
{
    //  Task implementation.
    float data0, data1;
    ambient20_get_data_lux( &ambient20, &data0, &data1 );
    
    log_printf( &logger, "Data 0: %.2f lx \r\n", data0 );
    log_printf( &logger, "Data 1: %.2f lx \r\n", data1 );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    
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
