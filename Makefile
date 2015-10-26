FCPU = 16000000UL
MMCU = atmega328p
PROGRAMMER = arduino
PORT = /dev/ttyACM0

NAME 	= robot
FILES	= ${NAME}.cpp USART/usart.cpp
OBJS	= ${NAME}.o usart.o

help:
	@echo 'Help details:'
	@echo 'hex: compile hex file'
	@echo 'flash: install hex file'
	@echo 'program: compile hex and install'

hex:
	avr-g++ -Wall -Os -std=c++11 -DF_CPU=${FCPU} -mmcu=${MMCU} -c ${FILES}
	avr-g++ -Wall -Os -std=c++11 -DF_CPU=${FCPU} -mmcu=${MMCU} -o ${NAME}.elf ${OBJS}
	avr-objcopy -O ihex ${NAME}.elf ${NAME}.hex
	rm ${NAME}.o
	
	echo -e "\n"
	avr-size -C --mcu=${MMCU} ${NAME}.elf
	
flash:
	avrdude -c ${PROGRAMMER} -p ${MMCU} -P ${PORT} -U flash:w:${NAME}.hex
