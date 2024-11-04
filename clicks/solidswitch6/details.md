
---
# SolidSwitch 6 Click

> SolidSwitch 6 Click is a compact add-on board for reliable load management in automotive power distribution systems. This board features the VNF1048F, a high-side switch controller with intelligent e-fuse protection from STMicroelectronics. This board supports an input voltage range of 6V to 48V, controls external MOSFET, and offers essential protection features such as overcurrent, under-voltage, and thermal shutdown, with diagnostic feedback via SPI. It also includes an NTC resistor for monitoring MOSFET temperature and operates with either 3.3V or 5V logic levels.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/solidswitch6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/solidswitch-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the SolidSwitch 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SolidSwitch 6 Click driver.

#### Standard key functions :

- `solidswitch6_cfg_setup` Config Object Initialization function.
```c
void solidswitch6_cfg_setup ( solidswitch6_cfg_t *cfg );
```

- `solidswitch6_init` Initialization function.
```c
err_t solidswitch6_init ( solidswitch6_t *ctx, solidswitch6_cfg_t *cfg );
```

- `solidswitch6_default_cfg` Click Default Configuration function.
```c
err_t solidswitch6_default_cfg ( solidswitch6_t *ctx );
```

#### Example key functions :

- `solidswitch6_get_vout` This function reads the raw ADC value and converts it to a proportional voltage level using the SPI serial interface.
```c
err_t solidswitch6_get_vout ( solidswitch6_t *ctx, float *vout );
```

- `solidswitch6_set_control` This function writes control registers to configure the switch controller using the SPI serial interface.
```c
err_t solidswitch6_set_control ( solidswitch6_t *ctx, solidswitch6_ctrl_t ctrl );
```

- `solidswitch6_get_device_temp` This function reads the raw ADC value and converts it to device temperature in degrees Celsius using the SPI serial interface.
```c
err_t solidswitch6_get_device_temp ( solidswitch6_t *ctx, float *tj );
```

## Example Description

> This library contains API for the SolidSwitch 6 Click driver
> and demonstrate uses of the high-side switch controller with intelligent fuse protection.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch6_cfg_t solidswitch6_cfg;  /**< Click config object. */
    
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
    solidswitch6_cfg_setup( &solidswitch6_cfg );
    SOLIDSWITCH6_MAP_MIKROBUS( solidswitch6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch6_init( &solidswitch6, &solidswitch6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH6_ERROR == solidswitch6_default_cfg ( &solidswitch6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ______________________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the device temperature 
> and voltage level of the current sense amplifier, NTC, and output voltage measurement.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float app_buf = 0;
    if ( SOLIDSWITCH6_OK == solidswitch6_get_device_temp( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " Temperature: %.2f [degC]\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vntc( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " NTC: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vout( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " Vout: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vds( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " VDS: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    log_printf( &logger, " ______________________\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
