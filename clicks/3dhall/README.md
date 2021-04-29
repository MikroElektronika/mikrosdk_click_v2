\mainpage Main Page
 
---
# 3D Hall click

3D Hall click carries the MLX90333 Triaxis Hall sensor, capable of detecting the position of any magnet in nearby space. It does so by being sensitive to three components of flux density (BX, BY, BZ)

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the c3DHall Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c3DHall Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3dhall_cfg_setup ( c3dhall_cfg_t *cfg ); 
 
- Initialization function.
> C3DHALL_RETVAL c3dhall_init ( c3dhall_t *ctx, c3dhall_cfg_t *cfg );


#### Example key functions :

- Read 8 bytes data from sensor function.
> void c3dhall_read_all_data ( c3dhall_t *ctx, c3dhall_all_data_t *all_data );
 
- Calculate angle function.
> uint8_t c3dhall_calculate_angle ( c3dhall_t *ctx, uint16_t data_angle );

## Examples Description

> This application use to determine angle position.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - SPI and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall_cfg_t cfg;
    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall_cfg_setup( &cfg );
    C3DHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall_init( &c3dhall, &cfg );
    Delay_100ms( );
}
  
```

### Application Task

> This is a example which demonstrates the use of 3D Hall Click board. 
> 3D Hall Click communicates with register via SPI by read data from register and calculate Alpha and Beta angle position. 
> Results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart.

```c

void application_task ( void )
{
    c3dhall_all_data_t all_data;

    uint8_t angle_alpha;
    uint8_t angle_beta;

    c3dhall_read_all_data( &c3dhall, &all_data );
    Delay_100ms( );

    if ( ( all_data.data_error ) == C3DHALL_NO_ERRORS )
    {
        angle_alpha = c3dhall_calculate_angle( &c3dhall, all_data.data_angle_a );
        angle_beta = c3dhall_calculate_angle( &c3dhall, all_data.data_angle_b );
        
        log_printf( &logger, "     Alpha : %u\r\n", ( uint16_t ) angle_alpha );

        log_printf( &logger, "     Beta  : %u\r\n", ( uint16_t ) angle_beta );

        log_printf( &logger, "-------------------------\r\n", angle_beta );
    }
    else
    {
        if ( all_data.data_error == C3DHALL_F_ADCMONITOR )
            log_printf( &logger, "       ADC Failure       \r\n" );
        else if ( all_data.data_error == C3DHALL_F_ADCSATURA )
            log_printf( &logger, "    Electrical failure   \r\n"  );
        else if ( all_data.data_error == C3DHALL_F_GAINTOOLOW )
            log_printf( &logger, "    Gain code is less    \r\n" );
        else if ( all_data.data_error == C3DHALL_F_GAINTOOHIGH )
            log_printf( &logger, "   Gain code is greater  \r\n" );
        else if ( all_data.data_error == C3DHALL_F_NORMTOOLOW )
            log_printf( &logger, "   Fast norm below 30   \r\n" );
        else if ( all_data.data_error == C3DHALL_F_FIELDTOOLOW )
            log_printf( &logger, "     The norm is less    \r\n" );
        else if ( all_data.data_error == C3DHALL_F_FIELDTOOHIGH )
            log_printf( &logger, "   The norm is greater   \r\n" );
        else if ( all_data.data_error == C3DHALL_F_ROCLAMP )
            log_printf( &logger, "  Analog Chain Rough off \r\n" );
        else if ( all_data.data_error == C3DHALL_F_DEADZONEALPHA )
            log_printf( &logger, " Angle ALPHA in deadzone \r\n" );
        else if ( all_data.data_error == C3DHALL_F_DEADZONEBETA )
            log_printf( &logger, "  Angle BETA in deadzone \r\n" );
        else if ( all_data.data_error == C3DHALL_MULTIPLE_ERRORS )
            log_printf( &logger, "   More than one error   \r\n" );
        else
            log_printf( &logger, "      Unknown error      \r\n" );

        log_printf( &logger, "-------------------------\r\n" );
        Delay_1sec( );
    }
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.c3DHall

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
