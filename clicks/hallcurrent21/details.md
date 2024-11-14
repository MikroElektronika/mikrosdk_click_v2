
---
# Hall Current 21 Click

> Hall Current 21 Click is a compact add-on board designed for precise current measurement across a wide frequency range, ideal for fast and accurate monitoring applications. This board features the ACS37030, a galvanically-isolated current sensor from Allegro Microsystems. It provides bidirectional current sensing with a range of ±65A and a sensitivity of 20.3mV/A, offering high isolation of 3500VRMS and a working voltage of up to 840VRMS. It also features low noise and a wide operating bandwidth, making it suitable for high-speed switching current and control loop monitoring. This Click board™ is perfect for power supplies in servers, data centers, and solar DC-DC converters.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent21_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/hall-current-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the Hall Current 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Current 21 Click driver.

#### Standard key functions :

- `hallcurrent21_cfg_setup` Config Object Initialization function.
```c
void hallcurrent21_cfg_setup ( hallcurrent21_cfg_t *cfg );
```

- `hallcurrent21_init` Initialization function.
```c
err_t hallcurrent21_init ( hallcurrent21_t *ctx, hallcurrent21_cfg_t *cfg );
```

#### Example key functions :

- `hallcurrent21_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level of the selected input channel.
```c
err_t hallcurrent21_read_voltage_avg ( hallcurrent21_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg );
```

- `hallcurrent21_calib_resolution` This function reads the sensor voltage reference and calibrates the data resolution at a known load current.
```c
err_t hallcurrent21_calib_resolution ( hallcurrent21_t *ctx, float calib_current );
```

- `hallcurrent21_read_current` This function reads the input current level [A].
```c
err_t hallcurrent21_read_current ( hallcurrent21_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Hall Current 21 Click board by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and calibrates the data resolution at 3A load current.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent21_cfg_t hallcurrent21_cfg;  /**< Click config object. */

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
    hallcurrent21_cfg_setup( &hallcurrent21_cfg );
    HALLCURRENT21_MAP_MIKROBUS( hallcurrent21_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hallcurrent21_init( &hallcurrent21, &hallcurrent21_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at %.1fA during the calibration process.\r\n", 
                HALLCURRENT21_CALIBRATING_CURRENT );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( HALLCURRENT21_ERROR == hallcurrent21_calib_resolution ( &hallcurrent21, 
                                                                 HALLCURRENT21_CALIBRATING_CURRENT ) )
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
    if ( HALLCURRENT21_OK == hallcurrent21_read_current ( &hallcurrent21, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
        Delay_ms ( 1000 );
    }
}
```

## Note

> The measurement range is approximately: +/- 65A.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
