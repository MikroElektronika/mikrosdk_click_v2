
---
# Current Sens 2 click

> Current Sens 2 Click is a compact add-on board designed for precise current measurements in industrial applications. This board features the HO 10-P, an AC/DC current transducer from LEM USA. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/currentsens2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-sens-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : ADC type


# Software Support

We provide a library for the Current Sens 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current Sens 2 Click driver.

#### Standard key functions :

- `currentsens2_cfg_setup` Config Object Initialization function.
```c
void currentsens2_cfg_setup ( currentsens2_cfg_t *cfg );
```

- `currentsens2_init` Initialization function.
```c
err_t currentsens2_init ( currentsens2_t *ctx, currentsens2_cfg_t *cfg );
```

#### Example key functions :

- `currentsens2_get_int_pin` Current Sens 2 get int pin state function.
```c
uint8_t currentsens2_get_int_pin ( currentsens2_t *ctx );
```

- `currentsens2_tare` Current Sens 2 tare function.
```c
err_t currentsens2_tare ( currentsens2_t *ctx );
```

- `currentsens2_get_current` Current Sens 2 read current function.
```c
err_t currentsens2_get_current ( currentsens2_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Current Sens 2 click board by reading and
  displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentsens2_cfg_t currentsens2_cfg;  /**< Click config object. */

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
    currentsens2_cfg_setup( &currentsens2_cfg );
    CURRENTSENS2_MAP_MIKROBUS( currentsens2_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == currentsens2_init( &currentsens2, &currentsens2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove Click from the electrical circuit \r\n" );
    Delay_ms( 1000 );
    if ( CURRENTSENS2_ERROR == currentsens2_tare ( &currentsens2 ) )
    {
        log_error( &logger, " Click tare error." );
        for ( ; ; );
    }

    currentsens2_set_prim_turn_no( &currentsens2, CURRENTSENS2_NUM_OF_PASSES_1 );

    log_printf( &logger, " Connect Click to the electrical circuit \r\n" );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the input current measurements and displays the results on the USB UART
  approximately once per second.

```c

void application_task ( void ) 
{
    float current = 0;
    if ( CURRENTSENS2_OK == currentsens2_get_current ( &currentsens2, &current ) ) 
    {
        log_printf( &logger, " Current : %.2f[A]\r\n\n", current );
        Delay_ms( 1000 );
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentSens2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
