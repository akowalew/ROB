#include "bluetoothIO.h"
#include <string.h>
#include "USART/usart.h"

uint8_t VARIABLES[4] = 
{
	0,
	240,
	255,
	40
} ;

const char ID[] = "ROB" ;
const char ID_OK[] = "ROB:OK" ;
const char ID_OK_READ[] = "ROB:OK:" ;
const char READ = '>' ;
const char WRITE = '<' ;
const char OPT = ':' ;

const uint8_t ID_LEN = sizeof(ID) / sizeof(char) - 1;
const uint8_t ID_OK_LEN = sizeof(ID_OK) / sizeof(char) - 1;
const uint8_t ID_OK_READ_LEN = sizeof(ID_OK_READ) / sizeof(char) - 1;

const char *OPT_ARGS[] = 
{
	"SEE",
	"RESET"
} ;

const void resetFun()
{
	Usart::sendLine("ROB:RESET") ;
}

const void seeFun()
{
	Usart::sendLine("ROB:SEE") ;
}

const void (*FUNCTION_PTRS[])() =
{
	seeFun,
	resetFun
} ;

const uint8_t FUNPTRS_LEN = sizeof(FUNCTION_PTRS) / sizeof(void *) ;
const uint8_t VARIABLES_LEN = sizeof(VARIABLES) / sizeof(uint8_t) ;

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

void obslugaKomunikatu(const char *komunikat)
{
	if(strncmp(komunikat, ID, ID_LEN) == 0)
	{
		if(komunikat[ID_LEN] == '\0') // wprowadził tylko ID
			Usart::sendLine(ID) ;
		else
		{
			const char *ptr = komunikat + ID_LEN + 1 ;
		
			if(komunikat[ID_LEN] == OPT) 
			{
				for(uint8_t i = 0 ; i < FUNPTRS_LEN ; i++)
					if(strcmp(OPT_ARGS[i], ptr) == 0)
						FUNCTION_PTRS[i]() ;
			}
			else if(komunikat[ID_LEN] == READ) 
			{	
				if(strcmp(ptr, "A") == 0)
				{
					// read ALL
					Usart::sendLine("ROB:ALL") ;
				}
				else
				{
					uint8_t varNum = atoi(ptr) ;
					if(varNum < VARIABLES_LEN)
					{
						char message[ID_OK_READ_LEN+3+1] ; // + ":OK:" + 8bit + '\0'
						strcpy(message, ID_OK_READ) ;
						myItoa(VARIABLES[varNum], message + ID_OK_READ_LEN) ;
						Usart::sendLine(message) ;
					}
				}				
			}
		}
	}
}
	
