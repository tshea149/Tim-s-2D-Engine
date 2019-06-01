#include "Debug.h"
#include <fstream>

namespace Debug
{
	std::ofstream file_out;
	std::string filename;

	std::string getDateTime()
	{
		time_t now = time(0);
		struct tm tstruct;
		localtime_s(&tstruct, &now);
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%m-%d-%Y__%X", &tstruct);
		return std::string(buffer);
	}

	void initialize()
	{
		// Ensure the debug module is only used in debug mode.
		#ifndef _DEBUG
		std::cout << "Attempted to use debug module while not in debug mode.";
		exit(-1);
		#endif

		filename = "log_" + getDateTime() + ".txt";

		// replace ':' from time string (not allowed in filename)
		for (size_t i = 0; i < filename.size(); i++)
		{
			if (filename[i] == ':')
			{
				filename[i] = '_';
			}
		}

		file_out.open("./logs/" + filename);
	}

	void log(std::string msg)
	{
		// Ensure the debug module is only used in debug mode.
		#ifndef _DEBUG
		std::cout << "Attempted to use debug module while not in debug mode.";
		exit(-1);
		#endif

		file_out << getDateTime() + ": " + msg + '\n';
	}

	void close()
	{
		// Ensure the debug module is only used in debug mode.
		#ifndef _DEBUG
		std::cout << "Attempted to use debug module while not in debug mode.";
		exit(-1);
		#endif

		file_out.close();
	}
}
