\mainpage Main Page

---
# SRAM 3 click

SRAM 3 Click is a compact add-on board that contains a serial non-volatile SRAM with a high storage capacity. This board features the ANV32AA1WDK66, a 1Mb serial SRAM with a non-volatile SONOS storage element included with each memory cell organized as 128k words of 8 bits each from Anvo-System Dresden. The serial SRAM provides fast access & cycle times, high data accuracy, ease of use, and unlimited read & write accessed by a high-speed SPI compatible bus. This Click board™ is suitable to store drive profiles, configurations, and similar data, or for applications such as medical devices, industrial automation (for example, motor control and robotics), smart metering systems, and many others.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sram_3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/sram-3-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the SRAM3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SRAM3 Click driver.

#### Standard key functions :

- `sram3_cfg_setup` Config Object Initialization function.
```c
void sram3_cfg_setup ( sram3_cfg_t *cfg );
```

- `sram3_init` Initialization function.
```c
err_t sram3_init ( sram3_t *ctx, sram3_cfg_t *cfg );
```

#### Example key functions :

- `sram3_enable_write` This function is for enabling writing to memory, status register or user serial.
```c
void sram3_enable_write( sram3_t *ctx );
```

- `sram3_disable_write` Function for disabling writing to memory, status register or user serial.
```c
void sram3_disable_write( sram3_t *ctx );
```

- `sram3_protect_memory` Function which secures part of memory from writing.
```c
void sram3_protect_memory( sram3_t *ctx, uint8_t protect_range );
```

## Example Description

> This is an example that shows the use of SRAM memory, using SRAM 3 click. SRAM 3 click is based on ANV32AA1W, and ANV32AA1W is a 1Mb serial SRAM with a non-volatile SONOS storage element included with each memory cell, 
organized as 128k words of 8 bits each. 
The devices are accessed by a high speed SPI-compatible bus. Specifically in this example, we used the high-speed SPI communication characteristics to write data to a specific registration address and read it.

**The demo application is composed of two sections :**

### Application Init

> Initialization SPI module, logger initalization and click initialization.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;         /**< Logger config object. */
    sram3_cfg_t sram3_cfg;     /**< Click config object. */

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
    sram3_cfg_setup( &sram3_cfg );
    SRAM3_MAP_MIKROBUS( sram3_cfg, MIKROBUS_1 );
    err_t init_flag  = sram3_init( &sram3, &sram3_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    sram3_release_hold( &sram3 );
    Delay_ms( 100 );
}

```

### Application Task

> First, we write the data to the registry address 0x00, and then we read the data from 0x00 address.

```c

void application_task ( void ) {
    char buff_out[ 10 ] = { 0 };
        
    log_printf( &logger, "Writing [ %s ] to memory...\r\n", buf );
    sram3_enable_write( &sram3 );
    sram3_write( &sram3, 0x00, &buf[0], 6 );

    Delay_ms( 100 );
    sram3_read( &sram3, 0x00, &buff_out[0], 6 );
    Delay_ms( 100 );
    log_printf( &logger, "Data read from memory: %s \r\n", buff_out );
    log_printf( &logger, "---------------------------------------------\r\n" );

    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SRAM3

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
