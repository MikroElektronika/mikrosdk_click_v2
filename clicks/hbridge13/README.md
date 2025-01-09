
---
# H-Bridge 13 Click

> [H-Bridge 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5795) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5795&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 13 Click board by
  driving the motor connected to OUT A and OUT B, in both directions with braking and freewheeling.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge13

### Example Key Functions

- `hbridge13_cfg_setup` Config Object Initialization function.
```c
void hbridge13_cfg_setup ( hbridge13_cfg_t *cfg );
```

- `hbridge13_init` Initialization function.
```c
err_t hbridge13_init ( hbridge13_t *ctx, hbridge13_cfg_t *cfg );
```

- `hbridge13_default_cfg` Click Default Configuration function.
```c
err_t hbridge13_default_cfg ( hbridge13_t *ctx );
```

- `hbridge13_write_reg` H-Bridge 13 write register function.
```c
err_t hbridge13_write_reg ( hbridge13_t *ctx, uint8_t reg, uint8_t data_out );
```

- `hbridge13_set_direction` H-Bridge 13 set direction function.
```c
err_t hbridge13_set_direction ( hbridge13_t *ctx, uint8_t dir_set, uint8_t speed );
```

- `hbridge13_get_an_voltage` H-Bridge 13 get xIPROPI voltage function.
```c
err_t hbridge13_get_an_voltage ( hbridge13_t *ctx, float *voltage, uint8_t an_sel );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge13_cfg_t hbridge13_cfg;  /**< Click config object. */

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
    hbridge13_cfg_setup( &hbridge13_cfg );
    HBRIDGE13_MAP_MIKROBUS( hbridge13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge13_init( &hbridge13, &hbridge13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE13_ERROR == hbridge13_default_cfg ( &hbridge13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example is driving a motor in both directions with changes in speed and
  motor braking and freewheeling in between.

```c
void application_task ( void ) 
{
    for( uint8_t n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        log_printf( &logger, " Motor in forward mode with speed of %d %% \r\n", ( uint16_t ) n_cnt );
        hbridge13_set_direction( &hbridge13, HBRIDGE13_DIR_FORWARD, n_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge13_set_brake( &hbridge13 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for( uint8_t n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        log_printf( &logger, " Motor in reverse with speed of %d %% \r\n", ( uint16_t ) n_cnt );
        hbridge13_set_direction( &hbridge13, HBRIDGE13_DIR_REVERSE, n_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge13_set_coast( &hbridge13 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
