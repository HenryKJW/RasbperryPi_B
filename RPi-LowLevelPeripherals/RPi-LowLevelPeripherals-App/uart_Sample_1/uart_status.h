#ifndef _UART_STATUS_H_
#define _UART_STATUS_H_

#define ERR_OPEN_COMPORT_FAILURE		ERR_BASE_UART(-001)
#define ERR_CLOSE_COMPORT_FAILURE		ERR_BASE_UART(-002)
#define ERR_WRITE_BYTE_FAILURE		ERR_BASE_UART(-003)
#define ERR_WRITE_STRING_FAILURE		ERR_BASE_UART(-004)
#define ERR_BAUDRATE_NOT_FOUND		ERR_BASE_UART(-005)
#define ERR_PARITY_NOT_FOUND			ERR_BASE_UART(-006)

#endif
