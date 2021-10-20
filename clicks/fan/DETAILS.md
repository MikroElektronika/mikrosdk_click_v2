

---
# Fan click

Fan Click carries an EMC2301 controller for powering and regulating the operation of 5V four-wire fans, which are commonly utilized as coolers in computers and other electronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fan_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fan-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Fan Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fan Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fan_cfg_setup ( fan_cfg_t *cfg ); 
 
- Initialization function.
> FAN_RETVAL fan_init ( fan_t *ctx, fan_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void fan_generic_write ( fan_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- Generic read function.
> void fan_generic_read ( fan_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
- Fan click lock registers.
> void fan_lock_registers ( fan_t *ctx, uint8_t lock );

## Examples Description
 
> This application is controller for powering and regulating.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and init chip. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fan_cfg_t fan_cfg;

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

    fan_cfg_setup( &fan_cfg );
    FAN_MAP_MIKROBUS( fan_cfg, MIKROBUS_1 );
    if ( fan_init( &fan, &fan_cfg ) == I2C_MASTER_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done ----" );
    fan_default_cfg( &fan );
    fan_pwm_base( &fan, FAN_PWM_BASE_FREQ_HALF_SCALE );
    log_info( &logger, "---- Application Program Running... ----\n" );
}
  
```

### Application Task

> Performs a control of the fan and reads rotation per minute (RPM).
> Results will be sent to the usb uart terminal.

```c

void application_task ( void )
{
    for ( uint8_t duty = FAN_DUTY_RATIO_0_PER; duty <= FAN_DUTY_RATIO_100_PER;
          duty += FAN_DUTY_RATIO_10_PER )
    {
        fan_setting( &fan, duty );
        log_printf( &logger, " Duty Ratio : %u%%\r\n", (uint16_t)duty );
        Delay_ms( 2000 );

        uint16_t tacho = 0;

        fan_get_tach( &fan, &tacho );
        log_printf( &logger, " Rotation per minute : %urpm\r\n\n", tacho );
        Delay_ms( 2000 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan

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
