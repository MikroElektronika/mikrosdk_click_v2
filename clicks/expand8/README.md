\mainpage Main Page

---
# Expand 8 Click

> Expand 8 Click is a compact add-on board that contains a multi-port I/O expander with bi-directional input/outputs. This board features the MAX7317, 10-Port SPI-interfaced I/O expander with overvoltage and hot-insertion protection from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/expand-8-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Expand8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand8 Click driver.

#### Standard key functions :

- `expand8_cfg_setup` Config Object Initialization function.
```c
void expand8_cfg_setup ( expand8_cfg_t *cfg );
```

- `expand8_init` Initialization function.
```c
err_t expand8_init ( expand8_t *ctx, expand8_cfg_t *cfg );
```

#### Example key functions :

- `expand8_write_data` Generic write data function.
```c
void expand8_write_data ( expand8_t *ctx, uint8_t addr, uint8_t tx_data );
```

- `expand8_read_data` Generic read data function.
```c
uint8_t expand8_read_data ( expand8_t *ctx, uint8_t addr );
```

- `expand8_set_port` Set port function.
```c
err_t expand8_set_port ( expand8_t *ctx, uint8_t sel_port, uint8_t sel_imped );
```

## Example Description

> This is an example that demonstrates the use of the Expand 8 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - SPI, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand8_cfg_t expand8_cfg;  /**< Click config object. */

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

    expand8_cfg_setup( &expand8_cfg );
    EXPAND8_MAP_MIKROBUS( expand8_cfg, MIKROBUS_1 );
    err_t init_flag  = expand8_init( &expand8, &expand8_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    select_port = EXPAND8_ADDR_OUT_LVL_PORT_P0;
    Delay_ms ( 100 );
}

```

### Application Task

> This example is working by toggling each of 10 available ports every 1 second.
> Results are being sent to the Uart Terminal where you can track their changes.

```c

void application_task ( void )
{
    expand8_set_port( &expand8, select_port, EXPAND8_SET_LOW_IMPEDANCE );
    
    log_printf( &logger, "     Port P%d - ON\r\n", ( uint16_t ) select_port );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    
    expand8_set_port( &expand8, select_port, EXPAND8_SET_HIGH_IMPEDANCE );
    
    log_printf( &logger, "     Port P%d - OFF\r\n", ( uint16_t ) select_port );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    select_port++;

    if ( select_port > EXPAND8_ADDR_OUT_LVL_PORT_P9 ) {
        select_port = EXPAND8_ADDR_OUT_LVL_PORT_P0;
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand8

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
