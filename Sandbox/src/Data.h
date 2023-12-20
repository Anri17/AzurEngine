#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Stage.h"

/*
	Load the data and save it


*/




void LoadGameData()
{
	// Load Stage1
	// Load Stage2
	// Load Stage3
	// Load Stage...
}

Stage* LoadStageVersion1(std::ifstream fstream)
{
	// TODO
	/*
	std::string line;
	while (fstream >> line) // continue to scan each line of the file
	{
		if (line == "[DIALOGUE]\n") // start parsing out the dialogue section
		{
			while (fstream >> line) // Parse each message
			// 1st token == time
			// 2nd token == duration
			// 3rd token == speaker
			// 4th token == message
			int time, duration;
			std::string speaker, message;
			std::vector<std::string> vec_message;
			// separate the line by the delimiter '|'
			std::string segment; // the word of each segment
			while (std::getline(line, segment, '_'))
			{
				vec_message.push_back(segment);
			}
			// TODO: INCOMPLETE -> extract tokens from file
			out->dialogue.push_back({ time, duration, speaker, message });
		}
	}*/
}

Stage* LoadStage(std::string filename)
{
	std::ifstream fstream;
	fstream.open(filename);
	std::string line;
	fstream >> line;	// first line should be the vesion of the file
	if (line == "#File Version 1\n");
	{
		
	}

	fstream.close();
}

void LogData()
{

}


#endif // _DATA_H_
