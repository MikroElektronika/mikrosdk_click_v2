\mainpage Main Page
 
 

---
# Cap Touch 2 click

Cap Touch 2 click is a capacitive touch sensing Click board which features the CAP1166, an advanced touch/proximity sensor IC, packed with a range of different touch/proximity functionalities, allowing development of robust and aesthetically pleasing touch interfaces.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/captouch2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-touch-2-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the CapTouch2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapTouch2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void captouch2_cfg_setup ( captouch2_cfg_t *cfg ); 
 
- Initialization function.
> CAPTOUCH2_RETVAL captouch2_init ( captouch2_t *ctx, captouch2_cfg_t *cfg );

- Click Default Configuration function.
> void captouch2_default_cfg ( captouch2_t *ctx );


#### Example key functions :

- Touch Detect function
> void captouch2_detect_touch( captouch2_t *ctx, uint8_t *in_sens );
 
- Interrupt Check function
> uint8_t captouch2_check_interrupt( captouch2_t *ctx );

- Reset function
> void captouch2_reset( captouch2_t *ctx );

## Examples Description
 
> The demo application shows the button reading and checking.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Reset device and settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch2_cfg_t cfg;

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

    captouch2_cfg_setup( &cfg );
    CAPTOUCH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch2_init( &captouch2, &cfg );

    captouch2_reset( &captouch2 );
    Delay_ms( 200 );
    captouch2_default_cfg( &captouch2 );
    Delay_ms( 100 );
    log_info( &logger, ">> Cap Touch 2 is initialized " );
}
```

### Application Task

> Calls function to check touch detection (is interrupt occured) and shows message on
> USB UART on which input touch is detected or on which input touch is released. 
> Also turns on LED on which linked input interrupt occured.

```c
void application_task ( void )
{
    uint8_t cnt;
    uint8_t sensor_results[ 6 ];

    captouch2_detect_touch( &captouch2, &sensor_results[ 0 ] );
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( sensor_results[ cnt ] == 1 )
        {
            log_printf( &logger, "Input %d is touchedr\r\n", cnt + 1 );
        }
        else if ( sensor_results[ cnt ] == 2 )
        {
            log_printf( &logger, "Input %d is released\r\n", cnt + 1 );
        }
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch2

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
