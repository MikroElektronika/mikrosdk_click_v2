/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "altitude2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ALTITUDE2_DUMMY             0
#define DBL_MAX                     3.40282347e+38
#define DBL_MAX_PIC                 6.80564713e+38
#define EXCESS                    126
#define MAX_EXPONENT              255

#define FRNDINT(x)                  ((double)(long)(x))
#define DBL_MANT_DIG               23
#define DBL_MANT_DIG_PIC           24
#define CHAR_BIT                    8

#define EXP_MAX                    89.416
#define EXP_MIN                   -87.33655

// -------------------------------------------------------------- PRIVATE TYPES

static union both
{
    struct flt
    {
        unsigned char   mant[ 2 ];
        unsigned        hmant:7;
        unsigned        exp:8;
        unsigned        sign:1;
      } flt;
   double fl;
};

// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void altitude2_make_conv_comm ( altitude2_t *ctx, uint8_t *comm_temp, uint8_t *comm_press );

static double pow ( double x, double y );
static double log ( double x );
static double exp ( double x );
static double eval_poly ( double x, const double code *d, int n );
static double ldexp ( double value, int newexp );
static double frexp ( double value, int *eptr );
static double floor ( double x );

static void altitude2_i2c_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes );
static void altitude2_i2c_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes );
static void altitude2_spi_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes );
static void altitude2_spi_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes );


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void altitude2_cfg_setup ( altitude2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = 100000; 
    cfg->i2c_address = ALTITUDE2_DEVICE_ADDR_1;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->sel = ALTITUDE2_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ALTITUDE2_RETVAL altitude2_init ( altitude2_t *ctx, altitude2_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ALTITUDE2_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) != I2C_MASTER_SUCCESS )
        {
            return ALTITUDE2_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->send_comm_f = altitude2_i2c_send_comm;
        ctx->send_comm_resp_f = altitude2_i2c_send_comm_resp;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        //spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
        {
            return  ALTITUDE2_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ALTITUDE2_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->send_comm_f = altitude2_spi_send_comm;
        ctx->send_comm_resp_f = altitude2_spi_send_comm_resp;

    }
    

    return ALTITUDE2_OK;
}

uint8_t altitude2_read_prom( altitude2_t *ctx, uint8_t select_data, uint32_t *data_out )
{
    uint8_t tmp_data;

    if( select_data > 7 )
    {
        return 1;
    }

    tmp_data = 0xA0 | ( select_data << 1 );
    ctx->send_comm_resp_f( ctx, tmp_data, data_out, 2 );

    return 0;
}

void altitude2_reset( altitude2_t *ctx )
{
    uint8_t comm_data = 0x1E;
    uint8_t cnt;

    ctx->send_comm_f( ctx, comm_data, 0, 0);
    Delay_10ms( );
    
    for( cnt = 1; cnt < 7; cnt++ )
    {
        altitude2_read_prom( ctx, cnt, &ctx->data_prom[ cnt - 1 ] );
    } 
}

uint8_t altitude2_set_ratio( altitude2_t *ctx, uint8_t temp_ratio, uint8_t press_ratio )
{
    if ( temp_ratio > 4 )
    {
        return 1;
    }
    if ( press_ratio > 4 )
    {
        return 2;
    }

    ctx->ratio_temp = temp_ratio;
    ctx->ratio_press = press_ratio;

    return 0;
}

