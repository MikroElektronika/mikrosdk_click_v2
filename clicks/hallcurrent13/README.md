\mainpage Main Page

---
# Hall Current 13 click

> Hall Current 13 Click is a compact add-on board that provides economical and precise AC or DC current sensing solutions. This board features the TMCS1107-Q1, a galvanically isolated Hall-effect current sensor capable of DC or AC current measurement with high accuracy, excellent linearity, and temperature stability from Texas Instruments. It enables the lowest drift, <3% full-scale error, and highest accuracy over time and temperature. It also provides a reliable 420V lifetime working voltage and 3kVRMS isolation between the current path and circuitry with uni/bidirectional current sensing. Besides, the user is allowed to process the output signal in analog or digital form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Hall Current 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Current 13 Click driver.

#### Standard key functions :

- `hallcurrent13_cfg_setup` Config Object Initialization function.
```c
void hallcurrent13_cfg_setup ( hallcurrent13_cfg_t *cfg );
```

- `hallcurrent13_init` Initialization function.
```c
err_t hallcurrent13_init ( hallcurrent13_t *ctx, hallcurrent13_cfg_t *cfg );
```

- `hallcurrent13_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent13_default_cfg ( hallcurrent13_t *ctx );
```

#### Example key functions :

- `hallcurrent13_read_current` This function reads the input current level [A] based on HALLCURRENT13_NUM_CONVERSIONS of voltage measurements.
```c
err_t hallcurrent13_read_current ( hallcurrent13_t *ctx, float *current );
```

- `hallcurrent13_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t hallcurrent13_read_voltage ( hallcurrent13_t *ctx, float *voltage );
```

- `hallcurrent13_set_vref` This function sets the voltage reference for Hall Current 13 click driver.
```c
err_t hallcurrent13_set_vref ( hallcurrent13_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of Hall Current 13 click board by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent13_cfg_t hallcurrent13_cfg;  /**< Click config object. */

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
    hallcurrent13_cfg_setup( &hallcurrent13_cfg );
    HALLCURRENT13_MAP_MIKROBUS( hallcurrent13_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent13_init( &hallcurrent13, &hallcurrent13_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the input current measurements and displays the results on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float current = 0;
    if ( HALLCURRENT13_OK == hallcurrent13_read_current ( &hallcurrent13, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", current );
        Delay_ms( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
