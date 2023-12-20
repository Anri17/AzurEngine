#ifndef _STAGE_H_
#define _STAGE_H_

#include <string>
#include <vector>

struct Message
{
	int time; // in milliseconds
	int duration; // in milliseconds
	std::string speaker;
	std::string message;
};

struct Stage
{
	std::vector<Message> dialogue; // vector of messages
};

#endif // _STAGE_H_