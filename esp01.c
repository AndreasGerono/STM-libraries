//
// esp01.c
// Created by Andreas Gerono on 10/10/2019.




uint8_t rx_buffer[] = "Connected to the internet";;

uint8_t search_rx_buffer(const char *str){
	return strstr((const char*)rx_buffer, str) != NULL;
}


