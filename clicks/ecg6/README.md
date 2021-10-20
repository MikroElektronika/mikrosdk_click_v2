\mainpage Main Page
 
---
# Ecg 6 click

ECG 6 Click is a complete solution for the development of ECG and Heart-Rate (HR) applications. It features the MAX86150, a Reflective Heart Rate Monitor and Medical-Grade Pulse Oximeter from Maxim Integrated. The Click board™ contain integrated electrocardiogram, pulse oximeter, heart rate monitor sensor module. The ECG 6 Click can be used for application in Fitness Assistant Devices, Wearable Devices, Smartphones, Tablet.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ecg-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Ecg6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ecg6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ecg6_cfg_setup ( ecg6_cfg_t *cfg ); 
 
- Initialization function.
> ECG6_RETVAL ecg6_init ( ecg6_t *ctx, ecg6_cfg_t *cfg );

- Click Default Configuration function.
> void ecg6_default_cfg ( ecg6_t *ctx );


#### Example key functions :

- This function gets one sample from FIFO
> void ecg6_get_sample_data( ecg6_t *ctx, ecg6_element_t *element, uint8_t num_sample );
 
- Sends ECG sensor data to SerialPlot
> static void plot_ecg_data ( uint32_t ecg_data )

- Sends PPG sensor data to SerialPlot
> static void plot_ppg_data ( uint32_t ir_data, uint32_t red_data )

## Examples Description

> ECG 6 Click contain integrated electrocardiogram, pulse oximeter, 
> heart rate monitor sensor module.

**The demo application is composed of two sections :**

### Application Init 

> Initialize I2C module and all necessary pins. Checking communication accuracy
> and running default configuration for measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg6_cfg_t cfg;

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

    ecg6_cfg_setup( &cfg );
    ECG6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg6_init( &ecg6, &cfg );
    
    Delay_ms( 1000 );
    
    DEMO_EXAMPLE = PPG_EXAMPLE;
   
    // Dummy read
    ecg6_check_path_id( &ecg6 );
    Delay_ms( 100 );
    
    device_check = ecg6_check_path_id( &ecg6 );
    
    if ( device_check != 0 )
    {
       log_printf( &logger, " -- > Device ERROR!!! \r\n" );
       for ( ; ; );
    }
    log_printf( &logger, " -- > Device OK!!! \r\n" );

    if ( DEMO_EXAMPLE == ECG_EXAMPLE )
    {
        ecg6_default_cfg( &ecg6 );
    }
    else
    {
        ecg6_ppg_default_config( &ecg6 );
    }

    log_printf( &logger, " ---- Configuration done ----- \r\n" );
    Delay_ms( 1000 );

    time_cnt = 0;
}
  
```

### Application Task

> Measures an ECG signal or PPG sensor and draws a graph on a SerialPlot

```c

void application_task ( void )
{
    ecg6_element_t sample;
    
    if ( ecg6_int_pin_state(&ecg6) == 0 ) {
        
        ecg6_get_sample_data( &ecg6, &sample, 0x00 );
    
        if ( DEMO_EXAMPLE == ECG_EXAMPLE )
        {
            plot_ecg_data( sample.element_1 );
        }
        
        else
        {
            plot_ppg_data( sample.element_1, sample.element_2 );
        }
    }
}  

```

## Note

> When using ECG measurement - PPG measurement must be switched off ...
> Drawing speeds vary for PPG and ECG sensor.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg6

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
