#include "BitMap.h"

BitMap::BitMap(const char* path)
{
	cv::Mat t;
	bMap = t;
	modifiedBMap = t;
	fname = path;
	info = nullptr;
}

BitMap::BitMap(const BitMap& other)
{
	this->bMap = other.bMap;
	this->modifiedBMap = other.modifiedBMap;
	this->fname = other.fname;
	this->info = other.info;
}

BitMap::~BitMap()
{
}

// a bmp file info headerjenek modositasa
void BitMap::setInfo(unsigned char* param)
{
	this->info = param;
}

// a bit terkep elmentese cv::Mat tipusu matrixban
void BitMap::setBMap(cv::Mat param)
{
	this->bMap = param;
}

// a bit terkep elmentese cv::Mat tipusu matrixban
void BitMap::setModifiedBMap(cv::Mat param)
{
	this->modifiedBMap = param;
}

// az info header-on belul a szelesseg modositja
void BitMap::setWidth(int param)
{
	info[18] = param;
	info[19] = param >> 8;
	info[20] = param >> 16;
	info[21] = param >> 24;
}

// az info header-on belul a magassagot modositja	
void BitMap::setHeight(int param) 
{
	info[22] = param;
	info[23] = param >> 8;
	info[24] = param >> 16;
	info[25] = param >> 24;
}

// info header lekerese
unsigned char* BitMap::getInfo() const
{
	return info;
}

// bit terkep matrixanak lekerese
cv::Mat BitMap::getBMap() const
{
	return bMap;
}

cv::Mat BitMap::getModifiedBMap() const
{
	return modifiedBMap;
}

// megadott fajlnev lekerese
const char* BitMap::getFname() const
{
	return fname;
}

// info header-bol a magassag adat lekerese
int BitMap::getHeight() const
{
	int height = 0;
	memcpy(&height, info + 22, sizeof(int));
	return height;
}
// info header-bol a szelesseg adat lekerese
int BitMap::getWidth() const
{
	int width = 0;
	memcpy(&width, info + 18, sizeof(int));
	return width;
}

// bmp kep beolvasasa
void BitMap::readImage()
{
	FILE* f;
	fopen_s(&f, fname, "rb");
	if (f) 
	{
		// info header-nek helyet fogalunk
		info = new unsigned char[54];
		// beolvassuk az info header-t
		fread(info, sizeof(unsigned char), 54, f);

		// magassag es szelesseg kiolvasasa az info header-bol
		int width = getWidth();
		int height = getHeight();
		
		// 3 byte hely foglalasa pixelenkent
		int size = 3 * width * abs(height);
		unsigned char* data = new unsigned char[size];

		// a bit terkep beolvasasa egy lepesben
		fread(data, sizeof(unsigned char), size, f);
		fclose(f);

		// CV_8UC3 - 24 bites kepeket tarolunk
		cv::Mat m(height, width, CV_8UC3, data);
		// a kep fejjel lefele van eltarolva a bit terkepben ezert megforditjuk
		cv::flip(m, m, 0);
		setBMap(m);
		return;
	}
	else 
	{
		throw "File could not be opened";
	}
}

void BitMap::writeImage(const char* name)
{
	strcat_s(const_cast<char *>(name) + strlen(name),sizeof(".bmp"), ".bmp");
	FILE* f;
	fopen_s(&f, name, "wb");
	if (f)
	{
		// megforditjuk a bit terkepet, hogy jol legyen tajolva
		cv::flip(this->modifiedBMap, this->modifiedBMap, 0);

		// helyet foglalunk a kiirando adatoknak
		int size = this->modifiedBMap.rows * this->modifiedBMap.cols * 3; 

		unsigned char* data = new unsigned char[size];
		
		data = this->modifiedBMap.data;

		// az info header kiirasa
		fwrite(info, sizeof(unsigned char), 54, f);
		// a bit terkep kiirasa
		fwrite(data, sizeof(unsigned char), size, f);

		fclose(f);
		delete[] data;
		return;
	}
	else
	{
		throw "Destination file could not be opened/created";
	}
}