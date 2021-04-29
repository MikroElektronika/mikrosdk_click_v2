\mainpage Main Page

---
# Buck 14 click

The Buck 14 Click is a Click board™ based around the BMR4613001/001, a PoL regulator from Flex. It's high-efficiency step-down converter which provides a highly regulated output voltage derived from the connected power source, rated from 4.5 to 14V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-14-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Buck14 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck14 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck14_cfg_setup ( buck14_cfg_t *cfg ); 
 
- Initialization function.
> BUCK14_RETVAL buck14_init ( buck14_t *ctx, buck14_cfg_t *cfg );

- Click Default Configuration function.
> void buck14_default_cfg ( buck14_t *ctx );


#### Example key functions :

- This function sets state of the power control pin on cs.
> void buck14_power_ctrl ( buck14_t *ctx, uint8_t state );
 
- This function gets manufacturer id.
> uint8_t buck14_salert ( buck14_t *ctx );

- This function sets output V.
> uint8_t buc14_write_vout ( buck14_t *ctx, float vout );

## Examples Description

> This app enables usage of high-efficiency step-down converter.

**The demo application is composed of two sections :**

### Application Init 

> Configure device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck14_cfg_t cfg;
    uint8_t write_data;
    uint8_t status_data;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck14_cfg_setup( &cfg );
    BUCK14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck14_init( &buck14, &cfg );

    buck14_reset( &buck14 );

    write_data  = BUCK14_CTRL_ENABLE_NO_MARGIN;
    buck14_generic_write( &buck14, BUCK14_CMD_OPERATION, write_data , 1 );
    Delay_ms( 300 );

    status_data = buck14_check_mfr_id(  &buck14 );
    error_handler( status_data );
    log_printf( &logger, "-Device ID OK!\r\n" );
    
    buck14_power_ctrl( &buck14, BUCK14_PIN_STATE_HIGH );

    buck14_default_cfg( &buck14 );
    log_printf( &logger, " ***** App init ***** \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> Sends 4 different commands for VOUT in span of 8sec

```c

void application_task ( void )
{
    uint8_t status_data;
    float vout_value;

    vout_value = 1.2;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }

    Delay_ms( 8000 );

    vout_value = 3.7;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data( &buck14 );
    }

    Delay_ms( 8000 );

    vout_value = 2.5;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }
    
    Delay_ms( 8000 );

    vout_value = 4.5;
    status_data = buc14_write_vout(  &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }
    
    Delay_ms( 4000 );
    log_printf( &logger, "```````````````\r\n" );
    Delay_ms( 4000 );
} 

```

## Note

> When you send data you should send LSB first.
> Device input V should be beetween 4.5 - 14 V.
> Device output V could be from 0.5 - 5 V deepending from limits you set currently it is set to 1V.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck14

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
