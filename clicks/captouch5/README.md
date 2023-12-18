\mainpage Main Page
 
 

---
# Cap Touch 5 click

Cap Touch 5 Click is a capacitive touch sensing Click board™ which features the CY8CMBR3106S-LQXI CapSense® Express™ controller which enables advanced, yet easy-to-implement, capacitive touch sensing user interface solutions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/captouch5_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/cap-touch-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the CapTouch5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapTouch5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void captouch5_cfg_setup ( captouch5_cfg_t *cfg ); 
 
- Initialization function.
> CAPTOUCH5_RETVAL captouch5_init ( captouch5_t *ctx, captouch5_cfg_t *cfg );

- Click Default Configuration function.
> void captouch5_default_cfg ( captouch5_t *ctx );


#### Example key functions :

- This function reads button status.
> void captouch5_read_button_status ( captouch5_t *ctx, T_CAPTOUCH5_BUTTONS *buttons );
 
- This function reads slider position.
> uint16_t captouch5_read_slider_position ( captouch5_t *ctx );


## Examples Description

> This example is waiting for touch sensor to detect something and then logs what is touched.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C module and driver, tests communication and configures device. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch5_cfg_t cfg;

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

    captouch5_cfg_setup( &cfg );
    CAPTOUCH5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch5_init( &captouch5, &cfg );
    captouch5_default_cfg ( &captouch5, &device_cfg );
}
  
```

### Application Task

Waiting for touch sensor to detect something and then logs what is touched.

```c

void application_task ( void )
{
    uint16_t temp_byte;
    uint16_t last_temp;
    uint8_t temp_slider;

    state_check = 0;

    if ( CAPTOUCH5_ERROR == captouch5_process( &captouch5 ) )
    {
        log_printf( &logger, "***** ERROR *****" );
        state_check = 1;
        return;
    }

    temp_byte = captouch5_read_slider_position( &captouch5 );
    captouch5_read_button_status( &captouch5, &buttons );

    if ( temp_byte != last_temp )
    {
        log_printf( &logger, "Slider position value: %u \r\n", temp_byte );
        last_temp = temp_byte;
        state_check = 1;
    }

    captouch5_read_buttons(  );

    Delay_ms ( 100 );

    if ( state_check == 1 )
    {
        log_info( &logger, "--- Waiting for command ---\r\n" );
    }
}

```

## Note

> Click will go to sleep if doesn't get any command in 340ms.
  When you start device try restarting your board few times to start device.
  The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or 
  found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch5

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
