
---
# PIR 2 click

> PIR 2 Click is a compact add-on board designed for high-performance motion detection applications. This board features the ZSLM323511, a dual-element balanced differential pyroelectric (PIR) sensor from Zilog. Key features include excellent EMI immunity, a low-profile surface mount package, and a typical field of view of 150 degrees on the X-axis and 139 degrees on the Y-axis. The board also integrates the ZCWM05GIV1 PIR lens for maximum IR transmissivity. Ideal for security systems, lighting control, and video doorbells, PIR 2 Click ensures reliable motion detection in various demanding environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pir2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pir-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the PIR 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PIR 2 Click driver.

#### Standard key functions :

- `pir2_cfg_setup` Config Object Initialization function.
```c
void pir2_cfg_setup ( pir2_cfg_t *cfg );
```

- `pir2_init` Initialization function.
```c
err_t pir2_init ( pir2_t *ctx, pir2_cfg_t *cfg );
```

#### Example key functions :

- `pir2_read_raw_adc` This function reads raw ADC value.
```c
err_t pir2_read_raw_adc ( pir2_t *ctx, uint16_t *raw_adc );
```

- `pir2_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t pir2_read_voltage ( pir2_t *ctx, float *voltage );
```

- `pir2_set_vref` This function sets the voltage reference for PIR 2 click driver.
```c
err_t pir2_set_vref ( pir2_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of PIR 2 Click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and selects the driver interface.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    pir2_cfg_t pir2_cfg;    /**< Click config object. */

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

    pir2_drv_interface_sel( &pir2_cfg, PIR2_DRV_SEL_I2C );

    // Click initialization.
    pir2_cfg_setup( &pir2_cfg );
    PIR2_MAP_MIKROBUS( pir2_cfg, MIKROBUS_1 );
    err_t init_flag = pir2_init( &pir2, &pir2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> It checks if the sensor has detected movement and displays message on the USB UART.

```c

void application_task ( void ) 
{
    float voltage = 0;
    pir2_read_voltage ( &pir2, &voltage );
    if ( voltage > PIR2_VOLTAGE_TRESHOLD )
    {
        log_printf( &logger, " Motion detected \r\n" );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PIR2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
