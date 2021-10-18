\mainpage Main Page
 
---
# DAC 6 click

DAC 6 Click is a compact add-on board that contains a fully-featured, general-purpose voltage-output digital-to-analog converter. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Dac6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dac6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac6_cfg_setup ( dac6_cfg_t *cfg ); 
 
- Initialization function.
> DAC6_RETVAL dac6_init ( dac6_t *ctx, dac6_cfg_t *cfg );


#### Example key functions :

- Function is used to set operation mode output channel and level.
> float dac6_set_output ( dac6_t *ctx );
 
- Sends 16-bit data to the device's input shift register.
> void dac6_write_data ( dac6_t *ctx, uint16_t wr_data );


## Examples Description

> DAC 6 click carries 12-bit buffered Digital-to-Analog Converter. It converts digital value 
> to the corresponding voltage level using external voltage reference.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac6_cfg_t cfg;

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

    dac6_cfg_setup( &cfg );
    DAC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac6_init( &dac6, &cfg );
}
  
```

### Application Task

> This example shows capabilities of DAC 6 click by changeing
> output values from 0 to the maximum output range on all four channels.
> Output voltage is calculated by using the equation : 
> Vout = Vrefin * (set_out / 4095).

```c

void application_task ( void )
{
    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_A;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  A : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }

    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_B;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  B : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }
    
    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_C;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  C : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }

    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_D;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  D : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }
    
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac6

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
