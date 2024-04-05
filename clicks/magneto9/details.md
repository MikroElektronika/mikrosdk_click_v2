
---
# Magneto 9 click

> Magneto 9 Click is a compact add-on board that contains a low-power, accurate, and reliable magnetic sensing device. This board features the A1359, dual tracking output linear hall-effect sensor from Allegro MicroSystems. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto_9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Magneto9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magneto9 Click driver.

#### Standard key functions :

- `magneto9_cfg_setup` Config Object Initialization function.
```c
void magneto9_cfg_setup ( magneto9_cfg_t *cfg );
```

- `magneto9_init` Initialization function.
```c
err_t magneto9_init ( magneto9_t *ctx, magneto9_cfg_t *cfg );
```

#### Example key functions :

- `magneto9_read_adc_voltage` This function reads raw 12-bit ADC data and converts it to voltage by using I2C serial interface.
```c
err_t magneto9_read_adc_voltage ( magneto9_t *ctx, float *voltage );
```

- `magneto9_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t magneto9_read_an_pin_voltage ( magneto9_t *ctx, float *data_out );
```

- `magneto9_get_pwm_pin` This function returns the PWM pin logic state.
```c
uint8_t magneto9_get_pwm_pin ( magneto9_t *ctx );
```

## Example Description

> This example demonstrates the use of Magneto 9 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    magneto9_cfg_t magneto9_cfg;  /**< Click config object. */

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
    magneto9_cfg_setup( &magneto9_cfg );
    MAGNETO9_MAP_MIKROBUS( magneto9_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == magneto9_init( &magneto9, &magneto9_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ADC voltage and calculates the magnetic field strength from it.
> Voltage increases with increasing positive (south) applied magnetic field.
> All data are being displayed on the USB UART where you can track their changes.

```c

void application_task ( void )
{
    float voltage = 0;
    
    if ( MAGNETO9_OK == magneto9_read_an_pin_voltage ( &magneto9, &voltage ) )
    {
        float field_strength = MAGNETO9_VOLTAGE_TO_FIELD_STRENGTH ( voltage );
        log_printf( &logger, " ADC Voltage : %.3f V\r\n", voltage );
        log_printf( &logger, " Magnetic field strength : %.3f mT\r\n", field_strength );
        if ( field_strength < 0 )
        {
            log_printf( &logger, " The North Pole magnetic field prevails.\r\n\n" );
        }
        else
        {
            log_printf( &logger, " The South Pole magnetic field prevails.\r\n\n" );
        }
    }
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
