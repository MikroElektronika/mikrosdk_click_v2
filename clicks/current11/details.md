
---
# Current 11 Click

> Current 11 Click is a compact add-on board for industrial and commercial current-sensing applications. This board features the ACS37600K (ACS37600KOKATN-006B5-C), a programmable linear Hall-effect sensor IC from Allegro Microsystems. This sensor features a chopper-stabilized Hall-effect front-end for precise magnetic flux detection, with a sensitivity of 6mV/G and a bidirectional operating range of ±333G.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/current-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Current 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current 11 Click driver.

#### Standard key functions :

- `current11_cfg_setup` Config Object Initialization function.
```c
void current11_cfg_setup ( current11_cfg_t *cfg );
```

- `current11_init` Initialization function.
```c
err_t current11_init ( current11_t *ctx, current11_cfg_t *cfg );
```

#### Example key functions :

- `current11_set_vref` This function sets the voltage reference for Current 11 Click driver.
```c
err_t current11_set_vref ( current11_t *ctx, float vref );
```

- `current11_calibrate_offset` This function calibrates the zero current offset value.
```c
err_t current11_calibrate_offset ( current11_t *ctx );
```

- `current11_read_current` This function reads the input current level [A] based on CURRENT11_NUM_CONVERSIONS of voltage measurements.
```c
err_t current11_read_current ( current11_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Current 11 Click board by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and calibrates the zero current offset.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current11_cfg_t current11_cfg;  /**< Click config object. */

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
    current11_cfg_setup( &current11_cfg );
    CURRENT11_MAP_MIKROBUS( current11_cfg, MIKROBUS_1 );
    err_t init_flag = current11_init( &current11, &current11_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( CURRENT11_ERROR == current11_calibrate_offset ( &current11 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Calibration DONE.\r\n" );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the input current measurements and displays the results on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float current = 0;
    if ( CURRENT11_OK == current11_read_current ( &current11, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
        Delay_ms ( 1000 );
    }
}

```

## Note

> For better accuracy, set the voltage reference by using the current11_set_vref function,
increase the number of conversions by modifying the CURRENT11_NUM_CONVERSIONS macro, 
and adjust the CURRENT11_COUPLING_FACTOR_G_A value.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
