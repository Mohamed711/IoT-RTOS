/*
 * I2C_slave.h
 *
 * Created: 2/9/2016 1:27:12 PM
 *  Author: sameh
 */ 


#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_


void TWI_init_slave(uint8_t address);
void TWI_match_read_slave(void);
char TWI_read_slave(void);
void TWI_match_write_slave(void);
void TWI_write_slave(char write_data);




#endif /* I2C_SLAVE_H_ */