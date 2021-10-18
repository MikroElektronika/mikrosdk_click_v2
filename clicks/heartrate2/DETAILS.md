
---
# Heart Rate 2 click

Heart Rate 2 Click is an add-on board based on MAXM86161 from Maxim Integrated a complete, integrated, optical data acquisition system, ideal for optical pulse oximetry and heart-rate detection applications. The optical readout has a low-noise signal conditioning analog front-end (AFE), including 19-bit ADC, an industry-lead ambient light cancellation (ALC) circuit, and a picket fence detect and replace algorithm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate2_click.png">
</p>

[click Product page](https://www.mikroe.com/heart-rate-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the HeartRate2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HeartRate2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void heartrate2_cfg_setup ( heartrate2_cfg_t *cfg ); 
 
- Initialization function.
> HEARTRATE2_RETVAL heartrate2_init ( heartrate2_t *ctx, heartrate2_cfg_t *cfg );

- Click Default Configuration function.
> void heartrate2_default_cfg ( heartrate2_t *ctx );


#### Example key functions :

- This function settings en pin status.
> void heartrate2_set_en ( heartrate2_t *ctx, uint8_t state );
 
- This function restarts device.
> void heartrate2_soft_reset ( heartrate2_t *ctx );

- This function reads data buffer from the desired register.
> void heartrate2_read_fifo ( heartrate2_t *ctx, heartrate2_fifo_data_t *fifo );

## Examples Description

> This example demonstrates the use of Heart rate 2 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initilizes the driver, resets the device, checks the device ID and applies default settings.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate2_cfg_t cfg;
    uint8_t rd_stat;

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

    heartrate2_cfg_setup( &cfg );
    HEARTRATE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate2_init( &heartrate2, &cfg );
    
    log_printf( &logger, "Configuring the module...\r\n" );
    Delay_ms( 1000 );
    
    heartrate2_set_en( &heartrate2, HEARTRATE2_PIN_HIGH );
    Delay_ms( 100 );
    heartrate2_soft_reset ( &heartrate2 );
    
    rd_stat = heartrate2_generic_read( &heartrate2, HEARTRATE2_REG_PART_ID );

    if ( rd_stat != HEARTRATE2_DEV_ID )
    {
        log_error( &logger, "---- WRONG ID ----" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
    
    heartrate2_default_cfg( &heartrate2, HEARTRATE2_CONFIG_GREEN );
    log_printf( &logger, "The module has been configured!\r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads the data from Green diode and displays the results on USB UART if the measured data
> is above defined threshold, otherwise, it displays a desired message on the terminal.

```c

void application_task ( void )
{
    heartrate2_fifo_data_t fifo_object;

    heartrate2_read_fifo( &heartrate2, &fifo_object );

    if ( fifo_object.tag == HEARTRATE2_FIFO_TAG_PPG1_LEDC1 )
    {
        counter++;
        if ( fifo_object.data_val > 1000 )
        {
            log_printf( &logger, "%lu;\r\n", fifo_object.data_val );
            counter = 1000;
        }
        else if ( counter > 1000 )
        {
            log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
            counter = 0;
        }
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate2

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
