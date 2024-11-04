\mainpage Main Page
 
---
# IR Sense 2 Click

IR Sense 2 Click is the infrared sensor Click board™, designed to be used for the short range IR sensing applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irsense2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-sense-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the IrSense2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrSense2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irsense2_cfg_setup ( irsense2_cfg_t *cfg ); 
 
- Initialization function.
> IRSENSE2_RETVAL irsense2_init ( irsense2_t *ctx, irsense2_cfg_t *cfg );

- Click Default Configuration function.
> void irsense2_default_cfg ( irsense2_t *ctx );


#### Example key functions :

- This function reads and returns 16bit value from the IR senor.
> int16_t irsense2_get_ir_data ( irsense2_t *ctx );
 
- This function calculates differences in read IR sensor data and
- determines if there was a presence that tireggered a change.
> uint8_t irsense_human_detected ( irsense2_t *ctx, float ir_data );

- This function reads from interrupt factor information register.
> void irsense2_get_int ( irsense2_t *ctx );

## Examples Description

> This application enables usage of IR sensor for presence detection.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense2_cfg_t cfg;

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

    irsense2_cfg_setup( &cfg );
    IRSENSE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense2_init( &irsense2, &cfg );

    Delay_us( 100 );
    
    irsense2_default_cfg ( &irsense2 );
}
  
```

### Application Task

> Fetches IR and temperature sensor data and prints them on terminal.

```c

void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float ir_data;
    uint8_t flag;

    Delay_ms ( 400 );

    irsense2_data_read( &irsense2, &ir_data, &temperature );

    flag = irsense_human_detected( &irsense2, ir_data );
    
    if( flag == 1 )
    {   log_printf( &logger, " \r\n----------------------------- \r\n");
        log_printf( &logger, "\r\n Person detected!!! \r\n" );
        log_printf( &logger, " \r\n----------------------------- \r\n");
        Delay_ms ( 300 );
    }

    log_printf( &logger, "\r\n\r\nIR Value:       %.2f  pA ", ir_data );
    log_printf( &logger, " \r\n----------------------------- \r\n");
    log_printf( &logger, "Temperature: %.8f  C \r\n", temperature );

    Delay_ms ( 1000 );
}
 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrSense2

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
