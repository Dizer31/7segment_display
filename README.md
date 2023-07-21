void setBrightness(uint8_t x)		//x = 0 - 24
void setBrightness(uint8_t pos, uint8_t x)		//x = 0 - 24, pos = 0 - nAnod
void clear() 
void clear(uint8_t pos)		//pos = 0 - nAnod
void point(bool flag)

void print(uint16_t num)		//num = 0 - 9999
void print(uint8_t pos, int8_t x)		//выводит цифру x в указанную ячейку дисплея pos
void print(int16_t* arr)		//выводит цифры массивом по ячейкам
void clock(uint8_t x1, uint8_t x2)		//x1 = 0 - 99, x2 = 0 - 99

void printChar(uint8_t pos, int8_t x)		//выводит байт вида 0xe6 и буквы-константы в ячейку
void printChar(int16_t* arr)		//выводит байт вида 0xe6 и буквы-константы массивом


