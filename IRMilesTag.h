#ifndef IRMILESTAG_H_
#define IRMILESTAG_H_

#include "IRremote.h"

class IRMilesTagSend : public IRsend {

public:
	void sendShot(unsigned int player, unsigned short team, unsigned int damage);
	void sendMessage(unsigned int message, unsigned int parameter);
	void sendCommand(unsigned int command);

};

class IRMilesTagRecv : public IRrecv {

public:
	IRMilesTagRecv(int recvpin);
	int recv(decode_results* results);

};

#endif /* IRMILESTAG_H_ */
