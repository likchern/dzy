#pragma once
#include <filesystem>
#include <string>
class Utils
{
public:
	static std::filesystem::path source();
	static void iterate();
private:
	static void iterate_jpg();
	static void iterate_png();
};

std::filesystem::path Utils::source()
{
	std::filesystem::path path = std::filesystem::current_path();
		path += "\\bmp";
		return path;
}

void stretch() 
{
	Utils::source();
	struct _finddata_t fileinfo;
	intptr_t hFile;
	if ((hFile = _findfirst("*.bmp", &fileinfo)) == -1)
	{
		return;
	}
	do
	{
		//load and save picture into source
		int iw, ih, channels;
		// Loading Pictures to Get Wide, High and Color Channel Information
		unsigned char* img = stbi_load(fileinfo.name, &iw, &ih, &channels, 0);
		if (iw>150 || ih>150)
		{
			int desireWidth = iw;
			int desireHeight = ih;
			while (iw > 150)
			{
				desireWidth = iw / 2;
				iw = desireWidth;
			}
			while (ih > 150)
			{
				desireHeight = ih / 2;
				ih = desireHeight;
			}
			auto buffer = new unsigned char[desireHeight * desireWidth * channels];

			stbir_resize_uint8(img, iw, ih, 0, buffer, desireWidth, desireHeight, 0, channels);

			stbi_write_bmp(fileinfo.name, desireWidth, desireHeight, channels, buffer);
			delete[] buffer;
		}
		stbi_image_free(img);
	} while (_findnext(hFile, &fileinfo) == 0);
	_findclose(hFile);
	return;
}
void Utils::iterate()
{
	std::filesystem::current_path(Utils::source());
	Utils::iterate_jpg;
	Utils::iterate_jpg;
}
void Utils::iterate_jpg()
{

	struct _finddata_t fileinfo;
	intptr_t hFile;
		if ((hFile = _findfirst("*.jpg", &fileinfo)) == -1)
		{
			return;
		}
		do
		{
			//load and save picture into source
			int iw, ih, n;
			// Loading Pictures to Get Wide, High and Color Channel Information
			unsigned char* img = stbi_load(fileinfo.name, &iw, &ih, &n, 3);
			size_t lastindex =std::string(fileinfo.name).find_last_of(".");
			std::string rawname = std::string(fileinfo.name).substr(0, lastindex) +".bmp";
			stbi_write_bmp(rawname.c_str(), iw, ih, n, img);
			stbi_image_free(img);
		} while (_findnext(hFile, &fileinfo) == 0);
	_findclose(hFile);
	return;
}

void Utils::iterate_png()
{
	struct _finddata_t fileinfo;
	intptr_t hFile;
	if ((hFile = _findfirst("*.png", &fileinfo)) == -1)
	{
		return;
	}
	do
	{
		//load and save picture into source
		int iw, ih, n;
		// Loading Pictures to Get Wide, High and Color Channel Information
		unsigned char* img = stbi_load(fileinfo.name, &iw, &ih, &n, 3);
		size_t lastindex = std::string(fileinfo.name).find_last_of(".");
		std::string rawname = std::string(fileinfo.name).substr(0, lastindex) + ".bmp";
		stbi_write_bmp(rawname.c_str(), iw, ih, n, img);
		stbi_image_free(img);
	} while (_findnext(hFile, &fileinfo) == 0);
	_findclose(hFile);
	return;
}

