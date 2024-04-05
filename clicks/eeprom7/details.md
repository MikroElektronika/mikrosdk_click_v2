
---
# EEPROM 7 click

EEPROM 7 Click is a compact add-on board that contains the highest-density memory solution. This board feature the 25CSM04, a 4-Mbit SPI Serial EEPROM with a 128-bit serial number and enhanced write protection mode from Microchip. Internally organized as 2,048 pages of 256 bytes each, the 25CSM04 comes up with the compatible SPI serial interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the EEPROM7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM7 Click driver.

#### Standard key functions :

- `eeprom7_cfg_setup` Config Object Initialization function.
```c
void eeprom7_cfg_setup ( eeprom7_cfg_t *cfg );
```

- `eeprom7_init` Initialization function.
```c
err_t eeprom7_init ( eeprom7_t *ctx, eeprom7_cfg_t *cfg );
```

- `eeprom7_default_cfg` Click Default Configuration function.
```c
err_t eeprom7_default_cfg ( eeprom7_t *ctx );
```

#### Example key functions :

- `eeprom7_sw_reset` Software device reset function.
```c
void eeprom7_sw_reset ( eeprom7_t *ctx );
```

- `eeprom7_write_memory` Write EEPROM memory function.
```c
void eeprom7_write_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_tx_data, uint8_t n_bytes );
```

- `eeprom7_read_memory` Read EEPROM memory function.
```c
void eeprom7_read_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_rx_data, uint8_t n_bytes);
```

## Example Description

> This is an example that demonstrates the use of the EEPROM 7 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - SPI, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom7_cfg_t eeprom7_cfg;  /**< Click config object. */

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

    eeprom7_cfg_setup( &eeprom7_cfg );
    EEPROM7_MAP_MIKROBUS( eeprom7_cfg, MIKROBUS_1 );
    err_t init_flag  = eeprom7_init( &eeprom7, &eeprom7_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    eeprom7_default_cfg ( &eeprom7 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In this example, we write and then read data from EEPROM memory. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes approximately for every 3 sec.

```c

void application_task ( void ) {
    eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WREN );
    Delay_ms ( 100 );
    
    eeprom7_write_memory( &eeprom7, 0x00001234, &demo_data[ 0 ], 9 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " > Write data: %s", demo_data );

    while ( eeprom7_is_device_ready( &eeprom7 ) == EEPROM7_DEVICE_IS_READY ) {
        check_status = eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WRBP );
        Delay_ms ( 1 );
    }

    eeprom7_read_memory( &eeprom7, 0x00001234, &read_data[ 0 ], 9 );
    Delay_ms ( 100 );
    log_printf( &logger, " > Read data: %s", read_data );

    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
