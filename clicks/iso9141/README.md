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

- **Author**        : MikroE Team
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
err_t iso9141_generic_write ( iso9141_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `iso9141_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t iso9141_generic_read ( iso9141_t *ctx, uint8_t *data_buf, uint16_t max_len );
```

## Example Description

> This example demonstrates the use of an ISO 9141 click board by showing the communication between the two click boards.

**The demo application is composed of two sections :**

### Application Init

> Initalizes device and makes an initial log.

```c

void application_init ( void )
{
    iso9141_cfg_t iso9141_cfg;
    log_cfg_t logger_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    log_info( &logger, " Application Init " );
    
    // Click initialization.
    iso9141_cfg_setup( &iso9141_cfg );
    ISO9141_MAP_MIKROBUS( iso9141_cfg, MIKROBUS_1 );
    if ( UART_ERROR == iso9141_init( &iso9141, &iso9141_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
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

> Depending on the selected application mode, it reads all the received data or sends the desired text message once per second.

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    iso9141_generic_write( &iso9141, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == iso9141_generic_read( &iso9141, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
    }
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
