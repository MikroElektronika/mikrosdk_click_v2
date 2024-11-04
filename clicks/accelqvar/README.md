\mainpage Main Page

---
# AccelQvar Click

> Accel&Qvar Click is a compact add-on board for capturing precise acceleration measurements and detecting electric charge variations. This board features the LIS2DUXS12, an ultralow-power accelerometer from STMicroelectronics. Besides low power consumption, it also includes Qvar technology, artificial intelligence, and an anti-aliasing filter. This digital, 3-axis accelerometer has adjustable full scales (±2g to ±16g), output data rates (1.6Hz to 800Hz), and multiple operating modes to serve various applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accelqvar_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accelqvar-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the AccelQvar Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AccelQvar Click driver.

#### Standard key functions :

- `accelqvar_cfg_setup` Config Object Initialization function.
```c
void accelqvar_cfg_setup ( accelqvar_cfg_t *cfg );
```

- `accelqvar_init` Initialization function.
```c
err_t accelqvar_init ( accelqvar_t *ctx, accelqvar_cfg_t *cfg );
```

- `accelqvar_default_cfg` Click Default Configuration function.
```c
err_t accelqvar_default_cfg ( accelqvar_t *ctx );
```

#### Example key functions :

- `accelqvar_get_axes_data` This function reads the accelerometer sensor axes data.
```c
err_t accelqvar_get_axes_data ( accelqvar_t *ctx, accelqvar_axes_t *axes );
```

- `accelqvar_get_qvar_data` This function reads the Qvar electrostatic sensor data output.
```c
err_t accelqvar_get_qvar_data ( accelqvar_t *ctx, float *qvar );
```

## Example Description

> This library contains API for the AccelQvar Click driver. 
> The library initializes and defines the I2C and SPI drivers to write and read data 
> from registers and the default configuration for reading the accelerator data 
> and Qvar electrostatic sensor measurement.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C and SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accelqvar_cfg_t accelqvar_cfg;  /**< Click config object. */

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
    accelqvar_cfg_setup( &accelqvar_cfg );
    ACCELQVAR_MAP_MIKROBUS( accelqvar_cfg, MIKROBUS_1 );
    err_t init_flag = accelqvar_init( &accelqvar, &accelqvar_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    if ( ACCELQVAR_ERROR == accelqvar_default_cfg ( &accelqvar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}
```

### Application Task

> This example demonstrates the use of the AccelQvar Click board.
> Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis [mg] 
> and detects and displays a touch position and the strength of a touch.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    accelqvar_axes_t acc_axis;
    if ( ACCELQVAR_OK == accelqvar_get_axes_data( &accelqvar, &acc_axis ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
        log_printf( &logger, "_________________\r\n" );
    }

    float qvar = 0;
    if ( ACCELQVAR_OK == accelqvar_get_qvar_data( &accelqvar, &qvar ) )
    {
        if ( abs( qvar ) > ACCELQVAR_THOLD_DETECT_TOUCH )
        {
            uint8_t touch_strength = ( uint8_t ) ( abs( qvar ) / ACCELQVAR_THOLD_SENS );
            log_printf( &logger, " Touch position: " );
            if ( qvar < ACCELQVAR_TOUCH_ZERO )
            {
                log_printf( &logger, " Left\r\n" );
            }
            else
            {
                log_printf( &logger, " Right\r\n " );
            }
            log_printf( &logger, " Strength: " );
            while ( touch_strength )
            {
                log_printf( &logger, "|" );
                touch_strength--;
            }
            log_printf( &logger, "\r\n_________________\r\n" );
            Delay_ms ( 100 );
        }
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AccelQvar

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
