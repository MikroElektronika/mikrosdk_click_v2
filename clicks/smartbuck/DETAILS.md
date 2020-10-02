
---
# SMART BUCK click

Smart Buck click is the two-channel step-down DC/DC converter and regulator, with plenty of additional functions. It can provide voltage measurement at each of its two programmable voltage outputs, as well as the measurement of the current consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartbuck_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/smart-buck-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the SMARTBUCK Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SMARTBUCK Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void smartbuck_cfg_setup ( smartbuck_cfg_t *cfg ); 
 
- Initialization function.
> SMARTBUCK_RETVAL smartbuck_init ( smartbuck_t *ctx, smartbuck_cfg_t *cfg );

- Click Default Configuration function.
> void smartbuck_default_cfg ( smartbuck_t *ctx );


#### Example key functions :

- Function performs the desired command for PAC1934.
> uint8_t smartbuck_send_cmd_PAC ( smartbuck_t *ctx, uint8_t command );
 
- Function reads and calculates the voltage, current and power data from PAC1934 activated channels.
> void smartbuck_get_data( smartbuck_t *ctx,  float *voltage, float *current, float *power );

- Function reads the desired number of bytes from the PAC1934 registers.
> uint8_t smartbuck_block_read_PAC( smartbuck_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes );

## Examples Description

> This example shows voltage, current and resistance of the selected channel.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and peforms the click configuration to work in Single-Shot Mode
> with signed averaged data of 64 samples. CH1 and CH3 are only activated and included in conversion cycle.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    smartbuck_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    smartbuck_cfg_setup( &cfg );
    SMARTBUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smartbuck_init( &smartbuck, &cfg );
    smartbuck_default_cfg( &smartbuck );

}   
  
```

### Application Task

> Sends command to update data registers with new converted data, waits one second and after that reads
> new data from data registers. On this way user can get voltage, current and power data for activated channels.
> Results for activated channels logs on uart terminal.

```c

void application_task ( void )
{
    smartbuck_send_cmd_PAC( &smartbuck, SMARTBUCK_REFRESH_V_CMND );
    Delay_ms( 1000 );
    smartbuck_get_data( &smartbuck, &voltage_res[0], &current_res[0], &power_res[0] );
    
    check_byte = 0x80;
    index = 0;
    
    for (cnt = 0; cnt < 4; cnt++)
    {
        if ((smartbuck.enabled_chann & check_byte) == 0)
        {
            channel_log();
            
            log_printf( &logger, "%f V ", voltage_res[ index ]);
            log_printf( &logger, "%f mA ", current_res[ index ]);
            log_printf( &logger, "%f mW ", power_res[ index ]);
            
            index++;
        }
        check_byte >>= 1;
    }
    
    log_printf( &logger, "\n");
}
 

```

## Note

> If we want to update registers with new converted data, after at least one conversion cycle is done, we should send first REFRESH or REFRESH_V command, before data be read, which will update registers with new values. Also these commands will update Control register with new desired configurations.
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub account.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SMARTBUCK

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
