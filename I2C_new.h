void Send_Start(void);
void Send_Stop(void);
unsigned char Send_I2C(unsigned char *Data,unsigned char Len);
unsigned char Read_I2C(unsigned char *Data,unsigned char Len);
unsigned char Page_Write(unsigned char BLOCK_NUMBER,unsigned char BLOCK_ADDR, unsigned char I2C_WR_Buf);
unsigned char Page_Read(unsigned int BLOCK_NUMBER,unsigned char BLOCK_ADDR);
unsigned char I2C_Status(unsigned char status_code);
void I2C_Init(void);
