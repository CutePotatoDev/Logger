/*
 * i2c.h
 *
 * Created: 2017-03-29 10:18:58
 */ 


#ifndef I2C_H_
#define I2C_H_

#define I2C_WRITE   0
#define I2C_READ    1


#define TWI_INTERRUPT (1 << TWINT)
#define TWI_START_COND (1 << TWSTA)
#define TWI_ENABLE (1 << TWEN)
#define TWI_ENABLE_ACK (1 << TWEA)
#define TWI_STOP (1 << TWSTO)

#define TWI_STATUS (TWSR & 0xF8)


void I2C_Init(void);
uint8_t I2C_Start(uint8_t);
uint8_t I2C_Write(uint8_t);
uint8_t I2C_ReadACK(void);
uint8_t I2C_ReadNACK(void);
void I2C_Stop(void);

#endif /* I2C_H_ */