\mainpage Main Page
 
---
# Driver click

Driver Click features an IC with seven integrated high-current sink drivers, which can be used to drive a wide range of loads via simple parallel interface. These integrated drivers use high-efficiency MOSFETs for improved thermal performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/driver_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/driver-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Driver Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Driver Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void driver_cfg_setup ( driver_cfg_t *cfg ); 
 
- Initialization function.
> DRIVER_RETVAL driver_init ( driver_t *ctx, driver_cfg_t *cfg );


#### Example key functions :

- IN1 Set function.
> void driver_set_in1 ( driver_t *ctx, uint8_t state );
 
- IN2 Set function.
> void driver_set_in2 ( driver_t *ctx, uint8_t state );

- IN3 Set function.
> void driver_set_in3 ( driver_t *ctx, uint8_t state );

## Examples Description
 
> This application offering a nine-pole spring terminal that can be used to implement and realize a wide range of different applications 

**The demo application is composed of two sections :**

### Application Init 


> Initializes GPIO driver and selects which inputs will be set in operation.
   Bits from 0 to 6 (selectIN) select inputs from IN1 to IN7, respectively.
 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    driver_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    driver_cfg_setup( &cfg );
    DRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    driver_init( &driver, &cfg );
}
  
```

### Application Task

> Performs cycles in which selected inputs will be turned on for pulseWidth
   delay time one by one. When one input is turned on, it will be turned off after desired delay time before the next input be turned on.

```c

void application_task ( void )
{
    uint8_t select_in;
    uint8_t temp;
    uint8_t count;

    select_in = 0x7F;
    temp = 1;
    
    for (count = 0; count < 7; count++)
    {
        switch ( select_in & temp )
        {
            case 0x01 :
            {
                driver_set_in1( &driver, ENABLE_IN );
                log_printf( &logger, "OUT1 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in1( &driver, DISABLE_IN );
                log_printf( &logger, "OUT1 disabled\r\n" );
                break;
            }
            case 0x02 :
            {
                driver_set_in2( &driver, ENABLE_IN );
                log_printf( &logger, "OUT2 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in2( &driver, DISABLE_IN );
                log_printf( &logger, "OUT2 disabled\r\n" );
                break;
            }
            case 0x04 :
            {
                driver_set_in3( &driver, ENABLE_IN );
                log_printf( &logger, "OUT3 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in3( &driver, DISABLE_IN );
                log_printf( &logger, "OUT3 disabled\r\n" );
                break;
            }
            case 0x08 :
            {
                driver_set_in4( &driver, ENABLE_IN );
                log_printf( &logger, "OUT4 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in4( &driver, DISABLE_IN );
                log_printf( &logger, "OUT4 disabled\r\n" );
                break;
            }
            case 0x10 :
            {
                driver_set_in5( &driver, ENABLE_IN );
                log_printf( &logger, "OUT5 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in5( &driver, DISABLE_IN );
                log_printf( &logger, "OUT5 disabled\r\n" );
                break;
            }
            case 0x20 :
            {
                driver_set_in6( &driver, ENABLE_IN );
                log_printf( &logger, "OUT6 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in6( &driver, DISABLE_IN );
                log_printf( &logger, "OUT6 disabled\r\n" );
                break;
            }
            case 0x40 :
            {
                driver_set_in7( &driver, ENABLE_IN );
                log_printf( &logger, "OUT7 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in7( &driver, DISABLE_IN );
                log_printf( &logger, "OUT7 disabled\r\n" );
                break;
            }
            default :
            {
                break;
            }
        }
        log_printf( &logger, "----------------------\r\n" );
        temp <<= 1;
        
        Delay_ms( 1000 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Driver

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
