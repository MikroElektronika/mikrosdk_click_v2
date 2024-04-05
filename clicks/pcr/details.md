
---
# PCR click

> PCR Click is a compact add-on board that allows you to use a pulsed coherent radar (PCR) in your application. This board features the XM125, the Entry+ PCR module from Acconeer. The XM125 uses an Acconeer A121 pulsed coherent radar system based on a patented PCR technology with picosecond time resolution. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pcr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pcr-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the PCR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PCR Click driver.

#### Standard key functions :

- `pcr_cfg_setup` Config Object Initialization function.
```c
void pcr_cfg_setup ( pcr_cfg_t *cfg );
```

- `pcr_init` Initialization function.
```c
err_t pcr_init ( pcr_t *ctx, pcr_cfg_t *cfg );
```

- `pcr_default_cfg` Click Default Configuration function.
```c
err_t pcr_default_cfg ( pcr_t *ctx );
```

#### Example key functions :

- `pcr_write_reg` PCR register writing function.
```c
err_t pcr_write_reg ( pcr_t *ctx, uint16_t reg, uint32_t data_in );
```

- `pcr_check_if_busy` PCR check if device is busy function.
```c
err_t pcr_check_if_busy ( pcr_t *ctx );
```

- `pcr_get_distance` PCR read distance function.
```c
err_t pcr_get_distance ( pcr_t *ctx, uint32_t *distance_data );
```

## Example Description

> This example demonstrates the use of PCR click board by 
  reading distance between click board and object. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pcr_cfg_t pcr_cfg;  /**< Click config object. */

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
    pcr_cfg_setup( &pcr_cfg );
    PCR_MAP_MIKROBUS( pcr_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pcr_init( &pcr, &pcr_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PCR_ERROR == pcr_default_cfg ( &pcr ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reading distance between click board and object every 2 seconds and logging it on UART terminal.

```c
void application_task ( void ) 
{
    uint32_t distance_data = 0;

    pcr_get_distance ( &pcr, &distance_data );
    log_printf( &logger, " Distance: %lu mm \r\n", distance_data );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PCR

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
