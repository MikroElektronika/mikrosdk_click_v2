\mainpage Main Page
 
 

---
# Cap Wheel 2 click

CAP Wheel 2 Click is a capacitive touch sensor with round-shaped electrodes integrated on a Click board™. This click can sense touch even through plastic, wood, or other dielectric materials, which can be used to protect the surface of the PCB and the sensor pad trace itself. Therefore, this Click board™ comes with overlay, made of plexiglass. Unlike the mechanical button, the capacitive touch button lasts much longer, it is not prone to damage and wear over time and it is very reliable. This Click board feature QS263B sensor which contains a ProxSense® module that uses patented technology to provide detection of proximity and touch conditions on numerous sensing lines.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/capwheel2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-wheel-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the CapWheel2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapWheel2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void capwheel2_cfg_setup ( capwheel2_cfg_t *cfg ); 
 
- Initialization function.
> CAPWHEEL2_RETVAL capwheel2_init ( capwheel2_t *ctx, capwheel2_cfg_t *cfg );

- Click Default Configuration function.
> void capwheel2_default_cfg ( capwheel2_t *ctx );


#### Example key functions :

- This function gets state of INT pin.
> uint8_t capwheel2_int_get ( capwheel2_t *ctx );
 
- This function waits for RDY pin to transition from HIGH to LOW state.
> uint8_t capwheel2_wait_for_rdy ( capwheel2_t *ctx );

## Examples Description

> This example sets basic device configuration; Contains function for waiting RDY(INT) pin, function for getting RDY(INT) pin state, function for I2C read and write with waiting for RDY(INT) pin and without waiting for RDY(INT) pin.

**The demo application is composed of two sections :**

### Application Init 

> Initializes CAP Wheel 2 device

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    capwheel2_cfg_t cfg;

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

    capwheel2_cfg_setup( &cfg );
    CAPWHEEL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capwheel2_init( &capwheel2, &cfg );
}
  
```

### Application Task

> Executes one of three 'capwheel2_get_xxx_task( )' functions.

```c

void application_task ( void )
{
    capwheel2_get_channels_task( );
} 

```

## Note

<pre> 
Additional Functions :

- capwheel2_error( ) - Logs error message and blocks code execution in endless while loop
- capwheel2_get_channels_task( ) - Logs active channels in touch and halt bytes ( channels: CH0 - proximity channel, CH1, CH2, CH3 )
- capwheel2_get_gesture_task( ) - Logs active gestures ( gestures: tap, touch, proximity )
- capwheel2_get_channel_counts_task( ) - Logs channel count values for each channel
- capwheel2_get_channels_touch( ) - Logs touch byte active channels ( exectuted by 'capwheel2_get_channels_task( )' function )
- capwheel2_get_channels_halt( ) - Logs halt byte active channels ( exectuted by 'capwheel2_get_channels_task( )' function )

</pre> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapWheel2

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
