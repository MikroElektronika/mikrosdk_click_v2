\mainpage Main Page

---
# Pressure 19 Click

> Pressure 19 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the MLX90817, a factory-calibrated absolute pressure sensor delivering ratiometric analog output from Melexis Technologies. The MLX90817 comes with a configurable host interface that supports I2C serial communication and configurable signal processing (the user is allowed to process the output signal in analog or digital form). It measures pressure from 0.2 up to 3bar with a pressure accuracy of ±33mbar. Its DSP-based architecture using a 16bit microcontroller provides outstanding performance in terms of initial accuracy and assures operation in a temperature range of -40°C to +120°C, ensuring stable operation under extreme conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Pressure 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 19 Click driver.

#### Standard key functions :

- `pressure19_cfg_setup` Config Object Initialization function.
```c
void pressure19_cfg_setup ( pressure19_cfg_t *cfg );
```

- `pressure19_init` Initialization function.
```c
err_t pressure19_init ( pressure19_t *ctx, pressure19_cfg_t *cfg );
```

#### Example key functions :

- `pressure19_get_pressure` This function reads the output voltage and converts it to pressure in mBar.
```c
err_t pressure19_get_pressure ( pressure19_t *ctx, uint16_t *pressure );
```

- `pressure19_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t pressure19_read_voltage ( pressure19_t *ctx, float *voltage );
```

- `pressure19_set_vref` This function sets the voltage reference for Pressure 19 Click driver.
```c
err_t pressure19_set_vref ( pressure19_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of Pressure 19 Click board by reading and displaying the absolute pressure value in mBar.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    pressure19_cfg_t pressure19_cfg;    /**< Click config object. */

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
    pressure19_cfg_setup( &pressure19_cfg );
    PRESSURE19_MAP_MIKROBUS( pressure19_cfg, MIKROBUS_1 );
    err_t init_flag = pressure19_init( &pressure19, &pressure19_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the absolute pressure value [mBar] on the USB UART approximately once per seconds.

```c

void application_task ( void )
{
    uint16_t pressure;
    if ( PRESSURE19_OK == pressure19_get_pressure ( &pressure19, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %u mBar\r\n\n", pressure );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
