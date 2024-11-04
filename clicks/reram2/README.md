\mainpage Main Page

---
# ReRAM 2 Click

> ReRAM 2 Click is a compact add-on board containing highly reliable resistive random-access memory. This board features the MB85AS8MT, an 8Mbit memory organized as 1,048,576 words of 8 bits from Fujitsu Semiconductor. The MB85AS8MT uses the resistance-variable memory process and silicon-gate CMOS process technologies to form nonvolatile memory cells. This SPI configurable ReRAM can withstand many write cycles (1x106 rewrite operations), has a data retention period greater than ten years, and can read and write to random addresses with very negligible delay. This Click board™ is ideal as a nonvolatile storage media or temporary RAM expansion for storing variables in any embedded application that requires rapid writes and unlimited endurance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/reram2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/reram-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ReRAM 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ReRAM 2 Click driver.

#### Standard key functions :

- `reram2_cfg_setup` Config Object Initialization function.
```c
void reram2_cfg_setup ( reram2_cfg_t *cfg );
```

- `reram2_init` Initialization function.
```c
err_t reram2_init ( reram2_t *ctx, reram2_cfg_t *cfg );
```

- `reram2_default_cfg` Click Default Configuration function.
```c
err_t reram2_default_cfg ( reram2_t *ctx );
```

#### Example key functions :

- `reram2_read_device_id` ReRAM 2 read device ID function.
```c
err_t reram2_read_device_id ( reram2_t *ctx, reram2_dev_id_t *dev_id );
```

- `reram2_write_memory` ReRAM 2 write memory function.
```c
err_t reram2_write_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint16_t len );
```

- `reram2_read_memory` ReRAM 2 read memory function.
```c
err_t reram2_read_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint16_t len );
```

## Example Description

> This library contains API for ReRAM 2 Click driver.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI driver and log UART.
> After driver initialization the app set default settings, 
> performs device wake-up, check Device ID,
> set Write Enable Latch command and write demo_data string ( mikroE ), 
> starting from the selected memory_addr ( 1234 ).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    reram2_cfg_t reram2_cfg;  /**< Click config object. */

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
    reram2_cfg_setup( &reram2_cfg );
    RERAM2_MAP_MIKROBUS( reram2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == reram2_init( &reram2, &reram2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RERAM2_ERROR == reram2_default_cfg ( &reram2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    reram2_wake_up( &reram2 );
    Delay_ms ( 100 );
    
    if ( RERAM2_ERROR == reram2_check_device_id( &reram2 ) )
    {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );
        for( ; ; );
    }

    reram2_send_command( &reram2, RERAM2_CMD_WREN );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    
    memory_addr = 1234;   
    log_printf( &logger, "\r\n  Write data : %s", demo_data );
    reram2_write_memory( &reram2, memory_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}

```

### Application Task

> This is an example that demonstrates the use of the ReRAM 2 Click board™.
> In this example, we read and display a data string, which we have previously written to memory, 
> starting from the selected memory_addr ( 1234 ).
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static char rx_data[ 9 ] = { 0 };
    
    reram2_read_memory( &reram2, memory_addr, &rx_data[ 0 ], 9 );
    log_printf( &logger, "  Read data  : %s", rx_data ); 
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ReRAM2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
