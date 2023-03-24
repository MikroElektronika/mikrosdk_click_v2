\mainpage Main Page

---
# DRAM click

> DRAM Click is a compact add-on board representing a dynamic random-access memory solution. This board features the APS6404L-3SQR, 64Mb high-performance SPI/QPI PSRAM memory organized as 8M x 8 bits each from AP Memory. This Pseudo-SRAM device features a high speed, low pin count interface and incorporates a seamless self-managed refresh mechanism to maximize the performance of memory read operation. It has 4 SDR I/O pins and operates in SPI or QPI (quad peripheral interface) mode with frequencies up to 133 MHz.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dram_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dram-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the DRAM Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DRAM Click driver.

#### Standard key functions :

- `dram_cfg_setup` Config Object Initialization function.
```c
void dram_cfg_setup ( dram_cfg_t *cfg );
```

- `dram_init` Initialization function.
```c
err_t dram_init ( dram_t *ctx, dram_cfg_t *cfg );
```

#### Example key functions :

- `dram_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t dram_memory_write ( dram_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );
```

- `dram_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t dram_memory_read ( dram_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

- `dram_memory_read_fast` This function reads a desired number of data bytes starting from the selected memory address performing fast read feature.
```c
err_t dram_memory_read_fast ( dram_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

## Example Description

> This example demonstrates the use of DRAM click board by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, resets the device and checks the communication by reading and verifying the device ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dram_cfg_t dram_cfg;  /**< Click config object. */

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
    dram_cfg_setup( &dram_cfg );
    DRAM_MAP_MIKROBUS( dram_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dram_init( &dram, &dram_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DRAM_ERROR == dram_reset ( &dram ) )
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( DRAM_ERROR == dram_check_communication ( &dram ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is written correctly by reading from the same memory location and displaying the memory content on the USB UART.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( DRAM_OK == dram_memory_write ( &dram, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( DRAM_OK == dram_memory_read ( &dram, STARTING_ADDRESS, 
                                             data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
    }
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( DRAM_OK == dram_memory_write ( &dram, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( DRAM_OK == dram_memory_read_fast ( &dram, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Fast read data : %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DRAM

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
