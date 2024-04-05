\mainpage Main Page

---
# DIGI POT 9 click

DIGI POT 9 Click is a compact add-on board used as a digitally controlled potentiometer. This board features the AD5235, a dual-channel, nonvolatile memory, digitally controlled potentiometer from Analog Devices. The AD5235's versatile programming via an SPI-compatible serial interface allows multiple modes of operation and adjustment. The resistor wiper position is determined by the RDAC register contents, which act as a scratchpad register, allowing unlimited changes of resistance settings. The nominal resistance of the RDAC between terminal A and terminal B (RAB) is 250 kΩ with 1024 positions (10-bit resolution).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-pot-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the DIGIPOT9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGIPOT9 Click driver.

#### Standard key functions :

- `digipot9_cfg_setup` Config Object Initialization function.
```c
void digipot9_cfg_setup ( digipot9_cfg_t *cfg );
```

- `digipot9_init` Initialization function.
```c
DIGIPOT9_RETVAL digipot9_init ( digipot9_t *ctx, digipot9_cfg_t *cfg );
```

- `digipot9_default_cfg` Click Default Configuration function.
```c
void digipot9_default_cfg ( digipot9_t *ctx );
```

#### Example key functions :

- `digipot9_generic_write` This function writes two data bytes to the selected command and address by using SPI serial interface.
```c
err_t digipot9_generic_write ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t data_in );
```

- `digipot9_generic_read` This function reads two data bytes from the selected command and address by using SPI serial interface.
```c
err_t digipot9_generic_read ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t *data_out );
```

- `digipot9_set_wiper_1` This function sets wiper 1 to desired value.
```c
err_t digipot9_set_wiper_1 ( digipot9_t *ctx, uint16_t data_in );
```

## Example Description

> This example demonstrates the use of DIGI POT 9 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    digipot9_cfg_t digipot9_cfg;  /**< Click config object. */

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

    digipot9_cfg_setup( &digipot9_cfg );
    DIGIPOT9_MAP_MIKROBUS( digipot9_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot9_init( &digipot9, &digipot9_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    digipot9_default_cfg ( &digipot9 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Iterates through the entire wiper range and sets both wipers to 
> the iterator value once per second. 
> The current wiper position will be displayed on the USB UART.

```c

void application_task ( void )
{
    for ( uint16_t cnt = DIGIPOT9_WIPER_ZERO_SCALE; cnt <= DIGIPOT9_WIPER_FULL_SCALE; cnt += 50 )
    {
        digipot9_set_wiper_1 ( &digipot9, cnt );
        digipot9_set_wiper_2 ( &digipot9, cnt );
        log_printf( &logger, " * Wipers position set to %u *\r\n", cnt );
        
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT9

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
