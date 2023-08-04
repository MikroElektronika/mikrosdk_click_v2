\mainpage Main Page

---
# Smoke 2 click

> Smoke 2 Click is a compact add-on board that contains the most efficient version of the smoke detector. This board features the ADPD188BI, a complete photometric system for smoke detection using optical dual-wavelength technology from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smoke2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/smoke-2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Smoke2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smoke2 Click driver.

#### Standard key functions :

- `smoke2_cfg_setup` Config Object Initialization function.
```c
void smoke2_cfg_setup ( smoke2_cfg_t *cfg );
```

- `smoke2_init` Initialization function.
```c
err_t smoke2_init ( smoke2_t *ctx, smoke2_cfg_t *cfg );
```

- `smoke2_default_cfg` Click Default Configuration function.
```c
err_t smoke2_default_cfg ( smoke2_t *ctx );
```

#### Example key functions :

- `smoke2_get_int_pin` This function eget state of int pin of Smoke 2 click board.
```c
uint8_t smoke2_get_int_pin ( smoke2_t *ctx );
```

- `smoke2_write_data` This function is generic for writing data to register of Smoke 2 click board.
```c
void smoke2_write_data( smoke2_t *ctx, uint8_t reg, uint16_t tx_data );
```

- `smoke2_read_data` This function is generic for reading data from registar of Smoke 2 click board.
```c
uint16_t smoke2_read_data( smoke2_t *ctx, uint8_t reg );
```

## Example Description

> This example is made to see how Smoke 2 clicks work. The purpose of this example is that, depending on the way we choose, 
it collects data from the external environment about smoke, processes it, and prints it via the UART terminal.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules, additional pins, Mapping pins and configures device for measurement.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    smoke2_cfg_t smoke2_cfg;      /**< Click config object. */
    
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
    smoke2_cfg_setup( &smoke2_cfg );
    SMOKE2_MAP_MIKROBUS( smoke2_cfg, MIKROBUS_1 );
    err_t init_flag  = smoke2_init( &smoke2, &smoke2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    smoke2_soft_reset( &smoke2 );
    smoke2_set_mode( &smoke2, SMOKE2_MODE_IDLE );

    uint16_t devid = smoke2_read_data( &smoke2, SMOKE2_REG_DEVID );
    log_printf( &logger, ">> ID:  0x%.2X\r\n", ( uint16_t ) ( devid & 0xFF ) );  
    log_printf( &logger, ">> REV: 0x%.2X\r\n", ( uint16_t ) ( ( devid >> 8 ) & 0xFF ) );
    Delay_ms( 1000 );
    
    log_printf( &logger, ">> Configuration <<\r\n" );
    smoke2_default_cfg( &smoke2 ); 
    Delay_ms( 1000 ); 
    
#if ( EXAMPLE_MODE == EXAMPLE_MODE_SMOKE )
    log_printf( &logger, ">> SMOKE MODE <<\r\n" );
    log_printf( &logger, ">> Calibration <<\r\n" );
    uint16_t calib_data = smoke2_smoke_calibration( &smoke2, 500 );
    log_printf( &logger, ">> Calibration data: %u\r\n", calib_data );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_PROXIMITY )
    log_printf( &logger, ">> PROXIMITY MODE <<\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Example shows module working depending on example mode. We can choose between: EXAMPLE_MODE_PROXIMITY and EXAMPLE_MODE_SMOKE.

```c

void application_task ( void ) 
{
#if ( EXAMPLE_MODE == EXAMPLE_MODE_SMOKE )
    smoke_example( &smoke2 );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_PROXIMITY )
    proximity_example( );
#endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Smoke2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
