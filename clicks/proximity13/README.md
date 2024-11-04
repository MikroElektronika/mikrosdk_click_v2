\mainpage Main Page
 
---
# Proximity 13 Click

Proximity 13 Click based on SI1153-AB09-GMR IC from Silicon Labs that can be used as an proximity, and gesture detector with I2C digital interface and programmable-event interrupt output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity13_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-13-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity13 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity13 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity13_cfg_setup ( proximity13_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY13_RETVAL proximity13_init ( proximity13_t *ctx, proximity13_cfg_t *cfg );

- Click Default Configuration function.
> void proximity13_default_cfg ( proximity13_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> void proximity13_generic_write ( proximity13_t *ctx, uint8_t reg_adr, uint8_t write_data );
 
- This function reads data from the desired register.
> uint8_t proximity13_generic_read ( proximity13_t *ctx, uint8_t reg_adr );

- This function reads all enabled channels.
> void proximity13_read_channels ( proximity13_t *ctx, proximity13_chn_val_t *chn_val );

## Examples Description

> This demo application shows example for measuring close distance.

**The demo application is composed of two sections :**

### Application Init 

> Initialization of I2C module and additional pin, checks id of device, 
> configurates device for measuring 1. channel,
> and then sends command to start measuring.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity13_cfg_t cfg;
    uint8_t status;

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
    log_info( &logger, " Application Init" );

    //  Click initialization.

    proximity13_cfg_setup( &cfg );
    PROXIMITY13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity13_init( &proximity13, &cfg );
    
    status = proximity13_get_int_pin_status( &proximity13 );
    while ( status != PROXIMITY13_PIN_HIGH );

    status = porximity13_check_id( &proximity13 );
    if ( status == PROXIMITY13_OK )
    {
        log_info( &logger, " Device OK" );
    }
    else
    {
        log_info( &logger, " Device Error" );
        for ( ; ; );
    }
    
    log_info( &logger, " Setting default configuration" );
    proximity13_default_cfg ( &proximity13 );
    
    proximity13_send_command( &proximity13, PROXIMITY13_CMD_START );
    log_info( &logger, " Starting measurement" );
}
  
```

### Application Task

> Appliction measures values every 100ms and logs result.

```c

void application_task ( void )
{
    proximity13_chn_val_t chn_val;

    proximity13_read_channels( &proximity13, &chn_val );

    log_printf( &logger, " Data : %u\r\n", chn_val.channel_1 );

    Delay_ms ( 100 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity13

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
