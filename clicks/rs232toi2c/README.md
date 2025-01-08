
---
# RS232 to I2C Click

> [RS232 to I2C Click](https://www.mikroe.com/?pid_product=MIKROE-5056) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5056&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of an RS232 to I2C Click board by showing the communication between the two Click board configured as a receiver and transmitter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RS232toI2C

### Example Key Functions

- `rs232toi2c_cfg_setup` Config Object Initialization function.
```c
void rs232toi2c_cfg_setup ( rs232toi2c_cfg_t *cfg );
```

- `rs232toi2c_init` Initialization function.
```c
err_t rs232toi2c_init ( rs232toi2c_t *ctx, rs232toi2c_cfg_t *cfg );
```

- `rs232toi2c_default_cfg` Click Default Configuration function.
```c
err_t rs232toi2c_default_cfg ( rs232toi2c_t *ctx );
```

- `rs232toi2c_write_tx_fifo` This function writes a desired number of data bytes to the TX fifo.
```c
err_t rs232toi2c_write_tx_fifo ( rs232toi2c_t *ctx, uint8_t *data_in, uint8_t data_len );
```

- `rs232toi2c_read_rx_fifo` This function reads all data from RX fifo.
```c
err_t rs232toi2c_read_rx_fifo ( rs232toi2c_t *ctx, uint8_t *data_out, uint8_t *data_len );
```

- `rs232toi2c_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t rs232toi2c_get_int_pin ( rs232toi2c_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the default UART configuration with 9600 baud rate.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs232toi2c_cfg_t rs232toi2c_cfg;  /**< Click config object. */

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
    rs232toi2c_cfg_setup( &rs232toi2c_cfg );
    RS232TOI2C_MAP_MIKROBUS( rs232toi2c_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rs232toi2c_init( &rs232toi2c, &rs232toi2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RS232TOI2C_ERROR == rs232toi2c_default_cfg ( &rs232toi2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t system_version;
    if ( RS232TOI2C_OK == rs232toi2c_read_system_version ( &rs232toi2c, &system_version ) )
    {
        log_printf ( &logger, " System Version: 0x%.6LX\r\n", system_version );
    }
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data and sends an adequate response back or sends the desired message and waits for a response every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    if ( RS232TOI2C_OK == rs232toi2c_write_tx_fifo( &rs232toi2c, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
        uint16_t timeout_cnt = 5000;
        // wait for an RX interrupt
        while ( rs232toi2c_get_int_pin ( &rs232toi2c ) && timeout_cnt )
        {
            Delay_ms ( 1 );
            timeout_cnt--;
        }
        if ( timeout_cnt )
        {
            uint8_t data_buf[ 256 ] = { 0 };
            uint8_t data_len = 0;
            if ( RS232TOI2C_OK == rs232toi2c_read_rx_fifo( &rs232toi2c, data_buf, &data_len ) )
            {
                log_printf( &logger, " Response: " );
                for ( uint8_t cnt = 0; cnt < data_len; cnt++ )
                {
                    log_printf( &logger, "%c", data_buf[ cnt ] );
                }
            }
        }
        else
        {
            log_error ( &logger, "TIMEOUT - no response received" );
        }
        log_printf( &logger, "\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#else
    // wait for an RX interrupt
    while ( rs232toi2c_get_int_pin ( &rs232toi2c ) );
    
    uint8_t data_buf[ 256 ] = { 0 };
    uint8_t data_len = 0;
    if ( RS232TOI2C_OK == rs232toi2c_read_rx_fifo( &rs232toi2c, data_buf, &data_len ) )
    {
        log_printf( &logger, " A new message has received: \"" );
        for ( uint8_t cnt = 0; cnt < data_len; cnt++ )
        {
            log_printf( &logger, "%c", data_buf[ cnt ] );
        }
        log_printf( &logger, "\"\r\n" );
        if ( strstr ( data_buf, DEMO_TEXT_MESSAGE ) )
        {
            if ( RS232TOI2C_OK == rs232toi2c_write_tx_fifo( &rs232toi2c, RESPONSE_OK, strlen( RESPONSE_OK ) ) )
            {
                log_printf( &logger, " Response \"%s\" has been sent to the sender!\r\n\n", ( char * ) RESPONSE_OK );
            }
        }
        else
        {
            if ( RS232TOI2C_OK == rs232toi2c_write_tx_fifo( &rs232toi2c, RESPONSE_ERROR, strlen( RESPONSE_ERROR ) ) )
            {
                log_printf( &logger, " Response \"%s\" has been sent to the sender!\r\n\n", ( char * ) RESPONSE_ERROR );
            }
        }
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
