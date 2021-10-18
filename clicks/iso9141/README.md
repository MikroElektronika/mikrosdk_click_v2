\mainpage Main Page

---
# ISO 9141 click

> ISO 9141 Click is a compact add-on board that contains a monolithic bus driver with ISO 9141 interface. This board features the L9637, a monolithic integrated circuit containing standard ISO 9141 compatible interface functions from ST Microelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/iso9141_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/iso-9141-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Aug 2021.
- **Type**          : UART type


# Software Support

We provide a library for the ISO9141 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISO9141 Click driver.

#### Standard key functions :

- `iso9141_cfg_setup` Config Object Initialization function.
```c
void iso9141_cfg_setup ( iso9141_cfg_t *cfg );
```

- `iso9141_init` Initialization function.
```c
err_t iso9141_init ( iso9141_t *ctx, iso9141_cfg_t *cfg );
```
#### Example key functions :

- `iso9141_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t iso9141_generic_write ( iso9141_t *ctx, char *data_buf, uint16_t len );
```

- `iso9141_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t iso9141_generic_read ( iso9141_t *ctx, char *data_buf, uint16_t max_len );
```

- `iso9141_send_data` This function send data.
```c
err_t iso9141_send_data ( iso9141_t *ctx, char *tx_data );
```

## Example Description

> This is an example that demonstrates the use of ISO 9141 Click board that contains a monolithic bus driver with ISO 9141 interface.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART used for communication and another UART bus used for data logging.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    iso9141_cfg_t iso9141_cfg;  /**< Click config object. */

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
    log_info( &logger, " \t Application Init \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    log_printf( &logger, "           ISO 9141  click         \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );

    // Click initialization.
    iso9141_cfg_setup( &iso9141_cfg );
    ISO9141_MAP_MIKROBUS( iso9141_cfg, MIKROBUS_1 );
    err_t init_flag  = iso9141_init( &iso9141, &iso9141_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. \r\n" );
        log_info( &logger, " Please, run program again... \r\n" );

        for ( ; ; );
    }

    Delay_ms( 100 );
    log_printf( &logger, "   Set app mode:   \r\n" );
    Delay_ms( 100 );

#ifdef TRANSMIT
    log_printf( &logger, "   Transmit data   \r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 1000 );
#elif defined RECEIVER
    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms( 2000 );
#else
    # error PLEASE SELECT TRANSMIT OR RECEIVE MODE!!!
#endif

    log_printf( &logger, "------------------\r\n" );
}

```

### Application Task

> In this example transmitter/Receiver task depend on uncommented code
Receiver logging each received byte to the UART for data logging, while transmitted send messages every 2 seconds.

```c

void application_task ( void )
{
#ifdef TRANSMIT
    iso9141_send_data( &iso9141, demo_message_data );
    log_printf( &logger, "\r\n Message Sent : %s \r\n", demo_message_data );
    Delay_ms( 2000 );
    log_printf( &logger, "------------------\r\n" );
#elif defined RECEIVER
    iso9141_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        iso9141_clear_app_buf(  );
    }
#else
    # error PLEASE SELECT TRANSMIT OR RECEIVE MODE!!!
#endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISO9141

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
