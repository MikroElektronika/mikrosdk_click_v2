\mainpage Main Page
 

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

- `heartrate3_cfg_setup` Config Object Initialization function.
```c
void heartrate3_cfg_setup ( heartrate3_cfg_t *cfg ); 
```

- `heartrate3_init` Initialization function.
```c
err_t heartrate3_init ( heartrate3_t *ctx, heartrate3_cfg_t *cfg );
```

- `heartrate3_default_cfg` Click Default Configuration function.
```c
err_t heartrate3_default_cfg ( heartrate3_t *ctx );
```

#### Example key functions :

- `heartrate3_check_data_ready` Function is used to check data ready flag.
```c
uint8_t heartrate3_check_data_ready ( heartrate3_t *ctx );
```

- `heartrate3_write_data` Function is used to write 32-bit data into register.
```c
err_t heartrate3_write_data ( heartrate3_t *ctx, uint8_t reg_adr, uint32_t wr_data );
```

- `heartrate3_read_24bit` Function is used to read 24-bit value from register.
```c
err_t heartrate3_read_24bit ( heartrate3_t *ctx, uint8_t reg_adr, uint32_t *data_out );
```

## Examples Description

> The demo application shows reflected red, green and ir values.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes click driver, resets the device, applies default settings and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate3_cfg_t heartrate3_cfg;

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
    heartrate3_cfg_setup( &heartrate3_cfg );
    HEARTRATE3_MAP_MIKROBUS( heartrate3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate3_init( &heartrate3, &heartrate3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "  Heart rate 3 Click  \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
    if ( HEARTRATE3_ERROR == heartrate3_default_cfg ( &heartrate3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, "     Initialised!     \r\n" );
    log_printf( &logger, "----------------------\r\n" );    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
  
```

### Application Task

> This example demonstrates the use of Heart rate 3 board. It is set in default mode,
and reads reflected red, green and ir values and displays the results on USART terminal.

```c

void application_task ( void )
{
    err_t error_flag = HEARTRATE3_OK;
    if ( heartrate3_check_data_ready ( &heartrate3 ) )
    {
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED2VAL, &led_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_ALED2VAL, &aled_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED1VAL, &led_1 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_ALED1VAL, &aled_1 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED2_ALED2VAL, &led_2_aled_2 );
        error_flag |= heartrate3_read_24bit( &heartrate3, HEARTRATE3_REG_LED1_ALED1VAL, &led_1_aled_1 );
        if ( HEARTRATE3_OK == error_flag )
        {
            log_printf( &logger, "%lu;%lu;%lu;%lu;%lu;%lu;\r\n", 
                        led_2, aled_2, led_1, aled_1, led_2_aled_2, led_1_aled_1 );
        }
    }
}  

```

## Note

> We recommend using the SerialPlot tool for data visualizing.

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