void altitude2_read_data( altitude2_t *ctx, float *temp_data, float *press_data, float *altitude_data )
{
    uint32_t buff_data[ 2 ];
    uint8_t temp_comm;
    uint8_t press_comm;
    float res_data[ 4 ];
    float tmp_var;
        
    altitude2_make_conv_comm( ctx, &temp_comm, &press_comm );
    ctx->send_comm_f( ctx, temp_comm, 0, 0 );
    ctx->send_comm_resp_f( ctx, 0x00, &buff_data[ 0 ], 3 );
    ctx->send_comm_f( ctx, press_comm, 0, 0 );
    ctx->send_comm_resp_f( ctx, 0x00, &buff_data[ 1 ], 3 );
    
    res_data[ 0 ] = ( float )ctx->data_prom[ 4 ] * 256.0;
    res_data[ 0 ] = ( float )buff_data[ 0 ] - res_data[ 0 ];
    res_data[ 1 ] = res_data[ 0 ] / 8.0;
    res_data[ 1 ] = res_data[ 1 ] * ( ( float )ctx->data_prom[ 5 ] / 1048576.0 );
    res_data[ 1 ] = res_data[ 1 ] + 2000.0;
    res_data[ 1 ] = res_data[ 1 ] / 100.0;
    *temp_data = res_data[ 1 ];
    
    res_data[ 2 ] = res_data[ 0 ] / 128.0;
    res_data[ 2 ] = res_data[ 2 ] * ( ctx->data_prom[ 2 ] / 2097152.0 );
    res_data[ 2 ] = res_data[ 2 ] + ( ctx->data_prom[ 0 ] / 32.0 );
    res_data[ 3 ] = res_data[ 0 ] / 32.0;
    res_data[ 3 ] = res_data[ 3 ] * ( ctx->data_prom[ 3 ] / 65536.0 ); 
    res_data[ 3 ] = res_data[ 3 ] + ( ctx->data_prom[ 1 ] * 4.0 );
    res_data[ 1 ] = buff_data[ 1 ] / 32768.0; 
    res_data[ 1 ] = res_data[ 1 ] * res_data[ 2 ];
    res_data[ 1 ] = res_data[ 1 ] - res_data[ 3 ];
    res_data[ 1 ] = res_data[ 1 ] / 100.0;
    *press_data = res_data[ 1 ];
    
    tmp_var = 1013.25 / *press_data;
    *altitude_data = pow( tmp_var, 0.19022256 );
    *altitude_data = *altitude_data - 1;
    tmp_var = *temp_data + 273.15;
    *altitude_data = *altitude_data *  tmp_var;
    *altitude_data = *altitude_data / 0.0065;
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void altitude2_i2c_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes )
{
    Delay_10ms( );
    i2c_master_write( &ctx->i2c, &comm_byte, 1 );  
}

static void altitude2_spi_send_comm ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *input_data, uint8_t num_bytes )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &comm_byte, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

static void altitude2_i2c_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes )
{
    uint8_t tmp[ 3 ];
    uint8_t cnt;
    uint32_t pom = 0;

    i2c_master_write_then_read( &ctx->i2c, &comm_byte, 1, tmp, num_bytes );
    
    for( cnt = 0; cnt < num_bytes; cnt++ )
    {
        pom = pom << 8;
        pom = pom | tmp[ cnt ];
        
    }
    *output_data = pom;
}


static void altitude2_spi_send_comm_resp ( altitude2_t *ctx, uint8_t comm_byte, uint32_t *output_data, uint8_t num_bytes )
{   
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 257 ];
    uint8_t cnt;
    uint32_t pom = 0;
    
    tx_buf[ 0 ] = comm_byte;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, num_bytes+1 );
    spi_master_deselect_device( ctx->chip_select ); 

    for( cnt = 0; cnt < num_bytes ; cnt++ )
    { 
        pom = pom << 8;
        pom = pom | rx_buf[ cnt + 1 ];  
        
    }
    *output_data = pom;
}

static void altitude2_make_conv_comm( altitude2_t *ctx, uint8_t *comm_temp, uint8_t *comm_press )
{
    uint8_t comm_byte = 0x50;
    uint8_t ratio_cnt = 0;

    while ( ctx->ratio_temp != ratio_cnt )
    {
        comm_byte += 2;
        ratio_cnt++;
    }

    *comm_temp = comm_byte;
    comm_byte = 0x40;
    ratio_cnt = 0;
    while ( ctx->ratio_press != ratio_cnt )
    {
        comm_byte += 2;
        ratio_cnt++;
    }

    *comm_press = comm_byte;
}

