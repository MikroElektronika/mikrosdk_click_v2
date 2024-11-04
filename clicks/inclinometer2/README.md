\mainpage Main Page

---
# Inclinometer 2 Click

> Inclinometer 2 Click is a compact add-on board that measures the orientation angle of an object with respect to the force of gravity. This board features the IIS2ICLX, high accuracy, and resolution two-axis inclinometer from STMicroelectronics. It allows selectable full-scale measurements in ranges of ±0.5/±1/±2/±3g in two axes with a configurable host interface that supports both SPI and I2C serial communication. The sensing element is manufactured using a dedicated micromachining process developed by STMicroelectronics to produce inertial sensors and actuators on silicon wafers.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/inclinometer2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/inclinometer-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Inclinometer 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Inclinometer 2 Click driver.

#### Standard key functions :

- `inclinometer2_cfg_setup` Config Object Initialization function.
```c
void inclinometer2_cfg_setup ( inclinometer2_cfg_t *cfg );
```

- `inclinometer2_init` Initialization function.
```c
err_t inclinometer2_init ( inclinometer2_t *ctx, inclinometer2_cfg_t *cfg );
```

- `inclinometer2_default_cfg` Click Default Configuration function.
```c
err_t inclinometer2_default_cfg ( inclinometer2_t *ctx );
```

#### Example key functions :

- `inclinometer2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t inclinometer2_get_int_pin ( inclinometer2_t *ctx );
```

- `inclinometer2_get_accel` This function checks if the accel data is ready and than reads the accel X and Y axis in mg.
```c
err_t inclinometer2_get_accel ( inclinometer2_t *ctx, float *x_axis, float *y_axis );
```

- `inclinometer2_get_temperature` This function checks if the temperature data is ready and than reads the temperature in Celsius.
```c
err_t inclinometer2_get_temperature ( inclinometer2_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Inclinometer 2 Click board by reading and displaying the Accel X and Y axis data (mg) and the temperature (degC) on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which enables the accel data ready interrupt, sets output data rate to 12.5 Hz and accel full-scale range to +-2g.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer2_cfg_t inclinometer2_cfg;  /**< Click config object. */

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
    inclinometer2_cfg_setup( &inclinometer2_cfg );
    INCLINOMETER2_MAP_MIKROBUS( inclinometer2_cfg, MIKROBUS_1 );
    err_t init_flag  = inclinometer2_init( &inclinometer2, &inclinometer2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER2_ERROR == inclinometer2_default_cfg ( &inclinometer2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the values of accel X and Y axis as well as the absolute temperature and displays the results on the USB UART. The data sample rate is
set to 12.5Hz by default, therefore the data is being read approximately every 80ms.

```c
void application_task ( void )
{
    // Wait for accel data ready indication
    while ( !inclinometer2_get_int_pin ( &inclinometer2 ) );
    
    float x_axis, y_axis;
    if ( INCLINOMETER2_OK == inclinometer2_get_accel ( &inclinometer2, &x_axis, &y_axis ) )
    {
        log_printf( &logger, " X: %.2f mg\r\n", x_axis );
        log_printf( &logger, " Y: %.2f mg\r\n", y_axis );
    }
    float temperature;
    if ( INCLINOMETER2_OK == inclinometer2_get_temperature ( &inclinometer2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
