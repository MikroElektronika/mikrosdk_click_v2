---
# DSP click

DSP Click is a compact add-on board that contains a multi-effects digital signal processor. This board features the V1000, a complete multi-effects audio DSP with ultra-high quality audio performance in a rapid ‘time-to-market’ solution from Coolaudio. The V1000 includes its integrated RAM with 16 built-in multi-effects and reverb controlled via I/O pins or I2C interface. Combined with a low-cost A/D-D/A codec like the V4220, this Click board™ provides an ultra-low cost FX solution.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dsp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dsp-click?adtoken=48b980cc0840208867ff3317ac2fc531db4a1dd7&ad=mikromanage&id_employee=33)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Dsp Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Dsp Click driver.
```

#### Standard key functions :

> Config Object Initialization function.
```
void dsp_cfg_setup ( dsp_cfg_t *cfg );
```

> Initialization function.
```
err_t dsp_init ( dsp_t *ctx, dsp_cfg_t *cfg );
```

> Click Default Configuration function.
```
void dsp_default_cfg ( dsp_t *ctx );
```

#### Example key functions :

> DSP reverb and multi-effects setting function.
```
dsp_retval_t dsp_set_effect ( dsp_t *ctx, uint8_t effects );
```

> DSP power on the device function.
```
void dsp_power_on ( dsp_t *ctx );
```

> DSP reset the device function.
```
void dsp_reset ( dsp_t *ctx );
```

## Examples Description

> This application controls reverb and multi-effects Digital Multi-Effects DSP 
> provides different sound performance of the DSP Click.

**The demo application is composed of two sections :**

### Application Init

> Initializes GPIO driver, set the default configuration and start to write log.

```
void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    dsp_cfg_t dsp_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dsp_cfg_setup( &dsp_cfg );
    DSP_MAP_MIKROBUS( dsp_cfg, MIKROBUS_1 );
    if ( dsp_init( &dsp, &dsp_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dsp_default_cfg ( &dsp );   
    log_info( &logger, " Application Task \r\n" );
    Delay_ms( 100 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "           DSP click           \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "     Digital Multi-Effects     \r\n" );
}
```

### Application Task

> This is an example that shows the use of a DSP click board.
> In this example, we change different sound effects
> such as multiple reverbs, echo, phaser, chorus, flanger, etc. every 10 sec.
> Results are being sent to the Usart Terminal where you can track their changes.

```
void application_task ( void ) {
    log_printf( &logger, "-------------------------------\r\n" );
    dsp_set_effect( &dsp, effects );
    display_effects( );
    
    effects++;
    if ( effects > DSP_SET_EFFECT_DELAY1 ) {
        effects = DSP_SET_EFFECT_MEDIUM;
    }

    Delay_ms( 10000 );  
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Dsp

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