static double pow( double x, double y )
{
    unsigned char sign = 0;
    long yi;

    if ( y == 0.0 )
        return 1.0;
    if ( x == 0.0 ) 
        return 0.0;
        
    if ( x < 0.0 )
    {
        yi = ( long )y;
                
        if ( ( double ) yi != y)
            return 0.0;
        sign = yi & 1;
        x = -x;
    }
        
    x = log( x );
    x = x * y;
    x = exp( x );

    if ( sign )
    {
        return -x;
    }

    return x;
}

static double log( double x )
{
    int exp;
    static const double coeff[ ] = {
     0.0000000001,      // a0 //
     0.9999964239,      // a1 //
    -0.4998741238,      // a2 //
     0.3317990258,      // a3 //
    -0.2407338084,      // a4 //
     0.1676540711,      // a5 //
    -0.0953293897,      // a6 //
     0.0360884937,      // a7 //
    -0.0064535442,      // a8 //
    };

    if ( x <= 0.0 )
        return 0.0;
        
    x = frexp( x, &exp ) * 2.0 - 1.0;
    exp--;
    x = eval_poly( x, coeff, sizeof coeff / sizeof coeff[ 0 ] - 1 );
        
    return x + 0.69314718055995 * exp;
}

static double exp( double x )
{
    int exp;
    char sign;

    const static double coeff[ ] = {
    1.0000000000e+00,
    6.9314718056e-01,
    2.4022650695e-01,
    5.5504108945e-02,
    9.6181261779e-03,
    1.3333710529e-03,
    1.5399104432e-04,
    1.5327675257e-05,
    1.2485143336e-06,
    1.3908092221e-07,
    };

    if (x == 0.0)
        return 1.0;
    if (x > EXP_MAX)
    {
        return DBL_MAX;
    }
    if (x < EXP_MIN)
    { 
        return 0.0;
    }
        
    sign = x < 0.0;
    if ( sign )
        x = -x;
        
    x *= 1.4426950409;           
    exp = ( int ) floor( x );
    x -= ( double ) exp;
    x = ldexp( eval_poly( x, coeff, sizeof coeff / sizeof coeff[ 0 ] - 1 ), exp );
        
    if ( sign )
    {
        if (x == DBL_MAX)
        {
            return 0.0;
        }
        return 1.0 / x;
    }
        
    return x;
}

static double eval_poly( double x, const double code *d, int n )
{
    double res;

    res = d[ n ];

    while ( n )
    {
        res = x * res + d[--n];
    }
    return res;
}

static double ldexp( double value, int newexp )
{
    union both uv;

    uv.fl = value;
    newexp += uv.flt.exp;
    if (newexp < 0)
        return 0.0;
    else
    if (newexp > MAX_EXPONENT)
        if (value < 0.0)
            return -DBL_MAX;
        else
            return DBL_MAX;
    else
        uv.flt.exp = newexp;
        
    return uv.fl;
}

static double frexp ( double value, int *eptr )
{
    union both uv;
    volatile int bb;

    uv.fl = value;
    bb = uv.flt.exp - EXCESS;
    *eptr = bb;
    uv.flt.exp = EXCESS;
        
    return uv.fl;
}


static double floor( double x )
{
    double i;
    int expon;

    expon = ( ( *( unsigned long * ) & x >> DBL_MANT_DIG ) & 255 );
    expon = expon - 127;
        
    if ( expon < 0 )
        if ( x < 0.0 )
        {
            return -1.0;
        }
        else
        {
            return  0.0;
        }
        
    if ( ( unsigned ) expon > sizeof( double ) * CHAR_BIT - 8 )
        return x;          
    i = FRNDINT(x);

    if ( i > x )
    {
        return i - 1.0;
    }
        
    return i;
}

// ------------------------------------------------------------------------- END

