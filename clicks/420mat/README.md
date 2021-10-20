\mainpage Main Page
 
 

---
# 4-20 mA T click

4-20mA T Click is an add-on board in mikroBUS form factor. It’s a compact and easy solution for adding 4-to-20mA industry standard communication protocol to your design

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/420mat_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/4-20ma-t-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the C420mat Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for C420mat Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c420mat_cfg_setup ( c420mat_cfg_t *cfg ); 
 
- Initialization function.
> C420MAT_RETVAL c420mat_init ( c420mat_t *ctx, c420mat_cfg_t *cfg );



#### Example key functions :

- This function sets the output of DAC.
> void c420mat_dac_output ( c420mat_t *ctx, uint16_t value_dac );
 
- This function sets the output current to selected value.
> void c420mat_set_i_out ( c420mat_t *ctx, uint8_t i_out );


## Examples Description

> This aplication changes the value of the output current.

**The demo application is composed of two sections :**

### Application Init 

> Initializes click SPI driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c420mat_cfg_t cfg;

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

    c420mat_cfg_setup( &cfg );
    C420MAT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c420mat_init( &c420mat, &cfg );
}
  
```

### Application Task

> Periodically changes Iout value.

```c

void application_task ( void )
{
   c420mat_set_i_out( &c420mat, 56 );                   // sets Iout to 5.6mA
   Delay_ms( 3000 );
   c420mat_set_i_out( &c420mat, 158 );                  // sets Iout to 15.8mA
   Delay_ms( 3000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.C420mat

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
