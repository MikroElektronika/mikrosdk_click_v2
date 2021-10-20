\mainpage Main Page
 
 

---
# Touch Key 4 click

Touch Key 4 click is a capacitive touch sensing Click board™, with the advanced touch/proximity sensor IC. It has three independently configurable channels and can work in several operating modes, including multiple button pattern detection mode, combo mode, press and hold detection mode, power button mode, and more. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchkey4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/touch-key-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TouchKey4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TouchKey4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void touchkey4_cfg_setup ( touchkey4_cfg_t *cfg ); 
 
- Initialization function.
> TOUCHKEY4_RETVAL touchkey4_init ( touchkey4_t *ctx, touchkey4_cfg_t *cfg );

- Click Default Configuration function.
> void touchkey4_default_cfg ( touchkey4_t *ctx );


#### Example key functions :

- This function detects touch on sensor inputs and checks is touch detected or released.
> void touchkey4_detect_touch( touchkey4_t *ctx, uint8_t *input_sens );

 
- This function puts device in Active mode and enables desired inputs in Active mode.
> void touchkey4_set_active_mode( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1,const uint8_t en_input2, const uint8_t en_input3 );


- This function puts device in Standby mode and enables desired inputs in Standby mode.
> void touchkey4_set_standby_mode( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1, const uint8_t en_input2, const uint8_t en_input3 );


## Examples Description

> This demo performs touch & release detection functionality of the Click. 

**The demo application is composed of two sections :**

### Application Init 

> Device and driver initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey4_cfg_t cfg;

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

    touchkey4_cfg_setup( &cfg );
    TOUCHKEY4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey4_init( &touchkey4, &cfg );

    Delay_ms( 1000 );
    
    touchkey4_default_cfg( &touchkey4 );
    log_info( &logger, "---- Configured and ready ----" );
}
  
```

### Application Task

> Calls function to check touch detection (is interrupt occured) and shows message on 
> USB UART if touch is detected or if touch is released on enabled inputs.

```c

void application_task ( void )
{
    touchkey4_detect_touch( &touchkey4, sensor_results );
    for ( cnt = 0; cnt < 3; cnt++ )
    {
        if ( sensor_results[ cnt ] == 1 )
        {
            if ( cnt == 0 )
            {
                log_info( &logger, "Input 1 is touched\r\n" );
            }
            else if ( cnt == 1 )
            {
                log_info( &logger, "Input 2 is touched\r\n" );
            }
            else
            {
                log_info( &logger, "Input 3 is touched\r\n" );
            }
        }
        else if ( sensor_results[ cnt ] == 2 )
        {
            if ( cnt == 0 )
            {
                log_info( &logger, "Input 1 is released\r\n" );
            }
            else if ( cnt == 1 )
            {
                log_info( &logger, "Input 2 is released\r\n" );
            }
            else
            {
                log_info( &logger, "Input 3 is released\r\n" );
            }
        }
    }
    Delay_ms( 300 );
} 

```

## Note

> TouchKey 4 is configured to work in Combo mode (Active and Standby mode). Input 1 is
> enabled in Active mode, input 3 is enabled in Standby mode, and input 2 is enabled to
> work in both modes. In this example the interrupt will be generated when touch is
> detected and when touch is released. 
> Standby mode should be used when fewer sensor inputs are enabled, and when
> they are programmed to have more sensitivity.
> Somethimes it is neccessary to cycle the board power supply if click doesn't work. 


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchKey4

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
