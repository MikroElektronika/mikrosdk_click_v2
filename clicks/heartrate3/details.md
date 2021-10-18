

---
# Heart rate 3 click

Heart rate 3 click is a mikroBUS add-on board whose functionality is determined by two components: an OSRAM’s SFH7050 pulse oximetry and heart rate monitoring module, and a TI AFE4404 (analong-front-end) IC specialized for bio-sensing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heart-rate-3-click)

---


#### Click library 

- **Author**        : Jova Stajkovic
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HeartRate3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HeartRate3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void heartrate3_cfg_setup ( heartrate3_cfg_t *cfg ); 
 
- Initialization function.
> HEARTRATE3_RETVAL heartrate3_init ( heartrate3_t *ctx, heartrate3_cfg_t *cfg );

- Click Default Configuration function.
> void heartrate3_default_cfg ( heartrate3_t *ctx );


#### Example key functions :

- Function is used to read 32-bit value from register.
> uint32_t heartrate3_read_u32 ( heartrate3_t *ctx, uint8_t reg_adr );
 
- Function is used to set or clear rst pin.
> void heartrate3_rst_state ( heartrate3_t *ctx, uint8_t state );

- Function is used to write 32-bit data into register.
> void heartrate3_write_data ( heartrate3_t *ctx, uint8_t reg_adr, uint32_t wr_data );

## Examples Description

> 
> The demo application shows reflected red, green and ir values.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes click driver, resets the device, applies default settings and makes an initial log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate3_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    heartrate3_cfg_setup( &cfg );
    HEARTRATE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate3_init( &heartrate3, &cfg );
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "  Heart rate 3 Click  \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
    heartrate3_rst_state ( &heartrate3, HEARTRATE3_PIN_STATE_LOW );
    Delay_us( 50 );
    
    heartrate3_rst_state ( &heartrate3, HEARTRATE3_PIN_STATE_HIGH );
    Delay_ms( 100 );
    
    heartrate3_default_cfg ( &heartrate3 );
    Delay_ms( 100 );
    
    log_printf( &logger, "     Initialised!     \r\n" );
    log_printf( &logger, "----------------------\r\n" );
}
  
```

### Application Task

>
> This example demonstrates the use of Heart rate 3 board. It is set in default mode,
  and reads reflected red, green and ir values and displays the results on USART terminal.
> 

```c

void application_task ( void )
{
    led_2 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED2VAL );
    log_printf( &logger, "LED2: %d \r\n", led_2 );
    
    aled_2 = heartrate3_read_u32( &heartrate3, HEARTRATE3_ALED2VAL );
    log_printf( &logger, "ALED2: %d \r\n", aled_2 );
    
    led_1 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED1VAL );
    log_printf( &logger, "LED1: %d \r\n", led_1 );
    
    aled_1 = heartrate3_read_u32( &heartrate3, HEARTRATE3_ALED1VAL );
    log_printf( &logger, "ALED1: %d \r\n", aled_1 );
    
    led_2_aled_2 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED2_ALED2VAL );
    log_printf( &logger, "LED2ALED2: %d \r\n", led_2_aled_2 );
    
    led_1_aled_1 = heartrate3_read_u32( &heartrate3, HEARTRATE3_LED1_ALED1VAL );
    log_printf( &logger, "LED1ALED1: %d \r\n", led_1_aled_1 );
    
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate3

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
