\mainpage Main Page


---
# CAP Slider 2 click

CAP Slider 2 Click is a capacitive touch sensor with XY cross shaped electrodes integrated on a Click board™. This click can sense touch even through plastic, wood, or other dielectric materials, which can be used to protect the surface of the PCB and the sensor pad trace itself

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/capslider2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-slider-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the CapSlider2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapSlider2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void capslider2_cfg_setup ( capslider2_cfg_t *cfg ); 
 
- Initialization function.
> CAPSLIDER2_RETVAL capslider2_init ( capslider2_t *ctx, capslider2_cfg_t *cfg );


#### Example key functions :

- Generic Write function
> uint8_t capsldr2_write_reg ( capslider2_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes );
 
- Generic Read function
> uint8_t capsldr2_read_reg ( capslider2_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes );

- Data Ready Check function
> uint8_t capsldr2_check_data_ready ( capslider2_t *ctx );

## Examples Description

> This application could be used for controlling various devices.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface, performs the device reset and configurations
> and sets the desired threshold value which determines sensor sensitivity.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    capslider2_cfg_t cfg;

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

    capslider2_cfg_setup( &cfg );
    CAPSLIDER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capslider2_init( &capslider2, &cfg );

    Delay_ms ( 500 );

    cnt = 0;
    wheel_avrg1 = 0;
    wheel_avrg2 = 0;
    
    capsldr2_reset( &capslider2 );
    Delay_ms ( 500 );
    
    capsldr2_enable_chann( &capslider2, CAPSLDR2_CH0_PROX_EN | CAPSLDR2_CH1_EN | CAPSLDR2_CH2_EN | CAPSLDR2_CH3_EN | CAPSLDR2_CH4_EN | CAPSLDR2_CH5_EN | CAPSLDR2_CH6_EN | CAPSLDR2_CH7_EN | CAPSLDR2_CH8_EN | CAPSLDR2_CH9_EN );
    capsldr2_config( &capslider2 );
    capsldr2_set_threshold( &capslider2, 0x04 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "CAP Slider 2 is initialized\r\n" );

}
  
```

### Application Task

> Checks for data ready and then read capacitance from all channels.
> There are two sliders on the clik board (X and Y).
> X slider selects which LEDs are being activated, 
> while Y slider increases/decreases the LEDs intensity.

```c

void application_task ( void )
{
    uint16_t data_wheel1;
    uint16_t data_wheel2;
    uint8_t ready_check;

    ready_check = capsldr2_check_data_ready( &capslider2 );
    
    if (ready_check == CAPSLDR2_DATA_READY)
    {
        capsldr2_get_data( &capslider2, &data_wheel1, &data_wheel2 );
        
        wheel_avrg1 += data_wheel1;
        wheel_avrg2 += data_wheel2;
        cnt++;
    }
    
    if (cnt == 1)
    {
        if ((wheel_avrg2 / cnt) > 1800)
        {
            horizontal_check(  );
            capsldr2_set_output( &capslider2, out_val, out_mode );
        }
        else if (((wheel_avrg2 / cnt) < 1650) && ((wheel_avrg2 / cnt) > 1000))
        {
            vertical_check(  );
            capsldr2_set_output( &capslider2, out_val, out_mode );
        }
        
        wheel_avrg1 = 0;
        wheel_avrg2 = 0;
        cnt = 0;
    }
}  

```

## Note

> In some cases, the user will need to wait several seconds after the click initialization for the sensor to be stabilized.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapSlider2

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
