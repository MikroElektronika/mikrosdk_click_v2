\mainpage Main Page

---
# LDC 2 Click

> LDC 2 Click is a compact add-on board that measures inductance change which a conductive target causes when it moves into the inductor's AC magnetic field. This board features the LDC1041, inductance-to-digital converter (LDC) for inductive sensing solutions from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ldc2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ldc-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the LDC2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LDC2 Click driver.

#### Standard key functions :

- `ldc2_cfg_setup` Config Object Initialization function.
```c
void ldc2_cfg_setup ( ldc2_cfg_t *cfg );
```

- `ldc2_init` Initialization function.
```c
err_t ldc2_init ( ldc2_t *ctx, ldc2_cfg_t *cfg );
```

- `ldc2_default_cfg` Click Default Configuration function.
```c
err_t ldc2_default_cfg ( ldc2_t *ctx );
```

#### Example key functions :

- `ldc2_measure_resonance_impedance` This function measures the resonance impedance and proximity data.
```c
err_t ldc2_measure_resonance_impedance ( ldc2_t *ctx, uint8_t *prox_data, float *rp_data );
```

- `ldc2_measure_inductance` This function measures the inductance and sensor frequency.
```c
err_t ldc2_measure_inductance ( ldc2_t *ctx, float *freq, float *inductance );
```

- `ldc2_get_sensor_frequency` This function reads and calculates the sensor frequency.
```c
err_t ldc2_get_sensor_frequency ( ldc2_t *ctx, float *freq );
```

## Example Description

> This example demonstrates the use of LDC 2 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ldc2_cfg_t ldc2_cfg;    /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ldc2_cfg_setup( &ldc2_cfg );
    LDC2_MAP_MIKROBUS( ldc2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ldc2_init( &ldc2, &ldc2_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( LDC2_ERROR == ldc2_default_cfg ( &ldc2 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Measures the resonance impedance and proximity as well as the inductance and sensor frequency 
> approximately every 200ms and displays all values on the USB UART.

```c

void application_task ( void )
{
    uint8_t prox_data = 0;
    float rp_data = 0;
    float freq = 0;
    float inductance = 0;
    
    if ( LDC2_OK == ldc2_measure_resonance_impedance( &ldc2, &prox_data, &rp_data ) )
    {
        log_printf( &logger, " Proximity: %u\r\n Resonance Impedance: %.3f kOhm\r\n\n", ( uint16_t ) prox_data, rp_data );
    }
    
    if ( LDC2_OK == ldc2_measure_inductance( &ldc2, &freq, &inductance ) )
    {
        log_printf( &logger, " Sensor Frequency: %.3f MHz\r\n Inductance: %.6f uH\r\n\n", freq, inductance );
    }
    
    Delay_ms ( 200 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LDC2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
