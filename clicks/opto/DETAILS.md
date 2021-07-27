

---
# OPTO click

OPTO Click is an accessory board in mikroBUS form factor. It features two VO2630 dual channel, high speed optocoupler modules.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/opto_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/opto-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the OPTO Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OPTO Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void opto_cfg_setup ( opto_cfg_t *cfg ); 
 
- Initialization function.
> OPTO_RETVAL opto_init ( opto_t *ctx, opto_cfg_t *cfg );

- Click Default Configuration function.
> void opto_default_cfg ( opto_t *ctx );


#### Example key functions :

- Function checks the state of OUT1 pin.
> uint8_t opto_check_out1( opto_t *ctx );
 
- Function checks the state of OUT2 pin.
> uint8_t opto_check_out2( opto_t *ctx );

- Function checks the state of OUT3 pin.
> uint8_t opto_check_out3( opto_t *ctx );

- Function checks the state of OUT4 pin.
> uint8_t opto_check_out4( opto_t *ctx );

## Examples Description

> This example checks the state of selected inputs and prints it.


**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO and also starts write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    opto_cfg_setup( &cfg );
    OPTO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto_init( &opto, &cfg );
    opto_set_logger(1,1,1,1);
}
  
```

### Application Task

> This example demonstrates the use of OPTO Click board by performing
> the check procedure for selected outputs and displays the results on USART terminal.

```c

void application_task ( void )
{
    tmp = 1;

    for( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( sel_output & tmp )
        {
            case 0x01 :
            {
                check_output = opto_check_out1( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT1 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT1 is high\r\n" );
                }
            break;
            }
            case 0x02 :
            {
                check_output = opto_check_out2( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT2 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT2 is high\r\n" );
                }
            break;
            }
            case 0x04 :
            {
                check_output = opto_check_out3( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT3 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT3 is high\r\n" );
                }
            break;
            }
            case 0x08 :
            {
                check_output = opto_check_out4( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT4 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT4 is high\r\n" );
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
    Delay_ms( 2000 );
}
```



The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OPTO

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
