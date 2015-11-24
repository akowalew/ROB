typedef unsigned char uint8_t ;

uint8_t myAtoi(volatile uint8_t *u8Dest, const char *src)
{
	// zwraca ilość wczytanych znaków
	// wczytuje tylko liczbę 8bit, więc wczyta co najwyżej 3 cyfry

	uint8_t ret = 0 ;

	*u8Dest = 0 ;

	while(src[ret] >= '0' && src[ret] <= '9' && ret < 3)
		*u8Dest = ((*u8Dest) * 10) + (src[ret++] - '0') ;

	return ret ;
}

void myItoa(uint8_t var, char *dest)
{
	uint8_t i = 0 ;
	char tmp[3] ;

	if(var == 0)
	{
		dest[0] = '0' ;
		dest[1] = '\0' ;
		return ;
	}

	while(var)
	{
		tmp[i++] = (var % 10) + '0' ;
		var /= 10 ;
	}

	--i ;
	uint8_t j = i ;

	do
	{
		dest[j-i] = tmp[i] ;
	}while(i-- > 0) ;

	dest[j+1] = '\0' ;
}

