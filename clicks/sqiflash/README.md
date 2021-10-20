\mainpage Main Page

---
# SQI FLASH click

> SQI FLASH click is based on the SST26VF064B, a 64 Mbit Serial Quad I/O flash device from Microchip. The chip utilizes 4-bit multiplexed I/O serial interface to boost the performance. The click is a very fast solid-state, non-volatile data storage medium, that can be electrically erased and reprogrammed.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sqiflash_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/sqi-flash-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the SqiFlash Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SqiFlash Click driver.

#### Standard key functions :

- `sqiflash_cfg_setup` Config Object Initialization function.
```c
void sqiflash_cfg_setup ( sqiflash_cfg_t *cfg );
```

- `sqiflash_init` Initialization function.
```c
err_t sqiflash_init ( sqiflash_t *ctx, sqiflash_cfg_t *cfg );
```

#### Example key functions :

- `sqiflash_write_generic` SQI FLASH Write.
```c
void sqiflash_write_generic( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );
```

- `sqiflash_read_generic` SQI FLASH Read.
```c
void sqiflash_read_generic( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );
```

- `sqiflash_global_block_unlock` SQI FLASH Global Block Unlock.
```c
void sqiflash_global_block_unlock( sqiflash_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the SQI FLASH Click board.

**The demo application is composed of two sections :**

### Application Init

> SQI FASH Driver Initialization, initializes the click by setting mikroBUS to
> approprieate logic levels, performing global block unlock and chip erase functions,
> reads manufacturer ID, memory type and device ID and logs it on USB UART teminal.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    sqiflash_cfg_t sqiflash_cfg;  /**< Click config object. */

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

    sqiflash_cfg_setup( &sqiflash_cfg );
    SQIFLASH_MAP_MIKROBUS( sqiflash_cfg, MIKROBUS_1 );
    err_t init_flag  = sqiflash_init( &sqiflash, &sqiflash_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 300 );
    sqiflash_global_block_unlock( &sqiflash );
    Delay_ms( 400 );
    sqiflash_chip_erase( &sqiflash );
    Delay_ms( 300 );
    
    device_manufac = sqiflash_device_manufac( &sqiflash );
    log_printf( &logger, "Manufacturer ID: 0x%.2X \r\n", ( uint16_t ) device_manufac );
    device_type = sqiflash_device_type( &sqiflash );
    log_printf( &logger, "Memory Type:     0x%.2X \r\n", ( uint16_t ) device_type );
    device_id = sqiflash_device_id( &sqiflash );
    log_printf( &logger, "Device ID:       0x%.2X \r\n", ( uint16_t ) device_id );
    log_printf( &logger, "--------------------\r\n" );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writing data to click memory and displaying the read data via UART.

```c

void application_task ( void ) {
    log_printf( &logger, "Writing data to flash memory, from address 0x015015:\r\n" );
    log_printf( &logger, "Data written: %s ", wr_data );
    sqiflash_write_generic( &sqiflash, 0x015015, &wr_data[ 0 ], 9 );
    log_printf( &logger, "Reading 9 bytes of flash memory, from address 0x015015:\r\n" );
    sqiflash_read_generic( &sqiflash, 0x015015, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %s ", rd_data );
    log_printf( &logger, "--------------------------------------------------------\r\n" );
    Delay_ms( 2000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SqiFlash

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
