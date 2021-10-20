\mainpage Main Page
 
 

---
CAP Wheel Click is a capacitive touch sensor with round shaped electrodes integrated on a Click board™. This click can sense touch even through plastic, wood, or other dielectric materials, which can be used to protect the surface of the PCB and the sensor pad trace itself.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/capwheel_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-wheel-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the CapWheel Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapWheel Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void capwheel_cfg_setup ( capwheel_cfg_t *cfg ); 
 
- Initialization function.
> CAPWHEEL_RETVAL capwheel_init ( capwheel_t *ctx, capwheel_cfg_t *cfg );



#### Example key functions :

- Generic Write function.
> uint8_t capwheel_write_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes );
 
- Generic Read function.
> uint8_t capwheel_read_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes );

- Data Ready Check function.
> uint8_t capwheel_check_data_ready ( capwheel_t *ctx );

## Examples Description

> This application is use for controling various devices.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface, performs the device reset and activates the desired channels (from CH0 to CH9), in this example all channels are activated.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    capwheel_cfg_t cfg;

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

    capwheel_cfg_setup( &cfg );
    CAPWHEEL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capwheel_init( &capwheel, &cfg );

    capwheel_reset ( &capwheel );
    capwheel_enable_chann( &capwheel, CAPWHEEL_CH0_PROX_EN | CAPWHEEL_CH1_EN | CAPWHEEL_CH2_EN | CAPWHEEL_CH3_EN | CAPWHEEL_CH4_EN | CAPWHEEL_CH5_EN | CAPWHEEL_CH6_EN | CAPWHEEL_CH7_EN | CAPWHEEL_CH8_EN | CAPWHEEL_CH9_EN );
    capwheel_set_threshold( &capwheel, 0x03 );
    Delay_ms( 500 );
    
    log_printf( &logger, "CAP Wheel is initialized and ready\r\n" );
}
  
```

### Application Task

> Checks is sense data ready for reading and if was ready, then reads wheel coordinates and sends these results to the LEDs.

```c

void application_task ( void )
{
    uint16_t sense_data;
    uint8_t ready_check;

    ready_check = capwheel_check_data_ready( &capwheel );

    if (ready_check == CAPWHEEL_DATA_READY)
    {
        capwheel_get_data( &capwheel, &sense_data );
        
        capwheel_set_output( &capwheel, sense_data, CAPWHEEL_LED_BRIGHTNESS_NUMBER );
    }
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapWheel

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
