\mainpage Main Page
 
---
# ECG 3 click

ECG 3 click is a complete solution for ECG and HR application development, utilizing a specialized IC with a clinical-grade analog front-end (AFE). ECG 3 click uses the MAX30003 IC, an ultra-low power, single-channel bio-sensor, which features a wide range of different options, making it an ideal solution for development of heart rate and ECG monitoring applications, fitness applications, for the ECG bio-authentication, and similar applications related to heart monitoring. ECG 3 click is also equipped with the 3.5mm electrodes connector, making it ready to be used out of the box.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ecg-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Ecg3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ecg3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ecg3_cfg_setup ( ecg3_cfg_t *cfg ); 
 
- Initialization function.
> ECG3_RETVAL ecg3_init ( ecg3_t *ctx, ecg3_cfg_t *cfg );

- Click Default Configuration function.
> void ecg3_default_cfg ( ecg3_t *ctx );


#### Example key functions :

- Function reads ECG data from FIFO register.
> void ecg3_get_ecg ( ecg3_t *ctx, uint32_t *out_ecg );
 
- Function checks a status flag for the desired interrupt.
> uint8_t ecg3_check_status ( ecg3_t *ctx, uint32_t bit_mask );

- Function reads Heart Rate and R - R data and calculates HR data to BPM, and RR data to ms.
> void ecg3_get_rtor ( ecg3_t *ctx, uint16_t *out_hr, uint16_t *out_rr );

## Examples Description

> This click is made for ECG and HR, 
> equipped with an ultra-low power, single channel, integrated biopotential AFE, 
> with the ECG and R-to-R detection functionality. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI interface and performs the all necessary configuration for device to work properly.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg3_cfg_t cfg;

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

    ecg3_cfg_setup( &cfg );
    ECG3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg3_init( &ecg3, &cfg );

    ecg3_sw_reset( &ecg3 );
    ecg3_fifo_reset( &ecg3 );
    Delay_ms( 100 );

    ecg3_default_cfg ( &ecg3 );
    Delay_ms( 300 );
}
  
```

### Application Task

> Reads ECG Data every 8ms and sends this data to the serial plotter.

```c

void application_task ( void )
{
    ecg3_get_ecg( &ecg3, &ecg_data );

    plot_ecg( );
} 

```

## Note

> Additional Functions :
>  - void plot_ecg() - Sends ECG Data to the serial plotter.
>  - void log_rtor_() - Sends Heart Rate and R - R Data to the uart terminal. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg3

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
