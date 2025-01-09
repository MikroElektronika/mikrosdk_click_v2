
---
# Cap Extend Click

> [Cap Extend Click](https://www.mikroe.com/?pid_product=MIKROE-2238) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2238&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases the initialization and configuration of the logger and Click modules
  and later on shows how to read and display the 16-bit button map ( LSB + MSB ). 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapExtend

### Example Key Functions

- `capextend_cfg_setup` Config Object Initialization function. 
```c
void capextend_cfg_setup ( capextend_cfg_t *cfg );
``` 
 
- `capextend_init` Initialization function. 
```c
err_t capextend_init ( capextend_t *ctx, capextend_cfg_t *cfg );
```

- `capextend_default_cfg` Click Default Configuration function. 
```c
void capextend_default_cfg ( capextend_t *ctx );
```

- `capextend_reset` This function does a software reset of the Click module. 
```c
void capextend_reset ( capextend_t *ctx );
```
 
- `capextend_read_msb_buttons` This function reads the MSB button map data. 
```c
int8_t capextend_read_msb_buttons ( capextend_t *ctx );
```

- `capextend_read_lsb_buttons` This function reads the LSB button map data. 
```c
int8_t capextend_read_lsb_buttons ( capextend_t *ctx );
```

### Application Init

> This function initializes and configures the Click and logger modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    capextend_cfg_t cfg;

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

    capextend_cfg_setup( &cfg );
    CAPEXTEND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capextend_init( &capextend, &cfg );
    capextend_reset( &capextend );
}
```

### Application Task

> This function collects map data and displays the 16-bit button map, where each bit that has
  the value 1 represents a button that has been pressed. 

```c
void application_task ( )
{
    uint8_t msb;
    uint8_t lsb;

    msb = capextend_read_msb_buttons( &capextend );
    lsb = capextend_read_lsb_buttons( &capextend );

    // LSB

    log_printf( &logger, " * ---------LSB--------- * \r\n" );
    log_printf( &logger, " * | %d", ( lsb & 0x80 ) >> 7 );
    log_printf( &logger, " %d", ( lsb & 0x40 ) >> 6 );
    log_printf( &logger, " %d", ( lsb & 0x20 ) >> 5 );
    log_printf( &logger, " %d |",( lsb & 0x10 ) >> 4 );
    log_printf( &logger, " %d", ( lsb & 0x08 ) >> 3 );
    log_printf( &logger, " %d", ( lsb & 0x04 ) >> 2 );
    log_printf( &logger, " %d", ( lsb & 0x02 ) >> 1 );
    log_printf( &logger, " %d | * \r\n", lsb & 0x01 );

    // MSB

    log_printf( &logger, " * ---------MSB--------- * \r\n" );
    log_printf( &logger, " * | %d", ( msb & 0x80 ) >> 7 );
    log_printf( &logger, " %d", ( msb & 0x40 ) >> 6 );
    log_printf( &logger, " %d", ( msb & 0x20 ) >> 5 );
    log_printf( &logger, " %d |",( msb & 0x10 ) >> 4 );
    log_printf( &logger, " %d", ( msb & 0x08 ) >> 3 );
    log_printf( &logger, " %d", ( msb & 0x04 ) >> 2 );
    log_printf( &logger, " %d", ( msb & 0x02 ) >> 1 );
    log_printf( &logger, " %d | * \r\n", msb & 0x01 );

    log_printf( &logger, " * ----------------------- * \r\n\r\n" );
    Delay_ms ( 500 );
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
