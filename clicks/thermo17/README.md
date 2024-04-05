\mainpage Main Page
 
---
# Thermo 17 click

The Thermo 17 Click is a Click board™ based on the TMP451-Q1, a high-accuracy, lowpower remote temperature sensor monitor with a built-in local temperature sensor from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo17_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-17-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo17 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo17 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo17_cfg_setup ( thermo17_cfg_t *cfg ); 
 
- Initialization function.
> THERMO17_RETVAL thermo17_init ( thermo17_t *ctx, thermo17_cfg_t *cfg );


#### Example key functions :

- This function reads data from the desired register.
> uint8_t thermo17_generic_read ( thermo17_t *ctx,  uint8_t reg_adr );

- This function writes data to the desired register.
> void thermo17_generic_write ( thermo17_t *ctx, uint8_t reg_adr, uint8_t write_data );
 
- This function reads data from the local or remote registers.
> float thermo17_read_temp ( thermo17_t *ctx, uint8_t temp_macro );

## Examples Description

> This demo-app shows local and remote temperature measurement procedure using Thermo 17 click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization of the device and checks ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo17_cfg_t cfg;
    uint8_t id_data;

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

    //  Click initialization.

    thermo17_cfg_setup( &cfg );
    THERMO17_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo17_init( &thermo17, &cfg );

    id_data = thermo17_generic_read( &thermo17 ,THERMO17_REG_R_ID );
    
    if ( id_data == THERMO17_DEV_ID )
    {
        log_info( &logger, " - Correct device ID" );
    }
    else
    {
        log_info( &logger, " - Device ID ERROR" );
        for ( ; ; );
    }

    log_info( &logger, " Starting measurement " );
}
  
```

### Application Task

> Appliction measures temp value every 1000ms and logs it.

```c

void application_task ( void )
{
    float read_data;

    read_data = thermo17_read_temp( &thermo17 ,THERMO17_TEMPERATURE_LOCAL );
    log_printf( &logger, " - LOCAL: : %.2f C\r\n", read_data );

    Delay_ms ( 100 );

    read_data = thermo17_read_temp( &thermo17 ,THERMO17_TEMPERATURE_REMOTE );
    log_printf( &logger, " - REMOTE: : %.2f C\r\n", read_data );
    
    Delay_ms ( 100 );
    log_printf( &logger, " ******************** \r\n" );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo17

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
