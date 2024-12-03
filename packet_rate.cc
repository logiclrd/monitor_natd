#include <pthread.h>
#include <unistd.h>

#include <iostream>
#include <string>

using namespace std;

volatile int packetCount = 0;
volatile int lastPacketCount = 0;
volatile int running = 1;

void *monitorThread(void *ptr)
{
	string lineBuffer;

	while (cin)
	{
		getline(cin, lineBuffer);

		if (lineBuffer.find("aliased to") != string::npos)
			packetCount++;
	}

	running = 0;
}

int main()
{
	pthread_t thread;

	pthread_create(&thread, NULL, monitorThread, NULL);

	while (running)
	{
		sleep(1);

		cout << "Packets per second: " << ((packetCount + lastPacketCount) / 2) << endl;

		lastPacketCount = packetCount;
		packetCount = 0;
	}
}

