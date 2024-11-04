\mainpage Main Page

---
# MCP2518FD Click

> MCP2518FD Click is a compact add-on board representing a complete CAN solution used as a control node in a CAN network. This board features the MCP2518FD, an external CAN FD controller with an SPI interface, and a high-speed CAN transceiver, the ATA6563, both from Microchip. The ATA6563, a low-level physical layer IC (PHY), provides a physical connection with the CAN bus itself, while the CAN controller MCP2518FD represents an interface between the MCU and the PHY. It features three operating modes with dedicated fail-safe features, remote wake-up via CAN, and ideally passive behavior when powered off on the CAN bus. This Click board™ is suitable for developing a wide range of automotive diagnostic applications, even on MCUs that do not natively support CAN interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp2518fd_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mcp2518fd-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Oct 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the MCP2518FD Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MCP2518FD Click driver.

#### Standard key functions :

- `mcp2518fd_cfg_setup` Config Object Initialization function.
```c
void mcp2518fd_cfg_setup ( mcp2518fd_cfg_t *cfg );
```

- `mcp2518fd_init` Initialization function.
```c
err_t mcp2518fd_init ( mcp2518fd_t *ctx, mcp2518fd_cfg_t *cfg );
```

- `mcp2518fd_default_cfg` Click Default Configuration function.
```c
err_t mcp2518fd_default_cfg ( mcp2518fd_t *ctx );
```

#### Example key functions :

- `mcp2518fd_transmit_message` Transmits the desired message and checks is message successfully sent.
```c
err_t mcp2518fd_transmit_message ( mcp2518fd_t *ctx, uint8_t *data_in, uint16_t data_len );
```

- `mcp2518fd_receive_message` Receives the message and checks is message successfully received.
```c
err_t mcp2518fd_receive_message ( mcp2518fd_t *ctx, uint8_t *data_out, uint16_t *data_len );
```

- `mcp2518fd_reset` Function for reset using generic transfer
```c
err_t mcp2518fd_reset ( mcp2518fd_t *ctx );
```

## Example Description

> This example demonstrates the use of an MCP2518FD Click board by showing
the communication between the two Click boards configured as a receiver and transmitter.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, performs the Click default configuration and displays the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcp2518fd_cfg_t mcp2518fd_cfg;  /**< Click config object. */

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
    mcp2518fd_cfg_setup( &mcp2518fd_cfg );
    MCP2518FD_MAP_MIKROBUS( mcp2518fd_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mcp2518fd_init( &mcp2518fd, &mcp2518fd_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MCP2518FD_ERROR == mcp2518fd_default_cfg ( &mcp2518fd ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
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

> Depending on the selected mode, it sends a desired message using CAN protocol or reads all the received data and displays them on the USB UART.

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    if ( MCP2518FD_OK == mcp2518fd_transmit_message( &mcp2518fd, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t data_buf[ 256 ] = { 0 };
    uint16_t data_len = 0;
    if ( MCP2518FD_OK == mcp2518fd_receive_message( &mcp2518fd, data_buf, &data_len ) )
    {
        log_printf( &logger, " A new message has received: \"" );
        for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
        {
            log_printf( &logger, "%c", data_buf[ cnt ] );
        }
        log_printf( &logger, "\"\r\n" );
    }
#endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MCP2518FD

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
