#include "dcm_to_raw.h"

std::string getSerialID(const std::string working_dir)
{
	int ret;
	std::string command =  std::string("c3d -dicom-series-list ")  + '\"' + working_dir + '\"';
	command = command + std::string(" > series_list.txt");
	//std::cout << command << std::endl;
	ret = system(command.c_str());
	if (ret != 0)
	{
		std::cout << "DICOM Series List Loading Error!" << std::endl;
		return "";
	}
	FILE* fp = NULL;
	std::string bufferstring = "";
	ret = fopen_s(&fp, "series_list.txt", "r");
	if (ret == 0)
	{
		char* buffer = (char*)malloc(10000);
		fgets(buffer, 10000, fp);
		fgets(buffer, 10000, fp);
		bufferstring = buffer;
		int last_tab = bufferstring.rfind('\t');
		bufferstring = bufferstring.substr(last_tab+1, bufferstring.length()-last_tab-2);
		//puts(buffer);
		//std::cout << bufferstring << std::endl;
		free(buffer);
	}
	fclose(fp);
	return bufferstring;
}


void convert(std::string working_dir, std::string serial_id, std::string option, std::string output_dir)
{
	std::string command = "c3d.exe -dicom-series-read ";
	command = command + '\"' + working_dir + '\"' + ' '  + serial_id;
	command = command + " -type " + option;
	command = command + " -omc ";
	command = command + '\"' + output_dir + '\\' + serial_id + ".mhd" +'\"';
	std::cout << command << std::endl;
	system(command.c_str());
}

void getFilesFromDirectory(std::vector<std::string>& files, const char* directoryPath)
{
	struct _finddata_t fileinfo;
	long hFile = 0;
	char tmpPath[MAX_PATH] = { 0 };
	sprintf(tmpPath, "%s\\*", directoryPath);
	if ((hFile = _findfirst(tmpPath, &fileinfo)) == -1) { return; }
	bool have_subdir = false;
	do
	{
		if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				have_subdir = true;
				sprintf(tmpPath, "%s\\%s", directoryPath, fileinfo.name);
				getFilesFromDirectory(files, tmpPath);
			}
		}
	} while (_findnext(hFile, &fileinfo) == 0);
	_findclose(hFile);
	if (!have_subdir)
	{
		files.push_back(std::string(directoryPath));
	}
}