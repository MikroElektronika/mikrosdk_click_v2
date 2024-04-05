
# Opto 2 click

Opto 2 click is a galvanic isolator Click board™, used to provide an optical isolation of sensitive microcontroller (MCU) pins, when operated by external signals.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/opto2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/opto-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Opto2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Opto2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void opto2_cfg_setup ( opto2_cfg_t *cfg ); 
 
- Initialization function.
> OPTO2_RETVAL opto2_init ( opto2_t *ctx, opto2_cfg_t *cfg );

#### Example key functions :

- OUT1 Check function.
> uint8_t opto2_check_out1 ( opto2_t *ctx );
 
- OUT2 Check function.
> uint8_t opto2_check_out2 ( opto2_t *ctx );

- OUT3 Check function.
> uint8_t opto2_check_out3 ( opto2_t *ctx );

## Examples Description

> This application used to provide an optical isolation of sensitive microcontroller. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes device selects the outputs (OUT1 - OUT4) which state be checked. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto2_cfg_t cfg;

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

    opto2_cfg_setup( &cfg );
    OPTO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto2_init( &opto2, &cfg );

    log_info( &logger, "---- Application Init ----" );

    opto2_set_logger( 1, 1, 0, 0 );
    log_printf( &logger, "OPTO 2 is initialized \r\n" );
    log_printf( &logger, "" );
    Delay_ms ( 200 );
}
  
```

### Application Task

> Performs the check procedure for selected outputs and logs the states from that
  outputs on USB UART. Repeat the check procedure every 2 seconds.

```c

void application_task ( void )
{
    tmp = 1;

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( sel_output & tmp )
        {
            case 0x01 :
            {
                check_output = opto2_check_out1( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT1 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT1 is high %d\r\n" );
                }
                break;
            }
            case 0x02 :
            {
                check_output = opto2_check_out2( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT2 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT2 is high %d\r\n" );
                }
                break;
            }
            case 0x04 :
            {
                check_output = opto2_check_out3( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT3 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT3 is high %d\r\n" );
                }
                break;
            }
            case 0x08 :
            {
                check_output = opto2_check_out4( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT4 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT4 is high %d\r\n" );
                }
                break;
            }
            default :
            {
                break;
            }
        }

    tmp <<= 1;
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto2

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
