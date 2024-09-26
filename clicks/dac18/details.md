
---
# DAC 18 click

> DAC 18 Click is a compact add-on board for converting general-purpose input to PWM signals. This board features the DAC539G2-Q1, a 10-bit smart DAC from Texas Instruments. The board offers two key output channels: one for digital-to-analog conversion (OUT1) and the other for voltage-to-PWM conversion (OUT0) supporting triangle or sawtooth waveforms. It features an operational mode selection pin for I2C programming or standalone operation, along with nonvolatile memory for storing register settings. DAC 18 Click is ideal for automotive lighting systems and industrial environments requiring reliable signal conversion.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac18_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-18-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the DAC 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 18 Click driver.

#### Standard key functions :

- `dac18_cfg_setup` Config Object Initialization function.
```c
void dac18_cfg_setup ( dac18_cfg_t *cfg );
```

- `dac18_init` Initialization function.
```c
err_t dac18_init ( dac18_t *ctx, dac18_cfg_t *cfg );
```

- `dac18_default_cfg` Click Default Configuration function.
```c
err_t dac18_default_cfg ( dac18_t *ctx );
```

#### Example key functions :

- `dac18_cfg_pwm_out` This function configures PWM output (OUT0) for the function generator by using the I2C serial interface.
```c
err_t dac18_cfg_pwm_out ( dac18_t *ctx, uint8_t f_sel, uint8_t c_step, uint8_t t_step );
```

- `dac18_set_mode` This function selects between programming and standalone modes by toggling the digital output state of the MOD pin.
```c
void dac18_set_mode ( dac18_t *ctx, uint8_t mode );
```

- `dac18_get_gpi_status` This function gets GPI status by reading the states of the GP0, GP1 and GP2 pins.
```c
void dac18_get_gpi_status ( dac18_t *ctx, uint8_t *gpi_status );
```

## Example Description

> This example demonstrates the use of the DAC 18 click board 
> by configuring the waveform signals from a function generator on the OUT0 
> and voltage level on the OUT1.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration (configuration mode).

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac18_cfg_t dac18_cfg;  /**< Click config object. */

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
    dac18_cfg_setup( &dac18_cfg );
    DAC18_MAP_MIKROBUS( dac18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dac18_init( &dac18, &dac18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC18_ERROR == dac18_default_cfg ( &dac18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Use the GP0, GP1 and GP2 switch to change the outputs\r\n\n" );
}
```

### Application Task

> The demo application operated in standalone mode and displayed the voltage level on OUT1.
> The GP0, GP1, and GP2 switches on the DAC 18 click board 
> are used to change the output voltage level and waveform signals.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    dac18_get_gpi_status( &dac18, &gpi_status );
    if ( gpi_status != new_gpi_status )
    {
        new_gpi_status = gpi_status;
        dac18_display_out_status( );
    }
    Delay_ms ( 100 );
}
```

## Note

> Set GP0, GP1, and GP2 switches to position "1" for the configuration modes.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
