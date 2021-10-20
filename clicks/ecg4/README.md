\mainpage Main Page
 
---
# ECG 4 click

ECG 4 Click is a complete solution for the development of ECG and Heart-Rate (HR) applications, based on the BMD101, a specialized bio-signal sensing System-on-Chip (SoC).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ecg-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Ecg4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ecg4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ecg4_cfg_setup ( ecg4_cfg_t *cfg ); 
 
- Initialization function.
> ECG4_RETVAL ecg4_init ( ecg4_t *ctx, ecg4_cfg_t *cfg );

- Reset module function.
> void ecg4_module_reset ( ecg4_t *ctx );


#### Example key functions :

- Function performs the uart interrupt routine, reads a data from uart rx buffer and makes a response from the BMD101 device.
> void ecg4_uart_isr( ecg4_t *ctx, uint8_t rx_dat );
 
- Function powers up or down control of LDO (Low Drop Out).
> void ecg4_enable_ldo_ctrl ( ecg4_t *ctx, uint8_t state );

- Generic read function.
> int32_t ecg4_generic_read ( ecg4_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from ECG 4 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, sets the driver handler and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg4_cfg_t cfg;

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

    ecg4_cfg_setup( &cfg );
    ECG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg4_init( &ecg4, &cfg );

    ecg4.driver_hdl = make_response;
    Delay_ms( 500 );

    ecg4_module_reset ( &ecg4 );
    ecg4_enable_ldo_ctrl ( &ecg4, ECG4_ENABLE_LDO_CTRL );

    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads the received data and parses it on the USB UART if the response buffer is ready.

```c

void application_task ( void )
{
    ecg4_process(  );
    if ( ecg4_responseReady( &ecg4 ) )
    {
        process_response( );
    }
}  

```

## Note

> Use the Serial Plot application for data plotting.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg4

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
