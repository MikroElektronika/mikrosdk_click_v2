
---
# UART I2C/SPI Click

> [UART I2C SPI Click](https://www.mikroe.com/?pid_product=MIKROE-3349) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3349&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the UART I2C/SPI Click module. 
> The Click is a I2C/SPI to UART bridge interface. It requires a RS232/485 cable in order to be 
> connected to other Click module or an adapter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UARTI2CSPI

### Example Key Functions

- `uarti2cspi_cfg_setup` Config Object Initialization function. 
```c
void uarti2cspi_cfg_setup ( uarti2cspi_cfg_t *cfg );
``` 
 
- `uarti2cspi_init` Initialization function. 
```c
err_t uarti2cspi_init ( uarti2cspi_t *ctx, uarti2cspi_cfg_t *cfg );
```

- `uarti2cspi_set_reset` Set RST pin state function. 
```c
void uarti2cspi_set_reset ( uarti2cspi_t *ctx, uint8_t state );
```

- `uarti2cspi_advanced_init` Advanced initialization function. 
```c
void uarti2cspi_advanced_init ( uarti2cspi_t *ctx, uint32_t baud_rate, uint8_t data_bits, uint8_t parity_mode, uint8_t stop_bits );
```
 
- `uarti2cspi_uart_write_text` Uart write text function. 
```c
void uarti2cspi_uart_write_text ( uarti2cspi_t *ctx, uint8_t *w_text );
```

- `uarti2cspi_uart_read` This function reads one byte from the Click module. 
```c
uint8_t uarti2cspi_uart_read ( uarti2cspi_t *ctx );
```

### Application Init

> Initializes the driver, configures UART, and enables UART interrupts. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uarti2cspi_cfg_t cfg;

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

    uarti2cspi_cfg_setup( &cfg );
    UARTI2CSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uarti2cspi_init( &uarti2cspi, &cfg );
    Delay_ms ( 1000 );

    uarti2cspi_advanced_init( &uarti2cspi, 115200, UARTI2CSPI_UART_8_BIT_DATA, 
                                                   UARTI2CSPI_UART_NOPARITY,
                                                   UARTI2CSPI_UART_ONE_STOPBIT );
    Delay_ms ( 100 );
    uarti2cspi_interrupt_enable( &uarti2cspi, UARTI2CSPI_RXD_INT_EN | UARTI2CSPI_THR_EMPTY_INT_EN );

    Delay_ms ( 100 );

#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif
    Delay_ms ( 1000 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    uarti2cspi_uart_write_text( &uarti2cspi, TEXT_TO_SEND );
    log_info( &logger, "---- The message has been sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
#ifdef DEMO_APP_RECEIVER
    if ( uarti2cspi_uart_data_ready( &uarti2cspi ) )
    {
        uint8_t rx_data = uarti2cspi_uart_read( &uarti2cspi );
        log_printf( &logger, "%c", rx_data );
    }
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
