\mainpage Main Page

---
# RS232 to I2C click

> RS232 to I2C Click is a compact add-on board representing a universal usable RS232 to I2C converter. This board features the ZDU0110RFX, a bridge between a UART port and an I2C bus from Zilog, which at the same time represents the connection between the MCU and the RS232 line driver and receiver, the MAX3232. The ZDU0110RFX provides full-duplex asynchronous communications with a 128 byte FIFO buffer, of which 64 bytes each are allocated to receive and transmit operations. It also contains a 4kbit EEPROM and GPIO with programmable interrupt capability; programmable interrupts and interrupt lines for UART and GPIO notifications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs232toi2c_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs232-to-i2c-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the RS232 to I2C Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RS232 to I2C Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of an RS232 to I2C click board by showing the communication between the two click board configured as a receiver and transmitter.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the default UART configuration with 9600 baud rate.

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RS232toI2C

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
