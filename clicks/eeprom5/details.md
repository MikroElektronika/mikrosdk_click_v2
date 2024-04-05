
---
# EEPROM 5 click

EEPROM 5 Click is a compact add-on board that contains the highest-density memory solution. This board features the M95M04, the 4Mbit electrically erasable programmable memory organized as 524288 x 8 bits accessed through the SPI interface from STMicroelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom_5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the EEPROM5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM5 Click driver.

#### Standard key functions :

- `eeprom5_cfg_setup` Config Object Initialization function.
```c
void eeprom5_cfg_setup ( eeprom5_cfg_t *cfg );
```

- `eeprom5_init` Initialization function.
```c
err_t eeprom5_init ( eeprom5_t *ctx, eeprom5_cfg_t *cfg );
```

#### Example key functions :

- `eeprom5_set_hold` Enable hold operation function.
```c
void eeprom5_set_hold ( eeprom5_t *ctx, uint8_t en_hold );
```

- `eeprom5_read_memory` Read EEPROM memory function.
```c
void eeprom5_read_memory ( eeprom5_t *ctx, uint32_t addr, uint8_t *p_rx_data, uint8_t n_bytes );
```

- `eeprom5_write_memory` Write EEPROM memory function.
```c
void eeprom5_write_memory ( eeprom5_t *ctx, uint32_t addr, uint8_t *p_tx_data, uint8_t n_bytes );
```

## Example Description

> This is an example that demonstrates the use of the EEPROM 5 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables SPI, also write log.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom5_cfg_t eeprom5_cfg;  /**< Click config object. */

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
    eeprom5_cfg_setup( &eeprom5_cfg );
    EEPROM5_MAP_MIKROBUS( eeprom5_cfg, MIKROBUS_1 );
    err_t init_flag  = eeprom5_init( &eeprom5, &eeprom5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    log_printf( &logger, " Disabling HOLD \r\n" );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    eeprom5_set_hold( &eeprom5, EEPROM5_HOLD_DISABLE );
    Delay_ms ( 100 );
    log_printf( &logger, " Disabling Write Protection \r\n" );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    eeprom5_set_write_protect( &eeprom5, EEPROM5_WRITE_PROTECT_DISABLE );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
}

```

### Application Task

> In this example, we write and then read data from EEPROM memory. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes approximately for every 5 sec.

```c

void application_task ( void ) 
{
    eeprom5_enable_memory_write( &eeprom5, EEPROM5_WRITE_MEMORY_ENABLE );
    Delay_ms ( 10 );
    
    eeprom5_write_memory( &eeprom5, 14, demo_data, 9 );
    log_printf( &logger, " Write data : %s ", demo_data );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    Delay_ms ( 100 );
    
    eeprom5_read_memory( &eeprom5, 14, read_data, 9 );
    log_printf( &logger, " Read data : %s ", read_data );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM5

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
