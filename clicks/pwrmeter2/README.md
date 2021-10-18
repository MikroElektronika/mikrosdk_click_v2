\mainpage Main Page
 
---
# PWR Meter 2 click

PWR Meter 2 click is a compact and accurate power monitoring Click board™, capable of measuring and monitoring voltage up to 24V and current up to 5A.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwrmeter2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pwr-meter-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the PwrMeter2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PwrMeter2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pwrmeter2_cfg_setup ( pwrmeter2_cfg_t *cfg ); 
 
- Initialization function.
> PWRMETER2_RETVAL pwrmeter2_init ( pwrmeter2_t *ctx, pwrmeter2_cfg_t *cfg );

- Click Default Configuration function.
> void pwrmeter2_default_cfg ( pwrmeter2_t *ctx );


#### Example key functions :

- This function waits until conversion, for the desired channel, is finished and returns information about data width.
> uint8_t pwrmeter2_check_data_ready ( pwrmeter2_t *ctx, uint8_t sel_chann );
 
- This function returns the state of the modulator output for the channel 1.
> uint8_t pwrmeter2_get_modulator_1 ( pwrmeter2_t *ctx );

- This function returns the state of the Data Ready ( DR ) pin.
> uint8_t pwrmeter2_check_ready_pin ( pwrmeter2_t *ctx );

## Examples Description

> This app measuring and monitoring voltage up to 24V and current up to 5A.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwrmeter2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    pwrmeter2_cfg_setup( &cfg );
    PWRMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwrmeter2_init( &pwrmeter2, &cfg );

    pwrmeter2_default_cfg( &pwrmeter2 );
    log_printf( &logger, "PWR Meter 2 is initialized \r\n" );
    Delay_ms( 200 );
}
  
```

### Application Task

> Gets calculated voltage, current and power data every 500 miliseconds
> and shows results on UART.

```c

void application_task ( void )
{
    int32_t voltage_res;
    int32_t current_res;
    uint32_t power_res;

    pwrmeter2_get_data( &pwrmeter2, &voltage_res, &current_res, &power_res );

    log_printf( &logger, "U = %ld mV \r\n", voltage_res );
    log_printf( &logger, "I = %ld mA \r\n", current_res );
    log_printf( &logger, "P = %lu mW \r\n", power_res );

    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.PwrMeter2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
