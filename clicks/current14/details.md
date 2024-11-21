
---
# Current 14 Click

> Current 14 Click is a compact add-on board designed for precise current measurement without direct contact. This board features the BM14270, a magnetic current sensor IC from ROHM Semiconductor. It uses a coreless, non-contact magnetic impedance (MI) sensor, ensuring low power loss and accurate current detection. It communicates through a 2-wire I2C interface, offering a 14-bit digital output with a measurable magnetic range of ±280μT and sensitivity of 0.045μT/LSB. The board includes an alert interrupt pin (ALR) that indicates data readiness, streamlining real-time data acquisition for the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current14_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/current-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Current 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current 14 Click driver.

#### Standard key functions :

- `current14_cfg_setup` Config Object Initialization function.
```c
void current14_cfg_setup ( current14_cfg_t *cfg );
```

- `current14_init` Initialization function.
```c
err_t current14_init ( current14_t *ctx, current14_cfg_t *cfg );
```

- `current14_default_cfg` Click Default Configuration function.
```c
err_t current14_default_cfg ( current14_t *ctx );
```

#### Example key functions :

- `current14_calib_offset` This function calibrates the zero current offset value.
```c
err_t current14_calib_offset ( current14_t *ctx );
```

- `current14_calib_resolution` This function calibrates the data resolution at the known load current.
```c
err_t current14_calib_resolution ( current14_t *ctx, float calib_current );
```

- `current14_get_current` This function reads the input current level [A].
```c
err_t current14_get_current ( current14_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Current 11 Click board by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and calibrates the zero current offset and data resolution at 3A load current.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current14_cfg_t current14_cfg;  /**< Click config object. */

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
    current14_cfg_setup( &current14_cfg );
    CURRENT14_MAP_MIKROBUS( current14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current14_init( &current14, &current14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT14_ERROR == current14_default_cfg ( &current14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT14_ERROR == current14_calib_offset ( &current14 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at 3A during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT14_ERROR == current14_calib_resolution ( &current14, 3.0f ) )
    {
        log_error( &logger, " Calibrate resolution." );
        for ( ; ; );
    }
    log_printf( &logger, " Data resolution calibration DONE.\r\n" );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the input current measurements and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float current = 0;
    if ( CURRENT14_OK == current14_get_current ( &current14, &current ) )
    {
        log_printf ( &logger, " Current: %.3f A\r\n\n", current );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
