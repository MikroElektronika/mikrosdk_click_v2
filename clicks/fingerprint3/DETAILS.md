
---
# Fingerprint 3 click

Fingerprint 3 Click is an adapter Click board™, used to interface a compatible Fingerprint Sensor with Two-Color LED Ring with the host MCU.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/fingerprint-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Fingerprint3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fingerprint3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fingerprint3_cfg_setup ( fingerprint3_cfg_t *cfg ); 
 
- Initialization function.
> FINGERPRINT3_RETVAL fingerprint3_init ( fingerprint3_t *ctx, fingerprint3_cfg_t *cfg );

#### Example key functions :

- Response parser and display function.
> void fingerprint3_parser_and_display_rsp ( fingerprint3_rsp_t *response );
 
- Response parser function.
> void fingerprint3_parser_rsp ( fingerprint3_rsp_t *response );

- Finger indicator function.
> uint8_t fingerprint3_finger_indicator ( fingerprint3_t *ctx );

## Examples Description

> This example reads and processes data from Fingerprint 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fingerprint3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fingerprint3_cfg_setup( &cfg );
    FINGERPRINT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fingerprint3_init( &fingerprint3, &cfg );

    log_printf( &logger, "--------------------------------- \r\n" );
    log_printf( &logger, "       Fingerprint 3 click        \r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
    Delay_ms( 500 );

    fingerprint3_generic_write( &fingerprint3, &check_sensor[ 0 ], 12 );
    log_printf( &logger, "        Check the sensor          \r\n" );
    fingerprint3_parser_rsp( &rsp );
    fingerprint3_display_rsp( );
    log_printf( &logger, "--------------------------------- \r\n" );
    Delay_ms( 3000 );

    fingerprint3_generic_write( &fingerprint3, &vfy_pwd[ 0 ], 16 );
    log_printf( &logger, "     Verify Module Password       \r\n" );
    fingerprint3_parser_rsp( &rsp );
    fingerprint3_display_rsp( );
    log_printf( &logger, "--------------------------------- \r\n" );
    Delay_ms( 3000 );

    log_printf( &logger, " >>>  Register fingerprint  <<<   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
    log_printf( &logger, " Place your finger on the sensor  \r\n" );


    while ( fingerprint3_finger_indicator( &fingerprint3 ) == FINGERPRINT3_DETECT_NO_FINGER )
    {
        fingerprint3_generic_write( &fingerprint3, &aura_led_config_purple[ 0 ], 16 );
        Delay_ms( 2000 );
    }

    log_printf( &logger, "--------------------------------- \r\n" );
    log_printf( &logger, "    Add fingerprint process...    \r\n" );
    fingerprint3_buf_clear( );
    fingerprint3_generic_write( &fingerprint3, &gen_img[ 0 ], 12 );
    Delay_ms( 500 );
    fingerprint3_parser_rsp( &rsp );

    if ( rsp.confirm_code == FINGERPRINT3_OK )
    {
        fingerprint3_generic_write( &fingerprint3, &img_2_tz_1[ 0 ], 13 );
        Delay_ms( 2000 );
        
        log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
        log_printf( &logger, "      Scanning is complete        \r\n" );
        log_printf( &logger, "--------------------------------- \r\n" );
        Delay_ms( 1000 );
    }

    fingerprint3_buf_clear( );
    log_printf( &logger, "  >>> Comparing Fingerprints <<<  \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
    log_printf( &logger, " Place your finger on the sensor  \r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    if ( fingerprint3_finger_indicator( &fingerprint3 ) == FINGERPRINT3_DETECT_FINGER )
    {
        fingerprint3_buf_clear( );
        log_printf( &logger, "--------------------------------- \r\n" );
        log_printf( &logger, " >>> Verification in progress...  \r\n" );
        Delay_ms( 2000 );

        fingerprint3_generic_write( &fingerprint3, &gen_img[ 0 ], 12 );
        Delay_ms( 500 );
        fingerprint3_parser_rsp( &rsp );
        Delay_ms( 100 );

        if ( rsp.confirm_code == FINGERPRINT3_OK )
        {
            fingerprint3_generic_write( &fingerprint3, &img_2_tz_2[ 0 ], 13 );
            Delay_ms( 500 );
            fingerprint3_buf_clear( );
        }

        fingerprint3_generic_write( &fingerprint3, &reg_model[ 0 ], 12 );
        Delay_ms( 100 );
        fingerprint3_buf_clear( );

        fingerprint3_generic_write( &fingerprint3, &fingerprint_match[ 0 ], 12 );
        Delay_ms( 500 );
        fingerprint3_parser_rsp( &rsp );
        fingerprint3_display_match_score( );
        Delay_ms( 3000 );

        log_printf( &logger, "  >>> Comparing Fingerprints <<<  \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
        log_printf( &logger, " Place your finger on the sensor  \r\n" );
    }
    else
    {
        fingerprint3_generic_write( &fingerprint3, &aura_led_config_purple[ 0 ], 16 );
        Delay_ms( 2000 );
        fingerprint3_buf_clear( );
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fingerprint3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
