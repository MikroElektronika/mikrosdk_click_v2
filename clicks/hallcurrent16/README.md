\mainpage Main Page

---
# Hall Current 16 Click

> Hall Current 16 Click is a compact add-on board that contains a precise solution for AC/DC current sensing. 
> This board features the ACS37002, a 400kHz high-accuracy current sensor from Allegro Microsystems. 
> This sensor features pin-selectable gains that can be used to configure the device 
> to one of the four defined sensitivities and corresponding current ranges, increasing design flexibility. 
> In addition, an adjustable overcurrent fast fault provides short-circuit detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/hall-current-16-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Hall Current 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Current 16 Click driver.

#### Standard key functions :

- `hallcurrent16_cfg_setup` Config Object Initialization function.
```c
void hallcurrent16_cfg_setup ( hallcurrent16_cfg_t *cfg );
```

- `hallcurrent16_init` Initialization function.
```c
err_t hallcurrent16_init ( hallcurrent16_t *ctx, hallcurrent16_cfg_t *cfg );
```

- `hallcurrent16_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent16_default_cfg ( hallcurrent16_t *ctx );
```

#### Example key functions :

- `hallcurrent16_get_current` Hall Current 16 get current function.
```c
err_t hallcurrent16_get_current ( hallcurrent16_t *ctx, float *current );
```

- `hallcurrent16_get_voltage`  Hall Current 16 get voltage function.
```c
err_t hallcurrent16_get_voltage ( hallcurrent16_t *ctx, float *voltage );
```

- `hallcurrent16_get_ovc_fault` Hall Current 16 get overcurrent fault function.
```c
uint8_t hallcurrent16_get_ovc_fault ( hallcurrent16_t *ctx );
```

## Example Description

> This example demonstrates the use of Hall Current 16 Click board 
> by reading and displaying the current measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent16_cfg_t hallcurrent16_cfg;  /**< Click config object. */

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
    hallcurrent16_cfg_setup( &hallcurrent16_cfg );
    HALLCURRENT16_MAP_MIKROBUS( hallcurrent16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hallcurrent16_init( &hallcurrent16, &hallcurrent16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLCURRENT16_ERROR == hallcurrent16_default_cfg ( &hallcurrent16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The app reads the current measurements [A] and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static float current;
    if ( HALLCURRENT16_OK == hallcurrent16_get_current( &hallcurrent16, &current ) )
    {
        log_printf( &logger, " Current : %.3f A \r\n", current );
    }
    log_printf( &logger, " -------------------- \r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
