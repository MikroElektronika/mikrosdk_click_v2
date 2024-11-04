\mainpage Main Page


---
# Remote Temp Click

Remote Temp Click is a temperature sensing Click board™, which features the EMC1833 from Microchip, a specifically designed IC, capable of measuring remote temperature. This option makes Remote Temp Click well-suited for monitoring the temperature of a CPU, GPU or FPGA, where the BJT model junction can be a substrate PNP or NPN.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/remotetemp_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/remote-temp-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the RemoteTemp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RemoteTemp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void remotetemp_cfg_setup ( remotetemp_cfg_t *cfg ); 
 
- Initialization function.
> REMOTETEMP_RETVAL remotetemp_init ( remotetemp_t *ctx, remotetemp_cfg_t *cfg );

- Click Default Configuration function.
> void remotetemp_default_cfg ( remotetemp_t *ctx );


#### Example key functions :

- Getting state of INT pin.
> uint8_t remotetemp_int_get ( remotetemp_t *ctx );

 
- Getting state of AN pin.
> uint8_t remotetemp_an_get ( remotetemp_t *ctx );


- Setting temperature range.
> uint8_t remotetemp_set_range( remotetemp_t *ctx, uint8_t range_setting );


## Examples Description

> This application reads remote temperature data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver, sets range, configures device and sets threshold values.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    remotetemp_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.

    remotetemp_cfg_setup( &cfg );
    REMOTETEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    remotetemp_init( &remotetemp, &cfg );
    Delay_ms ( 300 );
    remotetemp_set_range( &remotetemp, REMOTETEMP_RANGE_0_127 );
    remotetemp_default_cfg( &remotetemp );
    log_printf( &logger, "> app init done \r\n" );
}
```

### Application Task

> Executes all 'remotetemp_aux_getXxx()' functions.

```c
void application_task ( void )
{
    remotetemp_aux_get_fault( &remotetemp );
    remotetemp_aux_get_high_limit_status( &remotetemp );
    remotetemp_aux_get_low_limit_status( &remotetemp );
    remotetemp_aux_get_therm_limit_status( &remotetemp );
    remotetemp_aux_get_hottest_status( &remotetemp );
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RemoteTemp

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.


---
