
---
# Manometer 2 Click

Manometer 2 Click carries the MS5525DSO-SB001GS digital pressure sensor, based on leading MEMS technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/manometer2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/manometer-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Manometer2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Manometer2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void manometer2_cfg_setup ( manometer2_cfg_t *cfg ); 
 
- Initialization function.
> MANOMETER2_RETVAL manometer2_init ( manometer2_t *ctx, manometer2_cfg_t *cfg );

#### Example key functions :

- Generic read data function
uint32_t manometer2_read_command ( manometer2_t *ctx, uint8_t reg_address );

- Function read coeffitient
> void manometer2_read_coef ( manometer2_t *ctx );

- Get pressure data function
float manometer2_get_pressure ( manometer2_t *ctx, uint8_t oversampling_ratio );

## Examples Description

> This application is digital pressure sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C,
> initialization Manometer 2 sensor MS5525DSO-SB001GS by read coeffitient value
> and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    manometer2_cfg_t cfg;

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

    manometer2_cfg_setup( &cfg );
    MANOMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    manometer2_init( &manometer2, &cfg );

    manometer2_read_coef( &manometer2 );
    log_printf( &logger, "        Initialization \r\n" );
    log_printf( &logger, "----------------------------- \r\n" );
    Delay_100ms( );
}
  
```

### Application Task

> This is a example which demonstrates the use of Manometer 2 Click board.
> Measured pressure and temperature value from sensor, calculate pressure [ PSI ] and temperature [ �C ],
> results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec when the data value changes.

```c

void application_task (  )
{
    float temperature;
    float pressure;

    temperature = manometer2_get_temperature( &manometer2, MANOMETER2_CONVERT_4096 );
    Delay_10ms( );

    pressure = manometer2_get_pressure( &manometer2, MANOMETER2_CONVERT_4096 );
    Delay_10ms( );

    log_printf( &logger, " Pressure :  %.2f PSI \r\n", pressure );
    log_printf( &logger, " Temperature: %.2f C \r\n", temperature );
    log_printf( &logger, "----------------------------- \r\n" );

    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Manometer2

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
