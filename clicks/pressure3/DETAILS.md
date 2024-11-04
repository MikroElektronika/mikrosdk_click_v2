
# Pressure 3 Click

Pressure 3 Click is a mikroBUS add-on board that carries an Infineon DPS310 digital barometric pressure sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pressure3_cfg_setup ( pressure3_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE3_RETVAL pressure3_init ( pressure3_t *ctx, pressure3_cfg_t *cfg );

- Click Default Configuration function.
> void pressure3_default_cfg ( pressure3_t *ctx );


#### Example key functions :

- Get temperature pressure.
> void pressure3_get_t_p_data ( pressure3_t *ctx, float *temperature, float *presure, pressure3_coeff_t *coeff_struct );
 
- Get coefficients.
> void pressure3_get_coefficients ( pressure3_t *ctx, pressure3_coeff_t *coeff_struct );

- Read the coefficients value for calculation function.
> int32_t pressure3_get_measurement_data ( pressure3_t *ctx, uint8_t mbs_reg_addr );

## Examples Description

> This application is digital barometric pressure sensor. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization device, set default configuration and start to write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure3_cfg_t cfg;

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

    pressure3_cfg_setup( &cfg );
    PRESSURE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure3_init( &pressure3, &cfg );
    pressure3_default_cfg( &pressure3 );
}
  
```

### Application Task

> This is an example which demonstrates the use of Pressure 3 Click board.
     Measured pressure and temperature data from the DPS310 sensor on Pressure 3 Click board.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 3 sec.

```c

void application_task ( void )
{
    float pressure;
    float temperature;

    pressure3_get_t_p_data( &pressure3, &temperature, &pressure, &coeff_struct );
    
    log_printf( &logger, " * Pressure: %.2f mbar * \r\n", pressure );
    log_printf( &logger, " * Temperature: %.2f C * \r\n", temperature );
    log_printf( &logger, " ----------------------- \r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure3

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
