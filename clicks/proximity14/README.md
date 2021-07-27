\mainpage Main Page

---
# Proximity 14 click

<PRVIH_PAR_RECENICA_SA_PRODUCT_PAGE_DA_ISPRATE_CELINU>

<p align="center">
  <img src="CLICK_IMAGE_LINK" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity14 Click driver.

#### Standard key functions :

- `proximity14_cfg_setup` Config Object Initialization function.
```c
void proximity14_cfg_setup ( proximity14_cfg_t *cfg );
```

- `proximity14_init` Initialization function.
```c
err_t proximity14_init ( proximity14_t *ctx, proximity14_cfg_t *cfg );
```

- `proximity14_default_cfg` Click Default Configuration function.
```c
err_t proximity14_default_cfg ( proximity14_t *ctx );
```

#### Example key functions :

- `proximity14_generic_write` Writing function.
```c
err_t proximity14_generic_write ( proximity14_t *ctx, uint8_t reg, uint16_t tx_data );
```

- `proximity14_generic_read` Reading function.
```c
err_t proximity14_generic_read ( proximity14_t *ctx, uint8_t reg, uint16_t *rx_data );
```

- `proximity14_get_int` Get INT pin state.
```c
uint8_t proximity14_get_int ( proximity14_t *ctx );
```

## Example Description

> This example showcases the ability of the device to read proximity 
value. It can be configured to detect objects up to 20cm of distance.

**The demo application is composed of two sections :**

### Application Init

> Initialization of host communication modules (UART, I2C) and 
additional pins. Reads device ID and sets default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity14_cfg_t proximity14_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    proximity14_cfg_setup( &proximity14_cfg );
    PROXIMITY14_MAP_MIKROBUS( proximity14_cfg, MIKROBUS_1 );
    err_t init_flag = proximity14_init( &proximity14, &proximity14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag |= proximity14_default_cfg ( &proximity14 );
    if ( PROXIMITY14_OK != init_flag ) 
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint16_t temp_data = 0;
    init_flag = proximity14_generic_read( &proximity14, PROXIMITY14_REG_ID, &temp_data );
    log_printf( &logger, " > ID: 0x%.4X\r\n", temp_data );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
}

```

### Application Task

> In span of 100ms reads proximity data from device and logs result.

```c

void application_task ( void ) 
{
    uint16_t temp_data = 0;
    proximity14_generic_read( &proximity14, PROXIMITY14_REG_DATA, &temp_data );
    log_printf( &logger, " > Data: %u\r\n", temp_data );
    Delay_ms( 100 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
