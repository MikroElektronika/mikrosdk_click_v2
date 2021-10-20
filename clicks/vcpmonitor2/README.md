\mainpage Main Page
 
---
# VCP Monitor 2 click

VCP Monitor 2 Click is a three-channel, high-side current and bus voltage monitor with alert indication function ensuring the intended application works within desired operating conditions. Featured chip INA3221-Q1, by Texas Instruments, monitors both shunt voltage drops and bus supply voltages, in addition to having programmable conversion times and averaging modes for these signals.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vcpmonitor2_click.png">
</p>

[click Product page](https://www.mikroe.com/vcp-monitor-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Vcpmonitor2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Vcpmonitor2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vcpmonitor2_cfg_setup ( vcpmonitor2_cfg_t *cfg ); 
 
- Initialization function.
> VCPMONITOR2_RETVAL vcpmonitor2_init ( vcpmonitor2_t *ctx, vcpmonitor2_cfg_t *cfg );

#### Example key functions :

- Get Manufacture ID.
> uint16_t vcpmonitor2_get_manifacture_id ( vcpmonitor2_t *ctx );
 
- Get DIE ID.
> uint16_t vcpmonitor2_get_die_id ( vcpmonitor2_t *ctx );

- Get BUS voltage in mV.
> float vcpmonitor2_get_bus_voltage ( vcpmonitor2_t *ctx, uint8_t channel );

## Examples Description

> VCP Monitor 2 Click is a three-channel, high-side current and bus voltage monitor with alert indication 
> function ensuring the intended application works within desired operating conditions.

**The demo application is composed of two sections :**

### Application Init 

> Initiaizes the driver, and checks the communication by reading the manufacture device ID. After that, performs the device default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor2_cfg_t cfg;

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

    vcpmonitor2_cfg_setup( &cfg );
    VCPMONITOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor2_init( &vcpmonitor2, &cfg );

    check_id = vcpmonitor2_get_manifacture_id( &vcpmonitor2 );
    if ( check_id == VCPMONITOR2_DEF_MANUFACTURE_ID )
    {
        log_printf( &logger, ">> Manufacture ID: 0x%.4X\r\n", check_id );
    }
    else
    {
        log_error( &logger, " WRONG ID READ! " );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }

    vcpmonitor2_default_cfg( &vcpmonitor2 );
}
  
```

### Application Task

> Displays the voltage, current, and power detected from channel 1 on the USB UART every 2 seconds. It also displays the status of alert indicators.

```c

void application_task ( void )
{
    log_printf( &logger, ">> CHANNEL 1 <<\r\n" );
    display_channel_data( VCPMONITOR2_CHANNEL_1 );

    display_alert_status( );
    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Vcpmonitor2

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
