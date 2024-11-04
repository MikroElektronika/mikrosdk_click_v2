
---
# DIGI POT 8 Click

DIGI POT 8 Click is a compact add-on board used as a digitally controlled potentiometer. This board features the AD5206, 6-channel 256-position digitally controlled variable resistor device from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digi_pot_8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/digi-pot-8-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the DIGIPOT8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGIPOT8 Click driver.

#### Standard key functions :

- `digipot8_cfg_setup` Config Object Initialization function.
```c
void digipot8_cfg_setup ( digipot8_cfg_t *cfg );
```

- `digipot8_init` Initialization function.
```c
DIGIPOT8_RETVAL digipot8_init ( digipot8_t *ctx, digipot8_cfg_t *cfg );
```

#### Example key functions :

- `digipot8_write_data` DIGI POT 8 write data function.
```c
err_t digipot8_write_data ( digipot8_t *ctx, uint8_t reg, uint8_t data_in )
```

- `digipot8_set_wiper_1` DIGI POT 8 set wiper 2 function.
```c
err_t digipot8_set_wiper_1 ( digipot8_t *ctx, uint8_t data_in );
```

- `digipot8_set_wiper_2` DIGI POT 8 set wiper 3 function.
```c
err_t digipot8_set_wiper_2 ( digipot8_t *ctx, uint8_t data_in );
```

## Example Description

> This example demonstrates the use of DIGI POT 8 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot8_cfg_t digipot8_cfg;  /**< Click config object. */

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

    digipot8_cfg_setup( &digipot8_cfg );
    DIGIPOT8_MAP_MIKROBUS( digipot8_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot8_init( &digipot8, &digipot8_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Iterates through the entire wiper range and sets all wipers to 
> the iterator value each second. 
> The current wiper position will be displayed on USB UART.

```c

void application_task ( void )
{
    for ( uint8_t cnt = DIGIPOT8_WIPER_POSITION_MIN; cnt < DIGIPOT8_WIPER_POSITION_MAX; cnt += 5 )
    {
        digipot8_set_wiper_1 ( &digipot8, cnt );
        digipot8_set_wiper_2 ( &digipot8, cnt );
        digipot8_set_wiper_3 ( &digipot8, cnt );
        digipot8_set_wiper_4 ( &digipot8, cnt );
        digipot8_set_wiper_5 ( &digipot8, cnt );
        digipot8_set_wiper_6 ( &digipot8, cnt );
        log_printf( &logger, " * All wipers position set to %d *\r\n", ( uint16_t ) cnt );
        
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
