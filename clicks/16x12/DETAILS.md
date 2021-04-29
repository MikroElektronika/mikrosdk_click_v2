
---
# 16x12 click

16x12 G click carries a 16x12 LED display and the IS31FL3733 matrix driver. The click is designed to run on either 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/16x12g_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/16x12-g-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the 16x12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 16x12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c16x12_cfg_setup ( c16x12_cfg_t *cfg ); 
 
- Initialization function.
> C16X12_RETVAL c16x12_init ( c16x12_t *ctx, c16x12_cfg_t *cfg );

- Click Default Configuration function.
> void c16x12_default_cfg ( c16x12_t *ctx );


#### Example key functions :

- Functions for display Image 
> void c16x12g_display_image ( c16x12_t *ctx, uint16_t *pImage );

- Functions for display one Byte
> void c16x12g_display_byte ( c16x12_t *ctx, char ch );

- Functions for display text with scroll 
> void c16x12g_display_text ( c16x12_t *ctx, char *p_text, uint8_t n_char, uint8_t speed );

## Examples Description

>  This application draw object with led diodes.

**The demo application is composed of two sections :**

### Application Init 

> Initialization default device configuration, sets LED mode, 
> configuration ABM and display one character.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c16x12_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c16x12_cfg_setup( &cfg );
    C16X12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c16x12_init( &c16x12, &cfg );

    c16x12g_device_reset( &c16x12 );
    Delay_ms( 1000 );

    c16x12_default_cfg( &c16x12 );
    c16x12g_set_global_current_control( &c16x12, 255 );
    c16x12g_set_leds_mode( &c16x12, C16X12G_LED_MODE_ABM1 );

    abm_1.time_1     = C16X12G_ABM_T1_840MS;
    abm_1.time_2     = C16X12G_ABM_T2_840MS;
    abm_1.time_3     = C16X12G_ABM_T3_840MS;
    abm_1.time_4     = C16X12G_ABM_T4_840MS;
    abm_1.loop_begin = C16X12G_ABM_LOOP_BEGIN_T1;
    abm_1.loop_end   = C16X12G_ABM_LOOP_END_T3;
    abm_1.loop_times = C16X12G_ABM_LOOP_FOREVER;
    
    abm_2.time_1     = C16X12G_ABM_T1_210MS;
    abm_2.time_2     = C16X12G_ABM_T2_0MS;
    abm_2.time_3     = C16X12G_ABM_T3_210MS;
    abm_2.time_4     = C16X12G_ABM_T4_0MS;
    abm_2.loop_begin = C16X12G_ABM_LOOP_BEGIN_T1;
    abm_2.loop_end   = C16X12G_ABM_LOOP_END_T3;
    abm_2.loop_times = C16X12G_ABM_LOOP_FOREVER;

    c16x12g_configABM( &c16x12, C16X12G_ABM_NUM_1, &abm_1 );
    c16x12g_startABM( &c16x12 );
    
    c16x12g_displayByte( &c16x12, 'G' );
    Delay_ms( 11000 );
    
    c16x12g_configABM( &c16x12, C16X12G_ABM_NUM_1, &abm_2 );
    c16x12g_startABM( &c16x12 );
}
  
```

### Application Task

> Clear display, display one by one leds, display one character,
> display image and display text with scroll


```c

void applicationTask ( void )
{
    uint8_t cnt = 0;

    c16x12g_clear_display( &c16x12 );

    // Display point
    for ( cnt = 1; cnt <= 12; cnt++ )
    {
        c16x12g_set_led( &c16x12, cnt, cnt, C16X12G_LED_STATE_ON, C16X12G_STOP_SETTINGS );
        Delay_ms( 200 );
    }
    Delay_ms( 3000 );

    c16x12g_display_byte( &c16x12, 'G' );
    Delay_ms( 3000 );

    c16x12g_display_image( &c16x12, &demo_image_light[ 0 ] );
    Delay_ms( 3000 );
    
    c16x12g_display_image( &c16x12, &demo_image_dark[ 0 ] );
    Delay_ms( 3000 );
    
    c16x12g_display_text( &c16x12, &demo_text[ 0 ], 16, scroll_speed );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.16x12

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
