
---
# MRAM 3 Click

> MRAM 3 Click is a compact add-on board representing a magneto-resistive random-access memory solution. This board features the AS3001204, 1Mb high-performance serial SPI MRAM memory organized as 128K words of 8 bits each from Avalanche Technology. The MRAM technology is analog to Flash technology with SRAM compatible read/write timings (Persistent SRAM, P-SRAM), where data is always non-volatile. It also has a hardware write-protection feature and performs read and write operations with data retention for one million years and a write endurance of 1014 cycles.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mram3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mram-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the MRAM 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MRAM 3 Click driver.

#### Standard key functions :

- `mram3_cfg_setup` Config Object Initialization function.
```c
void mram3_cfg_setup ( mram3_cfg_t *cfg );
```

- `mram3_init` Initialization function.
```c
err_t mram3_init ( mram3_t *ctx, mram3_cfg_t *cfg );
```

- `mram3_default_cfg` Click Default Configuration function.
```c
err_t mram3_default_cfg ( mram3_t *ctx );
```

#### Example key functions :

- `mram3_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t mram3_memory_write ( mram3_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );
```

- `mram3_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t mram3_memory_read ( mram3_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

- `mram3_aug_memory_write` This function writes a desired number of data bytes starting from the selected augmented memory address.
```c
err_t mram3_aug_memory_write ( mram3_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );
```

## Example Description

> This example demonstrates the use of MRAM 3 Click board by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mram3_cfg_t mram3_cfg;  /**< Click config object. */

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
    mram3_cfg_setup( &mram3_cfg );
    MRAM3_MAP_MIKROBUS( mram3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mram3_init( &mram3, &mram3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MRAM3_ERROR == mram3_default_cfg ( &mram3 ) )
    {
        log_error( &logger, " Default configuration." );
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
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( MRAM3_OK == mram3_memory_write ( &mram3, STARTING_ADDRESS, 
                                          data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( MRAM3_OK == mram3_memory_read ( &mram3, STARTING_ADDRESS, 
                                         data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( MRAM3_OK == mram3_memory_write ( &mram3, STARTING_ADDRESS, 
                                          data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( MRAM3_OK == mram3_memory_read ( &mram3, STARTING_ADDRESS, 
                                         data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5LX: %s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                        data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MRAM3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
