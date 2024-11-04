\mainpage Main Page

---
# Hall Current 17 Click

> Hall Current 17 Click is a compact add-on board that contains a precise solution for AC/DC current sensing. This board features the ACS37010, a high-accuracy current sensor from Allegro MicroSystems. The ACS37010 has a high operating bandwidth of 450kHz and a fast response time of 1.3μs response time. It features a highly isolated compact surface-mount package, low internal primary conductor resistance, low sensitivity error, low offset voltage over temperature, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/hall-current-17-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Hall Current 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Current 17 Click driver.

#### Standard key functions :

- `hallcurrent17_cfg_setup` Config Object Initialization function.
```c
void hallcurrent17_cfg_setup ( hallcurrent17_cfg_t *cfg );
```

- `hallcurrent17_init` Initialization function.
```c
err_t hallcurrent17_init ( hallcurrent17_t *ctx, hallcurrent17_cfg_t *cfg );
```

- `hallcurrent17_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent17_default_cfg ( hallcurrent17_t *ctx );
```

#### Example key functions :

- `hallcurrent17_get_current` Hall Current 17 get current function.
```c
err_t hallcurrent17_get_current ( hallcurrent17_t *ctx, float *current );
```

- `hallcurrent17_get_vout` Hall Current 17 get Vout function.
```c
err_t hallcurrent17_get_vout ( hallcurrent17_t *ctx, float *adc_vout );
```

- `hallcurrent17_get_vref` Hall Current 17 get Vref function.
```c
err_t hallcurrent17_get_vref ( hallcurrent17_t *ctx, float *adc_vref );
```

## Example Description

> This example demonstrates the use of Hall Current 17 Click board™ 
> by reading and displaying the current measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent17_cfg_t hallcurrent17_cfg;  /**< Click config object. */

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
    hallcurrent17_cfg_setup( &hallcurrent17_cfg );
    HALLCURRENT17_MAP_MIKROBUS( hallcurrent17_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hallcurrent17_init( &hallcurrent17, &hallcurrent17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLCURRENT17_ERROR == hallcurrent17_default_cfg ( &hallcurrent17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads the current measurements [A] and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static float current = 0.0;
    if ( HALLCURRENT17_OK == hallcurrent17_get_current( &hallcurrent17, &current ) )
    {
        log_printf( &logger, " Current: %.3f [A]\r\n", current );
    }
    log_printf( &logger, " --------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
