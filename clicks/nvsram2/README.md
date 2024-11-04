\mainpage Main Page

---
# nvSRAM 2 Click

nvSRAM 2 Click is a compact add-on board that contains the most reliable nonvolatile memory. This board features the CY14B101Q, a 1Mbit nvSRAM organized as 128K words of 8 bits each with a nonvolatile element in each memory cell from Cypress Semiconductor. The embedded nonvolatile elements incorporate the QuantumTrap technology and provide highly reliable nonvolatile storage of data. Data transfer, initiated by the user through SPI commands, from SRAM to the nonvolatile elements takes place automatically at Power-Down. On the other hand, during the Power-Up, data is restored to the SRAM from the nonvolatile memory. This Click board™ is suitable for all applications that require fast access and high reliability of stored data, and unlimited endurance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nvsram2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nvsram-2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the nvSRAM2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for nvSRAM2 Click driver.

#### Standard key functions :

- `nvsram2_cfg_setup` Config Object Initialization function.
```c
void nvsram2_cfg_setup ( nvsram2_cfg_t *cfg );
```

- `nvsram2_init` Initialization function.
```c
err_t nvsram2_init ( nvsram2_t *ctx, nvsram2_cfg_t *cfg );
```

- `nvsram2_default_cfg` Click Default Configuration function.
```c
err_t nvsram2_default_cfg ( nvsram2_t *ctx );
```

#### Example key functions :

- `nvsram2_hold` The function enables hold operation by setting the state of the HOLD ( PWM ) pin depending on the function argument.
```c
void nvsram2_hold ( nvsram2_t *ctx, uint8_t en_hold );
```

- `nvsram2_set_cmd` The function sends desired command to the CY14B101Q2A memory on nvSRAM 2 Click board.
```c
void nvsram2_set_cmd ( nvsram2_t *ctx, uint8_t cmd );
```

- `nvsram2_read_id` The function performs the device ID read of the CY14B101Q2A memory on nvSRAM 2 Click board.
```c
uint32_t nvsram2_read_id ( nvsram2_t *ctx );
```

## Example Description

> This is an example using nvSRAM 2 Click based on CY14B101Q which is combines a 1-Mbit nvSRAM with a nonvolatile element in each memory cell with serial SPI interface. The memory is organized as 128K words of 8 bits each.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI and UART LOG, sets CS and PWM pins as outputs. Disables hold, sets write enable latch, targets the memory address at 12345 ( 0x00003039 ) for burst write starting point and writes data which is also displayed on the log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;               /**< Logger config object. */
    nvsram2_cfg_t nvsram2_cfg;       /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    nvsram2_cfg_setup( &nvsram2_cfg );
    NVSRAM2_MAP_MIKROBUS( nvsram2_cfg, MIKROBUS_1 );
    err_t init_flag  = nvsram2_init( &nvsram2, &nvsram2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    nvsram2_default_cfg ( &nvsram2 );
    log_info( &logger, " Application Task " );

    memory_addr = 12345;

    nvsram2_burst_write( &nvsram2, memory_addr, demo_data, 9 );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "-> Write data : %s \r\n", demo_data );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the nvSRAM 2 Click board. In this example, the data is read from the targeted memory address. The results are being sent to the Usart Terminal. This task repeats every 5 sec.

```c

void application_task ( void ) {
    nvsram2_burst_read( &nvsram2, memory_addr, rx_data, 9 );
    log_printf( &logger, "-----------------------\r\n"  );
    log_printf( &logger, "<- Read data  : %s \r\n", rx_data );
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
- Click.nvSRAM2

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
