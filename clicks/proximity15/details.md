
---
# Proximity 15 Click

> Proximity 15 Click is a compact add-on board that contains a close-range proximity sensing solution. This board features the VL53L1, a state-of-the-art, Time-of-Flight (ToF), a laser-ranging miniature sensor from STMicroelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-15-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity15 Click driver.

#### Standard key functions :

- `proximity15_cfg_setup` Config Object Initialization function.
```c
void proximity15_cfg_setup ( proximity15_cfg_t *cfg );
```

- `proximity15_init` Initialization function.
```c
err_t proximity15_init ( proximity15_t *ctx, proximity15_cfg_t *cfg );
```

- `proximity15_default_cfg` Click Default Configuration function.
```c
err_t proximity15_default_cfg ( proximity15_t *ctx );
```

#### Example key functions :

- `proximity15_get_distance` This function waits for the data ready, then reads the distance measured by the sensor in milimeters and clears interrupts.
```c
err_t proximity15_get_distance ( proximity15_t *ctx, uint16_t *distance );
```

- `proximity15_set_inter_measurement_period` This function programs the inter measurement period in miliseconds.
```c
err_t proximity15_set_inter_measurement_period ( proximity15_t *ctx, uint16_t time_ms );
```

- `proximity15_set_timing_budget` This function programs the timing budget in miliseconds.
```c
err_t proximity15_set_timing_budget ( proximity15_t *ctx, proximity15_timing_budget_t time );
```

## Example Description

> This example demonstrates the use of Proximity 15 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which 
enables the sensor and sets it to long distance mode with 50ms timing budget and 100ms inter measurement periods.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proximity15_cfg_t proximity15_cfg;  /**< Click config object. */

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
    proximity15_cfg_setup( &proximity15_cfg );
    PROXIMITY15_MAP_MIKROBUS( proximity15_cfg, MIKROBUS_1 );
    err_t init_flag = proximity15_init( &proximity15, &proximity15_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    init_flag = proximity15_default_cfg ( &proximity15 );
    if ( PROXIMITY15_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the distance measured by the sensor in milimeters and displays the value on the USB UART approximately every 100ms.

```c

void application_task ( void )
{
    uint16_t distance = 0;
    
    if ( PROXIMITY15_OK == proximity15_get_distance ( &proximity15, &distance ) )
    {
        log_printf( &logger, " Distance(mm): %u\r\n\n", distance );
    }
}

```

## Note

> In order to measure longer distance, increase the timing budget and inter measurement periods.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
