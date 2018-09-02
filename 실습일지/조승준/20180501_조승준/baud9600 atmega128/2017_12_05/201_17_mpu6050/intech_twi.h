/*****************************************
    CodeVisionAVR C, twi_mpu6050
*****************************************/
#ifndef _Intech_twi_INCLUDED_
#define _Intech_twi_INCLUDED_

#include <io.h>
//#include <intech_delay.h>

#pragma used+

/*
#define pwr_mgmt_1 0x6B
#define pwr_mgmt_2 0x6C

#define self_test_x = 0x0D
#define self_test_y = 0x0E
#define self_test_z = 0x0F
#define self_test_a = 0x10

#define accel_xout0 = 0x3B
#define accel_xout1 = 0x3C

#define accel_yout0 = 0x3D
#define accel_yout1 = 0x3E

#define accel_zout0 = 0x3F
#define accel_zout1 = 0x40

#define temp_out0 = 0x41
#define temp_out1 = 0x42

#define gyro_xout0 = 0x43
#define gyro_xout1 = 0x44

#define gyro_yout0 = 0x45
#define gyro_yout1 = 0x46

#define gyro_zout0 = 0x47
#define gyro_zout1 = 0x48

#define accel_config = 0x1C
#define gyro_config = 0x1B
*/

unsigned char mpu6050_read(unsigned char twi, unsigned char addr)
{
    char twi_dat;
    
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x08)));
    
    TWDR = (twi << 1);
    TWCR &= ~(1 << TWSTA);
    
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x18)));
    
    TWDR = addr;
    TWCR &= ~(1 << TWSTA); 
       
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x28)));
    
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
   
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x10)));
    
    TWDR = (twi << 1) + 1;
    TWCR &= ~(1 << TWSTA); 
        
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x40)));
    
    TWCR &= ~(1 << TWSTA);   
    
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x58)));
    twi_dat = TWDR;
    TWCR = (1 << TWINT)|(1 << TWSTO)|(1 << TWEN);
    
//    intech_delay_us(10);
    delay_us(10);
    
    return twi_dat;
}

void mpu6050_write(unsigned char twi, unsigned char addr, unsigned char data)
{
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
    
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x08)));
    
    TWDR = (twi << 1);
    TWCR &= ~(1 << TWSTA);
    
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x18)));
    
    TWDR = addr;
    TWCR &= ~(1 << TWSTA);    
    
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x28)));
    
    TWDR = data;
    TWCR &= ~(1 << TWSTA);
    
    while(((TWCR & 0x80) == 0x00 || ((TWSR & 0xF8) != 0x28)));
    
    TWCR = (1 << TWINT)|(1 << TWSTO)|(1 << TWEN);  
    
    delay_us(50);
}

#pragma used-

#endif