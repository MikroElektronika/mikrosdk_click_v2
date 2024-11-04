\mainpage Main Page

---
# Hall Current 18 Click

> Hall Current 18 Click is a compact add-on board that contains a precise solution for AC/DC current sensing. This board features the MCS1806, an isolated Hall-effect current sensor from MPS. The sensor is immune to external magnetic fields via differential sensing and has no magnetic hysteresis. The MCS1806 features galvanic isolation between the pins of the primary conductive path and the sensor leads, allowing it to replace optoisolators and other isolation devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/hall-current-18-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Hall Current 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Current 18 Click driver.

#### Standard key functions :

- `hallcurrent18_cfg_setup` Config Object Initialization function.
```c
void hallcurrent18_cfg_setup ( hallcurrent18_cfg_t *cfg );
```

- `hallcurrent18_init` Initialization function.
```c
err_t hallcurrent18_init ( hallcurrent18_t *ctx, hallcurrent18_cfg_t *cfg );
```

- `hallcurrent18_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent18_default_cfg ( hallcurrent18_t *ctx );
```

#### Example key functions :

- `hallcurrent18_read_current` Hall Current 18 read current function.
```c
err_t hallcurrent18_read_current ( hallcurrent18_t *ctx, float *current );
```

- `hallcurrent18_read_voltage` Hall Current 18 read voltage level function.
```c
err_t hallcurrent18_read_voltage ( hallcurrent18_t *ctx, float *voltage );
```

- `hallcurrent18_read_raw_adc` Hall Current 18 read raw ADC value function.
```c
err_t hallcurrent18_read_raw_adc ( hallcurrent18_t *ctx, uint16_t *raw_adc );
```

## Example Description

> This example demonstrates the use of Hall Current 18 Click board™ 
> by reading and displaying the current measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration
> and set the zero voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent18_cfg_t hallcurrent18_cfg;  /**< Click config object. */

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
    hallcurrent18_cfg_setup( &hallcurrent18_cfg );
    HALLCURRENT18_MAP_MIKROBUS( hallcurrent18_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent18_init( &hallcurrent18, &hallcurrent18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLCURRENT18_ERROR == hallcurrent18_default_cfg ( &hallcurrent18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, " Turn off the load current in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( HALLCURRENT18_OK == hallcurrent18_set_zero_ref( &hallcurrent18 ) )
    {
        log_printf( &logger, " Process complete!\r\n");
    }
    else
    {
        log_error( &logger, " Zero reference." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the current measurements [A] and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float current = 0;
    if ( HALLCURRENT18_OK == hallcurrent18_read_current ( &hallcurrent18, &current ) ) 
    {
        log_printf( &logger, " Current : %.2f [A]\r\n\n", current );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
