
---
# ECG Click

This is an ECG (or EKG) machine on a Click board. It measures the electrical activity of a beating heart through electrodes taped to the skin. The board requires little setup, and the final measurement results can be displayed as an Electrocardiogram using a free Windows app.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ecg-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Ecg Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ecg Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ecg_cfg_setup ( ecg_cfg_t *cfg ); 
 
- Initialization function.
> ECG_RETVAL ecg_init ( ecg_t *ctx, ecg_cfg_t *cfg );

- Click Default Configuration function.
> void ecg_default_cfg ( ecg_t *ctx );


#### Example key functions :

- This function read ADC data.
> ecg_data_t ecg_generic_read ( ecg_t *ctx );
 
- This function executes default configuration for ECG Click.
> void ecg_default_cfg ( ecg_t *ctx );


- This function initializes all necessary pins and peripherals used for this Click.
> ECG_RETVAL ecg_init ( ecg_t *ctx, ecg_cfg_t *cfg );

## Examples Description

> This example demonstrates the use of ECG Click board. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg_cfg_t cfg;

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

    ecg_cfg_setup( &cfg );
    Delay_ms ( 200 );
    ECG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg_init( &ecg, &cfg );
    Delay_ms ( 200 );

    time_read = 0;
}
  
```

### Application Task

> Reads ADC sends results on serial plotter.

```c

void application_task ( void )
{
    time_read++;
    read_adc = ecg_generic_read( &ecg );
    plot_res( read_adc , time_read);

    Delay_ms ( 5 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
