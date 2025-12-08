
---
# UART I2C SPI 2 Click

> [UART I2C SPI 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6827) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6827&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the UART I2C SPI 2 Click board.
It sends a predefined demo message to both UART0 and UART1 interfaces,
then reads back any received data and logs the results on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UARTI2CSPI2

### Example Key Functions

- `uarti2cspi2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void uarti2cspi2_cfg_setup ( uarti2cspi2_cfg_t *cfg );
```

- `uarti2cspi2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t uarti2cspi2_init ( uarti2cspi2_t *ctx, uarti2cspi2_cfg_t *cfg );
```

- `uarti2cspi2_default_cfg` This function executes a default configuration of UART I2C SPI 2 Click board.
```c
err_t uarti2cspi2_default_cfg ( uarti2cspi2_t *ctx );
```

- `uarti2cspi2_read_reg` This function reads a single byte of data from the selected register address.
```c
err_t uarti2cspi2_read_reg ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `uarti2cspi2_read_data` This function reads a block of data from the receive buffer.
```c
err_t uarti2cspi2_read_data ( uarti2cspi2_t *ctx, uint8_t *data_out, uint8_t len );
```

- `uarti2cspi2_write_data` This function writes a block of data to the transmit buffer.
```c
err_t uarti2cspi2_write_data ( uarti2cspi2_t *ctx, uint8_t *data_in, uint8_t len );
```

### Application Init

> Initializes the logger and UART I2C SPI 2 Click, and applies the default configuration which sets the UART0 to 115200-8N1 and UART1 to 9600-8N1.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uarti2cspi2_cfg_t uarti2cspi2_cfg;  /**< Click config object. */

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
    uarti2cspi2_cfg_setup( &uarti2cspi2_cfg );
    UARTI2CSPI2_MAP_MIKROBUS( uarti2cspi2_cfg, MIKROBUS_1 );
    err_t init_flag = uarti2cspi2_init( &uarti2cspi2, &uarti2cspi2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UARTI2CSPI2_ERROR == uarti2cspi2_default_cfg ( &uarti2cspi2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Alternately selects UART0 and UART1, sends the demo message, reads back data from the RX FIFO, and logs the transmitted and received strings every second.

```c
void application_task ( void )
{
    uint8_t fifo_data[ UARTI2CSPI2_FIFO_LEN ] = { 0 };
    uint8_t fifo_lvl = 0;
    uarti2cspi2_select_uart_0 ( &uarti2cspi2 );
    if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, "U0: ", 4 ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, DEMO_MESSAGE, strlen ( DEMO_MESSAGE ) ) )
        {
            log_printf ( &logger, "\r\nSend to U0: %s", DEMO_MESSAGE );
        }
    }
    if ( UARTI2CSPI2_OK == uarti2cspi2_read_reg ( &uarti2cspi2, UARTI2CSPI2_REG_RXFIFOLVL, &fifo_lvl ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_read_data ( &uarti2cspi2, fifo_data, fifo_lvl ) )
        {
            log_printf ( &logger, "Read from U0: %s\r\n", fifo_data );
        }
    }
    uarti2cspi2_select_uart_1 ( &uarti2cspi2 );
    if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, "U1: ", 4 ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, DEMO_MESSAGE, strlen ( DEMO_MESSAGE ) ) )
        {
            log_printf ( &logger, "Send to U1: %s", DEMO_MESSAGE );
        }
    }
    if ( UARTI2CSPI2_OK == uarti2cspi2_read_reg ( &uarti2cspi2, UARTI2CSPI2_REG_RXFIFOLVL, &fifo_lvl ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_read_data ( &uarti2cspi2, fifo_data, fifo_lvl ) )
        {
            log_printf ( &logger, "Read from U1: %s\r\n", fifo_data );
        }
    }
    Delay_ms ( 1000 );
}
```

### Note

> Ensure that the connected devices on UART0 and UART1 are properly configured to communicate at the same baud rate and parameters. 

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
