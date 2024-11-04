
---
# Buck 18 Click

> Buck 18 Click is a compact add-on board for step-down voltage conversion in power-sensitive applications. This board features the MAXM38643, an ultra-low-IQ nanoPower buck module from Analog Devices, providing highly efficient voltage regulation with minimal power consumption. The board supports input voltages from 1.8V to 5.5V, converting them to output voltages between 0.7V and 3.3V. Users can manually adjust the output voltage through an onboard TRIM trimmer or digitally via the AD5171 digital potentiometer controlled through an I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/buck-18-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Buck 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck 18 Click driver.

#### Standard key functions :

- `buck18_cfg_setup` Config Object Initialization function.
```c
void buck18_cfg_setup ( buck18_cfg_t *cfg );
```

- `buck18_init` Initialization function.
```c
err_t buck18_init ( buck18_t *ctx, buck18_cfg_t *cfg );
```

- `buck18_default_cfg` Click Default Configuration function.
```c
err_t buck18_default_cfg ( buck18_t *ctx );
```

#### Example key functions :

- `buck18_set_vout` This function sets the voltage output level.
```c
err_t buck18_set_vout ( buck18_t *ctx, buck18_vout_t vout );
```

- `buck18_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t buck18_read_voltage ( buck18_t *ctx, float *voltage );
```

- `buck18_enable` This function turns on the power switch and enables the buck mode.
```c
void buck18_enable ( buck18_t *ctx );
```

## Example Description

> This example demonstrates the use of the Buck 18 Click board by changing the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck18_cfg_t buck18_cfg;  /**< Click config object. */

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
    buck18_cfg_setup( &buck18_cfg );
    BUCK18_MAP_MIKROBUS( buck18_cfg, MIKROBUS_1 );
    err_t init_flag = buck18_init( &buck18, &buck18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK18_ERROR == buck18_default_cfg ( &buck18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application changes the output voltage and displays the current voltage output value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( buck18_vout_t vout = BUCK18_VOUT_3V3; vout <= BUCK18_VOUT_0V9; vout++ )
    {
        if ( BUCK18_OK == buck18_set_vout( &buck18, vout ) )
        {
            float voltage = 0;
            if ( BUCK18_OK == buck18_read_voltage( &buck18, &voltage ) ) 
            {
                log_printf( &logger, " Voltage : %.3f[V]\r\n\n", voltage );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
            }
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
