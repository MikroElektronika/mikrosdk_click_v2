\mainpage Main Page

---
# Ultrasonic 5 Click

> Ultrasonic 5 Click is a compact add-on board that contains circuits for processing the ultrasonic sensor's output. 
> This board features the TUSS4470, a transformer-drive ultrasonic sensor IC with a logarithmic amplifier from Texas Instruments. 
> In addition to the high selectability of the power supply of the IC itself, 
> this board also allows you to choose between 40kHz and 1MHz operating frequency, 
> with a signal zero crossing comparator as an option. The ultrasonic sensor, 
> the UTR-1440K from PUI Audio, also comes in the same package with this Click board™.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ultrasonic5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ultrasonic-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Ultrasonic 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ultrasonic 5 Click driver.

#### Standard key functions :

- `ultrasonic5_cfg_setup` Config Object Initialization function.
```c
void ultrasonic5_cfg_setup ( ultrasonic5_cfg_t *cfg );
```

- `ultrasonic5_init` Initialization function.
```c
err_t ultrasonic5_init ( ultrasonic5_t *ctx, ultrasonic5_cfg_t *cfg );
```

- `ultrasonic5_default_cfg` Click Default Configuration function.
```c
err_t ultrasonic5_default_cfg ( ultrasonic5_t *ctx );
```

#### Example key functions :

- `ultrasonic5_clear_io1_pin` This function clears the IO1 pin to low logic state.
```c
void ultrasonic5_clear_io1_pin ( ultrasonic5_t *ctx );
```

- `ultrasonic5_pwm_start` This function starts the PWM module output.
```c
err_t ultrasonic5_pwm_start ( ultrasonic5_t *ctx );
```

- `ultrasonic5_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t ultrasonic5_read_an_pin_voltage ( ultrasonic5_t *ctx, float *data_out );
```

## Example Description

> This example demonstrates the use of Ultrasonic 5 Click board by reading the measurements from the connected ultrasonic sensor and displaying it on a Serial Plot.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultrasonic5_cfg_t ultrasonic5_cfg;  /**< Click config object. */

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
    ultrasonic5_cfg_setup( &ultrasonic5_cfg );
    ULTRASONIC5_MAP_MIKROBUS( ultrasonic5_cfg, MIKROBUS_1 );
    if ( ULTRASONIC5_OK != ultrasonic5_init( &ultrasonic5, &ultrasonic5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ULTRASONIC5_OK != ultrasonic5_default_cfg ( &ultrasonic5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Performs a burst generation which starts the measurement and then reads the next 200 ADC samples and displays the results on the USB UART (SerialPlot).

```c
void application_task ( void )
{
    float voltage = 0;
    // Burst generation / Start measurement
    ultrasonic5_set_duty_cycle ( &ultrasonic5, ULTRASONIC5_DEF_DYTY );
    ultrasonic5_pwm_start( &ultrasonic5 );
    ultrasonic5_clear_io1_pin ( &ultrasonic5 );
    Delay_500us ( );
    ultrasonic5_set_io1_pin ( &ultrasonic5 );
    ultrasonic5_pwm_stop( &ultrasonic5 );
    // Read and log the next 200 ADC samples which we will plot on a Serial Plotter
    for ( uint16_t cnt = 0; cnt < 200; cnt++ )
    {
        if ( ULTRASONIC5_OK == ultrasonic5_read_an_pin_voltage ( &ultrasonic5, &voltage ) ) 
        {
            log_printf( &logger, "%.3f\r\n", voltage );
        }
    }
}
```

## Note

> In order to get valid measuremets a proper ultrasonic sensor must be connected to OUTA and OUTB.
We have used an UTR-1440K-TT-R sensor for the test. We recommend using the SerialPlot tool
for data visualizing. Refer to the datasheet "Application Curves" section in order to check
and compare the results from the plotter.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ultrasonic5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
