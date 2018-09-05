#include <stdio.h>
#include "header.h"
#include "Agent_agent_header.h"

int send(void)
{
	fprintf(stderr, "\nIT %d ID %d adds ID message", iteration_loop, ID);
	add_info_message(ID);

	return 0;
}



int print_id(void)
{
	fprintf(stderr, "\nIT %d ID %d prints own ID", iteration_loop, ID);

	return 0;
}

int read(void)
{
	fprintf(stderr, "\nIT %d ID %d reads ID messages:\t", iteration_loop, ID);
	START_INFO_MESSAGE_LOOP
		fprintf(stderr, "%d ", info_message->id);
	FINISH_INFO_MESSAGE_LOOP

	return 0;
}

