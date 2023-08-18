
---
# ClickID

> Hardware and software solution based on a secure authenticator device (EEPROM) that enables the hot-plugging of peripheral add-on Click Boards™ to any mikroBUS™ compatible system.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clickid.png" height=300px>
</p>

[Product page](https://www.mikroe.com/clickid)

---


#### Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2023.
- **Type**          : One Wire type


# Software Support

We provide a library for the ClickID
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ClickID driver.

#### Standard key functions :

- `clickid_cfg_setup` Config Object Initialization function.
```c
void clickid_cfg_setup ( clickid_cfg_t *cfg );
```

- `clickid_init` Initialization function.
```c
err_t clickid_init ( clickid_t *ctx, clickid_cfg_t *cfg );
```

#### Example key functions :

- `clickid_check_communication` This function checks the communication by reading the ROM address as well as verifying family code and CRC 8.
```c
err_t clickid_check_communication ( clickid_t *ctx );
```

- `clickid_read_memory` This function reads a desired number of data bytes starting from the selected address of the EEPROM memory using One Wire communication protocol.
```c
err_t clickid_read_memory ( clickid_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );
```

- `clickid_read_information` This function reads the click board information from the permanent data memory.
```c
err_t clickid_read_information ( clickid_t *ctx, clickid_information_t *info );
```

## Example Description

> This example reads the information from ClickID permanent memory.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and checks the communication with the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clickid_cfg_t clickid_cfg;  /**< ClickID config object. */

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

    // ClickID initialization.
    clickid_cfg_setup( &clickid_cfg );
    CLICKID_MAP_MIKROBUS( clickid_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == clickid_init( &clickid, &clickid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLICKID_ERROR == clickid_check_communication ( &clickid ) )
    {
        log_error( &logger, " Communication fail." );
        log_printf( &logger, "Check if the click is attached to the correct " );
        log_printf( &logger, "MIKROBUS socket, and try again.\r\n" );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the information from ClickID permanent manifest every 5 seconds.

```c
void application_task ( void )
{
    clickid_information_t info;
    if ( CLICKID_OK == clickid_read_information ( &clickid, &info ) )
    {
        log_printf ( &logger, "\r\n --- Click info ---\r\n" );
        log_printf ( &logger, " Name: %s\r\n", info.name );
        log_printf ( &logger, " PID: MIKROE-%u\r\n", info.serial );
        log_printf ( &logger, " HW REV.: %u.%.2u\r\n", 
                     ( uint16_t ) info.hw_rev.major, ( uint16_t ) info.hw_rev.minor );
        log_printf ( &logger, " Type: 0x%.4X\r\n", info.type );
        log_printf ( &logger, " Custom: 0x%.2X\r\n", ( uint16_t ) info.custom );
    }
    
    Delay_ms ( 5000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ClickID

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
