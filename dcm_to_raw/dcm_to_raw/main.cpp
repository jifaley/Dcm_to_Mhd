#include "dcm_to_raw.h"

int main()
{
	std::vector<std::string> files;
	std::string parent_dir = R"(..\..\R_004)";

	getFilesFromDirectory(files, parent_dir.c_str()); 

	int total = files.size();
	std::cout << total << std::endl;
	system("pause");
	int count = 0;

	for (auto iter = files.cbegin(); iter != files.cend(); iter++)
	{
		std::cout << ++count << '/' << total << std::endl;
		std::string working_dir = *iter;
		std::string sid = getSerialID(working_dir);
		std::cout << sid << std::endl;
		convert(working_dir, sid, "short", working_dir);
	}
	return 0;
}