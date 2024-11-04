
---
# DMX Click

> DMX Click is a device used to establish communication between the MCU and equipment that uses the DMX512-A communication protocol.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dmx_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dmx-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Dmx Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dmx Click driver.

#### Standard key functions :

- `dmx_cfg_setup` Config Object Initialization function.
```c
void dmx_cfg_setup ( dmx_cfg_t *cfg ); 
```

- `dmx_init` Initialization function.
```c
err_t dmx_init ( dmx_t *ctx, dmx_cfg_t *cfg );
```

#### Example key functions :

- `dmx_generic_write` Generic write function.
```c
void dmx_generic_write ( dmx_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `dmx_generic_read` Generic read function.
```c
err_t dmx_generic_read ( dmx_t *ctx, uint8_t *data_buf, uint16_t max_len );
```

- `dmx_send_cmd` Send command function.
```c
void dmx_send_cmd ( dmx_t* ctx, uint8_t *cmd );
```

## Examples Description

> This example demonstrates the use of the DMX Click board by showcasing the control for a 6-channel DMX RGB LED reflector connected to it.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dmx_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    dmx_cfg_setup( &cfg );
    DMX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dmx_init( &dmx, &cfg );

    dmx_set_auto_baud_rate( &dmx, 1 );
    Delay_ms ( 100 );

    dmx_reset( &dmx, DMX_MASTER );
    dmx_run( &dmx, DMX_CONFIG_MODE );
    Delay_ms ( 100 );
    
    dmx_process( );
    dmx_clear_app_buf( );

    // Clear the internal buffers
    dmx_send_cmd( &dmx, DMX_CMD_PURGEBFR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set start address
    dmx_send_cmd( &dmx, DMX_CMD_SADR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set input data buffer length
    dmx_send_cmd( &dmx, DMX_CMD_BLEN );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set DMX frame length
    dmx_send_cmd( &dmx, DMX_CMD_FLEN_MASTER );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set interrupt pulse duration
    dmx_send_cmd( &dmx, DMX_CMD_ITMR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set a time delay between two frames
    dmx_send_cmd( &dmx, DMX_CMD_FTMR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Display configuration
    dmx_send_cmd( &dmx, DMX_CMD_DISPLCFG );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );
    dmx_clear_app_buf( );
    
    dmx_run( &dmx, DMX_RUN_MODE );

    log_info( &logger, " Application Task " );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Performs the LEDs dimming control on a 6-channel DMX RGB LED reflector.

```c

void application_task ( void )
{
    uint8_t dmx_6_ch_buf[ 6 ] = { 0 };
    int16_t cnt = 0;
    
    dmx_6_ch_buf[ 0 ] = 255; // Dimmer
    dmx_6_ch_buf[ 1 ] = 0;   // Red
    dmx_6_ch_buf[ 2 ] = 0;   // Green
    dmx_6_ch_buf[ 3 ] = 0;   // Blue
    dmx_6_ch_buf[ 4 ] = 0;   // Strobe
    dmx_6_ch_buf[ 5 ] = 0;   // Macro
    
    log_printf( &logger, "\r\nDimming RED LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 1 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 1 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    log_printf( &logger, "Dimming GREEN LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 2 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 2 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    log_printf( &logger, "Dimming BLUE LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 3 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 3 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    dmx_6_ch_buf[ 1 ] = 255;
    dmx_6_ch_buf[ 2 ] = 255;
    dmx_6_ch_buf[ 3 ] = 255;
    log_printf( &logger, "Dimming all LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 0 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 0 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dmx

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
