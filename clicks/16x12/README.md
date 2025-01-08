
---
# 16x12 Click

> [16x12 G Click](https://www.mikroe.com/?pid_product=MIKROE-2758) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2758&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

>  This application draw object with led diodes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.16x12

### Example Key Functions

- `c16x12_cfg_setup` Config Object Initialization function. 
```c
void c16x12_cfg_setup ( c16x12_cfg_t *cfg );
``` 
 
- `c16x12_init` Initialization function. 
```c
err_t c16x12_init ( c16x12_t *ctx, c16x12_cfg_t *cfg );
```

- `c16x12_default_cfg` Click Default Configuration function. 
```c
void c16x12_default_cfg ( c16x12_t *ctx );
```

- `c16x12g_display_image` Functions for display Image . 
```c
void c16x12g_display_image( c16x12_t *ctx, uint16_t *pImage );
```

- `c16x12g_display_byte` Functions for display one Byte. 
```c
void c16x12g_display_byte( c16x12_t *ctx, char ch );
```

- `c16x12g_display_text` Functions for display text with scroll . 
```c
void c16x12g_display_text( c16x12_t *ctx, char *p_text, uint8_t n_char, uint8_t speed );
```

### Application Init

> Initialization default device configuration, sets LED mode, 
> configuration ABM and display one character.


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c16x12_cfg_t cfg;

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

    c16x12_cfg_setup( &cfg );
    C16X12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c16x12_init( &c16x12, &cfg );

    c16x12g_device_reset( &c16x12 );
    Delay_ms ( 1000 );

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
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
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
        Delay_ms ( 200 );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x12g_display_byte( &c16x12, 'G' );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x12g_display_image( &c16x12, &demo_image_light[ 0 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    c16x12g_display_image( &c16x12, &demo_image_dark[ 0 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    c16x12g_display_text( &c16x12, &demo_text[ 0 ], 16, scroll_speed );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
