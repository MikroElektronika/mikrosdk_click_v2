\mainpage Main Page

---
# Hall Current 19 Click

> Hall Current 19 Click is a compact add-on board designed for precise current sensing in various applications. This board features the CZ3AG2, a coreless current sensor from AKM Semiconductor. The CZ3AG2 offers high-accuracy and high-speed current sensing using Hall sensor technology, with features like stray magnetic field reduction and dual overcurrent detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/hall-current-19-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : ADC type


# Software Support

We provide a library for the Hall Current 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Current 19 Click driver.

#### Standard key functions :

- `hallcurrent19_cfg_setup` Config Object Initialization function.
```c
void hallcurrent19_cfg_setup ( hallcurrent19_cfg_t *cfg );
```

- `hallcurrent19_init` Initialization function.
```c
err_t hallcurrent19_init ( hallcurrent19_t *ctx, hallcurrent19_cfg_t *cfg );
```

#### Example key functions :

- `hallcurrent19_get_oc2` This function is used to get state of the overcurrent 2 detection of the Hall Current 19 Click board.
```c
uint8_t hallcurrent19_get_oc2 ( hallcurrent19_t *ctx );
```

- `hallcurrent19_set_zero_ref` This function sets the zero voltage reference of the Hall Current 19 Click board.
```c
err_t hallcurrent19_set_zero_ref ( hallcurrent19_t *ctx );
```

- `hallcurrent19_get_current` This function reads and calculate input current value of the Hall Current 19 Click board.
```c
err_t hallcurrent19_get_current ( hallcurrent19_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Hall Current 19 Click board
  by reading and displaying the current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and set the zero voltage reference.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent19_cfg_t hallcurrent19_cfg;  /**< Click config object. */

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
    hallcurrent19_cfg_setup( &hallcurrent19_cfg );
    HALLCURRENT19_MAP_MIKROBUS( hallcurrent19_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == hallcurrent19_init( &hallcurrent19, &hallcurrent19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Turn off the load current in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( HALLCURRENT19_OK == hallcurrent19_set_zero_ref( &hallcurrent19 ) )
    {
        log_printf( &logger, " Process complete!\r\n");
    }
    else
    {
        log_error( &logger, " Zero reference." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> The demo application reads the current measurements [A] and displays the results.
  Results are being sent to the UART Terminal, where you can track their changes.

```c

void application_task ( void ) 
{
    float voltage = 0;
    if ( HALLCURRENT19_OK == hallcurrent19_get_current ( &hallcurrent19, &voltage ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", voltage );
        Delay_ms ( 1000 );
    }
    if ( HALLCURRENT19_OCD_ACTIVE == hallcurrent19_get_oc1( &hallcurrent19 ) )
    {
        log_printf( &logger, " Current over 7A \r\n" );
    }
    if ( HALLCURRENT19_OCD_ACTIVE == hallcurrent19_get_oc2( &hallcurrent19 ) )
    {
        log_printf( &logger, " Current over 17.5A \r\n" );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
