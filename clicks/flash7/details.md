
---
# Flash 7 Click

Flash 7 Click is a compact add-on board that contains a high-performance memory solution. This board features the GD25LQ16C, a high-performance 16Mbit SPI NOR Flash Memory solution with advanced security features from GigaDevice Semiconductor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/flash-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Flash7 Click driver.

#### Standard key functions :

- `flash7_cfg_setup` Config Object Initialization function.
```c
void flash7_cfg_setup ( flash7_cfg_t *cfg );
```

- `flash7_init` Initialization function.
```c
err_t flash7_init ( flash7_t *ctx, flash7_cfg_t *cfg );
```

- `flash7_default_cfg` Click Default Configuration function.
```c
err_t flash7_default_cfg ( flash7_t *ctx );
```

#### Example key functions :

- `flash7_send_command` Send command function.
```c
void flash7_send_command ( flash7_t *ctx, uint8_t cmd );
```

- `flash7_page_program` Page program function.
```c
uint8_t flash7_page_program ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_tx_data, uint16_t n_bytes );
```

- `flash7_read_memory` Read memory function.
```c
void flash7_read_memory ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint16_t n_bytes );
```

## Example Description

> This is an example that demonstrates the use of the Flash 7 Click board. 

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables SPI, disables write protect and hold, performs whole chip erase, targets the memory address at "4096" for page program starting point and writes data which is also displayed on the log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash7_cfg_t flash7_cfg;  /**< Click config object. */

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

    flash7_cfg_setup( &flash7_cfg );
    FLASH7_MAP_MIKROBUS( flash7_cfg, MIKROBUS_1 );
    err_t init_flag  = flash7_init( &flash7, &flash7_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    flash7_default_cfg ( &flash7 );
    
    log_printf( &logger, " ----------------------- \r\n" );
    log_printf( &logger, " Chip Erase \r\n" );
    flash7_chip_erase( &flash7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    memory_addr = 4096;
    
    log_printf( &logger, " ----------------------- \r\n" );
    log_printf( &logger, " Write data : %s ", demo_data );
    log_printf( &logger, " ----------------------- \r\n" );
    flash7_page_program( &flash7, memory_addr, demo_data, 9 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------- \r\n" );
}

```

### Application Task

> In this example, the data is read from the targeted memory address. The results are being sent to the Usart Terminal. This task repeats every 5 sec.

```c

void application_task ( void ) {
    flash7_read_memory( &flash7, memory_addr, rx_data, 9 );
    log_printf( &logger, " Read data : %s ", rx_data );
    log_printf( &logger, " ----------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash7

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
