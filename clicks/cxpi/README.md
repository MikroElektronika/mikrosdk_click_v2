
---
# CXPI Click

> [CXPI Click](https://www.mikroe.com/?pid_product=MIKROE-4336) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4336&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This is an example that demonstrates the use of the CXPI Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CXPI

### Example Key Functions

- `cxpi_cfg_setup` Config Object Initialization function.
```c
void cxpi_cfg_setup ( cxpi_cfg_t *cfg );
```

- `cxpi_init` Initialization function.
```c
err_t cxpi_init ( cxpi_t *ctx, cxpi_cfg_t *cfg );
```

- `cxpi_send_command` Send command.
```c
void cxpi_send_command ( cxpi_t *ctx, char *command );
```

- `cxpi_set_pwm_pin_state` Set PWM pin state function.
```c
void cxpi_set_pwm_pin_state ( cxpi_t *ctx, uint8_t pin_state );
```

- `cxpi_set_through_mode` Set through mode function.
```c
void cxpi_set_through_mode ( cxpi_t *ctx );
```

### Application Init

> Initializes UART driver. In addition to this module is placed inside transmitter/receiver working mode cappable of transmission/receive the data.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cxpi_cfg_t cxpi_cfg;  /**< Click config object. */

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

    // Click initialization.

    cxpi_cfg_setup( &cxpi_cfg );
    CXPI_MAP_MIKROBUS( cxpi_cfg, MIKROBUS_1 );
    err_t init_flag  = cxpi_init( &cxpi, &cxpi_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    cxpi_set_through_mode( &cxpi );

#ifdef DEMO_APP_TRANSMITER
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    Delay_ms ( 1000 );
#endif

#ifdef DEMO_APP_RECEIVER 
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif

    log_printf( &logger, "------------------\r\n" );
}
```

### Application Task

> Transmitter/Receiver task depend on uncommented code Receiver logging each received byte to the UART for data logging, while transmitted send messages every 5 seconds.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_RECEIVER 
    cxpi_process( );
    if ( current_rsp_buf > 0 ) {
        log_printf( &logger, "%s", current_rsp_buf );
        cxpi_clear_current_rsp_buf( );
    }
#endif 

#ifdef DEMO_APP_TRANSMITER
    cxpi_send_command( &cxpi, &demo_message[ 0 ] );
    log_printf( &logger, " Sent data : %s",  &demo_message[ 0 ] );
    log_printf( &logger, "------------------\r\n" ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
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
