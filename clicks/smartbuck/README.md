\mainpage Main Page
 
 

---
# Smart Buck click

Smart Buck click is the two-channel step-down DC/DC converter and regulator, with plenty of additional functions. It can provide voltage measurement at each of its two programmable voltage outputs, as well as the measurement of the current consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartbuck_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/smart-buck-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Smart Buck Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Smart Buck Click driver.

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

> This application reads voltage, current, and power from all available channels.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and logger and peforms the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    smartbuck_cfg_t cfg;

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

    smartbuck_cfg_setup( &cfg );
    SMARTBUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smartbuck_init( &smartbuck, &cfg );
    smartbuck_default_cfg( &smartbuck );
}   
  
```

### Application Task

> Sends command for updating data registers with new converted data, 
> then waits 500ms and after that reads new data from data registers. 
> In this way we can get voltage, current and power data from activated channels.
> Results are being logged on USB UART.

```c

void application_task ( void )
{
    smartbuck_send_cmd_pac( &smartbuck, SMARTBUCK_REFRESH_V_CMND );
    Delay_ms( 500 );
    smartbuck_get_data( &smartbuck, &voltage_res[ 0 ], &current_res[ 0 ], &power_res[ 0 ] );
    
    check_byte = 0x80;
    idx = 0;
    
    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( ( smartbuck.enabled_chann & check_byte ) == 0 )
        {
            channel_log();
            
            log_printf( &logger, "U: %.2f V    ", voltage_res[ idx ] );
            log_printf( &logger, "I: %.2f mA    ", current_res[ idx ] );
            log_printf( &logger, "P: %.2f mW    ", power_res[ idx ] );
            
            idx++;
        }
        check_byte >>= 1;
    }
    
    log_printf( &logger, "\n");
}
 

```

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
