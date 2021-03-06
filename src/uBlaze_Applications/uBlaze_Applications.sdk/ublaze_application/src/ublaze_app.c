#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "sleep.h"
#include "ublaze_app_functions.h"

int main()
{
    init_platform();

    print("Starting test!\n\r");

    // Initialize the timer
    init_64b_timer(0,0);

    // Insert complex code in here to study the time it takes to complete
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////


    // Wait 1.123 seconds, replace this code with some algorithm later
    usleep(1123000);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // Calculate the time

    u64 total_cycles = get_64b_time();

    // Computes the execution time in seconds
    double raw_exe_time = (double) total_cycles / XPAR_TMRCTR_0_CLOCK_FREQ_HZ;

    // Computes the minutes
    int exe_time_min = ((int) raw_exe_time / 60) % 60;

    // Computes the hours
    int exe_time_hr = (raw_exe_time / 3600);

    // Computes the integer number of seconds
    int whole_sec = raw_exe_time - exe_time_min*60 - exe_time_hr*3600;

    // Computes the thousands value
    double whole_sec_doub = raw_exe_time - exe_time_min*60 - exe_time_hr*3600;
    int thousands_sec = (whole_sec_doub - whole_sec) * 1000;

    xil_printf("The execution time was %d hours, %d minutes, and %d.%d seconds!\n\r", exe_time_hr, exe_time_min, whole_sec, thousands_sec);


    // UART TX -> RX Loop forever example
    int uart_rx;
    while(1){
    	// Loop forever
    	uart_rx = 0;
    	while(uart_rx == 0){
    		// Loop until the RX FIFO is not empty

    		// Sleep for 1 us
    		usleep(1);

			// Check to see if the RX FIFO is empty
			uart_rx = Xil_In32(XPAR_AXI_UARTLITE_0_BASEADDR + 0x08) & 0x01;

    	};
    	// Read the RX register
    	uart_rx = Xil_In32(XPAR_AXI_UARTLITE_0_BASEADDR + 0x00);

    	// Print the character from the RX register
		xil_printf("%c", uart_rx);
	};

    cleanup_platform();
    return 0;
}
