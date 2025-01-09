
---
# DIGI POT 7 Click

> [DIGI POT 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4414) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4414&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrate the use of the DIGI POT 7 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT7

### Example Key Functions

- `digipot7_cfg_setup` Config Object Initialization function.
```c
void digipot7_cfg_setup ( digipot7_cfg_t *cfg );
```

- `digipot7_init` Initialization function.
```c
err_t digipot7_init ( digipot7_t *ctx, digipot7_cfg_t *cfg );
```

- `digipot7_hw_reset` Hardware reset function
```c
void digipot7_hw_reset ( digipot7_t *ctx );
```

- `digipot7_read_rdac` The function read a 10-bit RDAC data
```c
uint16_t digipot7_read_rdac ( digipot7_t *ctx );
```

- `digipot7_write_rdac` The function writes a 10-bit RDAC data
```c
void digipot7_write_rdac ( digipot7_t *ctx, uint16_t rdac_data );
```

### Application Init

> Initialization enables I2C, perform a hardware reset, enable write and set to normal operating mode, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot7_cfg_t digipot7_cfg;  /**< Click config object. */

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
    digipot7_cfg_setup( &digipot7_cfg );
    DIGIPOT7_MAP_MIKROBUS( digipot7_cfg, MIKROBUS_1 );
    err_t init_flag = digipot7_init( &digipot7, &digipot7_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Hardware Reset \r\n" );
    digipot7_hw_reset( &digipot7 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Enable Write \r\n" );
    digipot7_enable_write( &digipot7 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Set normal operating mode \r\n" );
    digipot7_operating_mode( &digipot7, DIGIPOT7_NORMAL_MODE );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
}
```

### Application Task

> In this example we set different resistance values: 1.024 kOhm, 2.048 kOhm, 4.096 kOhm and 8.192 kOhm. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes approximately for every 5 sec.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Set Resistance: 1.024 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 1024 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Set Resistance: 2.048 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 2048 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Set Resistance: 4.096 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 4096 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Set Resistance: 8.192 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 8192 );
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
