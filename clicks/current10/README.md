\mainpage Main Page

---
# Current 10 click

> Current 10 Click is a compact add-on board designed for reliable current measurements. This board features the CT455, an XtremeSense™ TMR coreless current sensor from Allegro Microsystems, with a wide 1MHz bandwidth and a sensitivity of 333.3mV/mT, capable of detecting both positive and negative current flows (±6mT). It translates magnetic fields into a linear analog output with less than ±1.0% error across temperature and supply voltage variations.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Current 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current 10 Click driver.

#### Standard key functions :

- `current10_cfg_setup` Config Object Initialization function.
```c
void current10_cfg_setup ( current10_cfg_t *cfg );
```

- `current10_init` Initialization function.
```c
err_t current10_init ( current10_t *ctx, current10_cfg_t *cfg );
```

#### Example key functions :

- `current10_calib_offset` This function calibrates the zero current offset value.
```c
err_t current10_calib_offset ( current10_t *ctx );
```

- `current10_calib_resolution` This function calibrates the data resolution at the known load current.
```c
err_t current10_calib_resolution ( current10_t *ctx, float calib_current );
```

- `current10_read_current` This function reads the input current level [A].
```c
err_t current10_read_current ( current10_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Current 10 click board by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and calibrates the zero current offset and data resolution at 3A load current.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current10_cfg_t current10_cfg;  /**< Click config object. */

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
    current10_cfg_setup( &current10_cfg );
    CURRENT10_MAP_MIKROBUS( current10_cfg, MIKROBUS_1 );
    err_t init_flag = current10_init( &current10, &current10_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT10_ERROR == current10_calib_offset ( &current10 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at %.1fA during the calibration process.\r\n", 
                CURRENT10_CALIBRATING_CURRENT );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT10_ERROR == current10_calib_resolution ( &current10, CURRENT10_CALIBRATING_CURRENT ) )
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
    if ( CURRENT10_OK == current10_read_current ( &current10, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
        Delay_ms ( 1000 );
    }
}

```

## Note

> The measurement range is approximately: +/- 75A.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
