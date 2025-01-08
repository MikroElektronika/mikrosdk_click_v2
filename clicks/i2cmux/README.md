
---
# I2C MUX Click

> [I2C MUX Click](https://www.mikroe.com/?pid_product=MIKROE-4048) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4048&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of I2C MUX Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux

### Example Key Functions

- `i2cmux_cfg_setup` Config Object Initialization function. 
```c
void i2cmux_cfg_setup ( i2cmux_cfg_t *cfg );
``` 
 
- `i2cmux_init` Initialization function. 
```c
err_t i2cmux_init ( i2cmux_t *ctx, i2cmux_cfg_t *cfg );
```

- `i2cmux_hw_reset` This function resets I2C MUX 2 Click board by clearing the RST pin for 100ms. 
```c
void i2cmux_hw_reset ( i2cmux_t *ctx );
```
 
- `i2cmux_set_channel` This function sets channel of the I2C MUX Click board. 
```c
void i2cmux_set_channel ( i2cmux_t *ctx, uint8_t channel, uint8_t ch_slave_address );
```

- `i2cmux_generic_read` This function reads data from the desired register. 
```c
void i2cmux_generic_read ( i2cmux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initalizes the driver, preforms hardware reset, then enables channel 0 and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux_cfg_t cfg;

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

    i2cmux_cfg_setup( &cfg );
    I2CMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux_init( &i2cmux, &cfg );
    Delay_ms ( 100 );
    i2cmux_hw_reset( &i2cmux );
    Delay_ms ( 100 );
    
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_0, 0x39 );
    log_printf( &logger, " Please connect a Spectrometer Click to channel 0\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the device ID of a Spectrometer Click (dev ID: 0x24) and displays it on the USB UART each second.

```c
void application_task ( void )
{
    uint8_t rx_data;
    
    i2cmux_generic_read( &i2cmux, 0x92, &rx_data, 1 );
    log_printf( &logger, " The Click device ID is:  0x%.2X\r\n", ( uint16_t ) rx_data );
    log_printf( &logger, "-------------------------------\r\n" );
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
