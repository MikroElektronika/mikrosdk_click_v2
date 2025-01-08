
---
# Heart rate 3 Click

> [Heart rate 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2036) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2036&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jova Stajkovic
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application shows reflected red, green and ir values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate3

### Example Key Functions

- `heartrate3_cfg_setup` Config Object Initialization function.
```c
void heartrate3_cfg_setup ( heartrate3_cfg_t *cfg ); 
```

- `heartrate3_init` Initialization function.
```c
err_t heartrate3_init ( heartrate3_t *ctx, heartrate3_cfg_t *cfg );
```

- `heartrate3_default_cfg` Click Default Configuration function.
```c
err_t heartrate3_default_cfg ( heartrate3_t *ctx );
```

- `heartrate3_check_data_ready` Function is used to check data ready flag.
```c
uint8_t heartrate3_check_data_ready ( heartrate3_t *ctx );
```

- `heartrate3_write_data` Function is used to write 32-bit data into register.
```c
err_t heartrate3_write_data ( heartrate3_t *ctx, uint8_t reg_adr, uint32_t wr_data );
```

- `heartrate3_read_24bit` Function is used to read 24-bit value from register.
```c
err_t heartrate3_read_24bit ( heartrate3_t *ctx, uint8_t reg_adr, uint32_t *data_out );
```

### Application Init

> Initalizes Click driver, resets the device, applies default settings and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate3_cfg_t heartrate3_cfg;

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
    heartrate3_cfg_setup( &heartrate3_cfg );
    HEARTRATE3_MAP_MIKROBUS( heartrate3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate3_init( &heartrate3, &heartrate3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "  Heart rate 3 Click  \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
    if ( HEARTRATE3_ERROR == heartrate3_default_cfg ( &heartrate3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, "     Initialised!     \r\n" );
    log_printf( &logger, "----------------------\r\n" );    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of Heart rate 3 board. It is set in default mode,
and reads reflected red, green and ir values and displays the results on USART terminal.

```c
void application_task ( void )
{
    err_t error_flag = HEARTRATE3_OK;
    if ( heartrate3_check_data_ready ( &heartrate3 ) )
    {
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED2VAL, &led_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_ALED2VAL, &aled_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED1VAL, &led_1 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_ALED1VAL, &aled_1 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED2_ALED2VAL, &led_2_aled_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED1_ALED1VAL, &led_1_aled_1 );
        if ( HEARTRATE3_OK == error_flag )
        {
            log_printf( &logger, "%lu;%lu;%lu;%lu;%lu;%lu;\r\n", 
                        led_2, aled_2, led_1, aled_1, led_2_aled_2, led_1_aled_1 );
        }
    }
}
```

### Note

> We recommend using the SerialPlot tool for data visualizing.

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
