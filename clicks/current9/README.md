\mainpage Main Page

---
# Current 9 click

> Current 9 Click is a compact add-on board providing a precise and accurate current sensing solution. This board features the CT415-HSN830DR, high-bandwidth and ultra-low-noise XtremeSense® TMR current sensor designed for the current range up to 30A from Crocus Technology. This sensor also features an integrated current-carrying conductor which handles rated current and generates a current measurement as a linear analog output voltage, accomplishing a total output error of about ±1% full-scale. After that, the user is allowed to process the output voltage in analog or digital form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Current 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current 9 Click driver.

#### Standard key functions :

- `current9_cfg_setup` Config Object Initialization function.
```c
void current9_cfg_setup ( current9_cfg_t *cfg );
```

- `current9_init` Initialization function.
```c
err_t current9_init ( current9_t *ctx, current9_cfg_t *cfg );
```

#### Example key functions :

- `current9_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t current9_read_voltage ( current9_t *ctx, float *voltage );
```

- `current9_read_current` This function reads the input current level [A] based on @b CURRENT9_NUM_CONVERSIONS  of voltage measurements.
```c
err_t current9_read_current ( current9_t *ctx, float *current );
```

- `current9_set_vref` This function sets the voltage reference for Current 9 click driver.
```c
err_t current9_set_vref ( current9_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of Current 9 click board by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current9_cfg_t current9_cfg;  /**< Click config object. */

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
    current9_cfg_setup( &current9_cfg );
    CURRENT9_MAP_MIKROBUS( current9_cfg, MIKROBUS_1 );
    err_t init_flag = current9_init( &current9, &current9_cfg );
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
    if ( CURRENT9_OK == current9_read_current ( &current9, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", current );
        Delay_ms ( 1000 );
    }
}

```

## Note

> For better accuracy, set the voltage reference by using the @b current9_set_vref function,
increase the number of conversions by modifying the @b CURRENT9_NUM_CONVERSIONS macro,
and adjust the @b CURRENT9_ZERO_CURRENT_OFFSET voltage value.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
