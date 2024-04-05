
---
# Heart Rate click

Heart Rate click is a heart rate monitoring and pulse oximetry measuring Click board™. It features an advanced oximeter and heart rate monitoring sensor, which relies on two integrated LEDs, a photosensitive element, and a very accurate and advanced low noise analog front end, to provide clean and accurate readings.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heart-rate-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the HeartRate Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HeartRate Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void heartrate_cfg_setup ( heartrate_cfg_t *cfg ); 
 
- Initialization function.
> HEARTRATE_RETVAL heartrate_init ( heartrate_t *ctx, heartrate_cfg_t *cfg );

- Click Default Configuration function.
> void heartrate_default_cfg ( heartrate_t *ctx );


#### Example key functions :

- Using this function we can check if the data is ready for reading
> uint8_t heartrate_data_ready ( heartrate_t *ctx );
 
- Using this function we can read IR and RED values.
> uint8_t heartrate_read_ir_red ( heartrate_t *ctx, uint16_t *ir_buff, uint16_t *red_buff );

- This function reads data from the desired register.
> void heartrate_generic_read ( heartrate_t *ctx, uint8_t reg, uint16_t len, uint8_t *data_buf );

## Examples Description

> This click features an advanced oximeter and heart rate monitoring sensor, 
> which relies on two integrated LEDs. It is enough to place an index finger on a top 
> of the sensor to get both of the heart rate and blood oxygen saturation via the I2C interface. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes heartrate driver and set the click board default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate_cfg_t cfg;

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

    heartrate_cfg_setup( &cfg );
    HEARTRATE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate_init( &heartrate, &cfg );

    heartrate_default_cfg( &heartrate );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Reading values from both Ir and Red diode and displaying their average values on the USB UART.

```c

void application_task ( void )
{
    if ( heartrate_data_ready( &heartrate ) )      
    {
        sample_num = heartrate_read_ir_red( &heartrate, ir_buff, red_buff );             
        if ( sample_num > 0 )
        {
            ir_average = 0;
            red_average = 0;
            for ( uint8_t cnt = 0; cnt < sample_num; cnt++ )
            {              
                ir_average += ir_buff[ cnt ];
                red_average += red_buff[ cnt ];
            }                 
            ir_average  /= sample_num;
            red_average /= sample_num;
            counter++;
            if( red_average > 100 && ir_average > 100 )                
            {       
                log_printf( &logger, "%lu;%lu;\r\n", red_average, ir_average );
                counter = 500;
            }
            else
            {
                if ( counter > 500 ) 
                {
                    log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
                    counter = 0;
                }
            }   
        }
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate

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
