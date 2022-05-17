#include <iostream>
#include <vector>							// std::vector
#include "image.h"
#include <opencv2/calib3d.hpp>				// findHomography()
#include <opencv2/core/types.hpp>			// Point2f		
#include <opencv2/core/mat.hpp>				// Mat
#include <opencv2/imgproc.hpp>				// warpPerspective()

class BitMap : public Image{
private:
	unsigned char* info;
	cv::Mat bMap;
	cv::Mat modifiedBMap;
	const char* fname;
public:
	BitMap(const char* path);
	BitMap(const BitMap& other);
	~BitMap();

	void setInfo(unsigned char* param);
	void setBMap(cv::Mat param);
	void setModifiedBMap(cv::Mat param);
	void setWidth(int param);
	void setHeight(int param);

	unsigned char* getInfo() const;
	cv::Mat getBMap() const;
	cv::Mat getModifiedBMap() const;
	const char* getFname() const;
	int getHeight() const;		// kiolvassa az info tagvaltozobol a magassagi adatot
	int getWidth() const;		// kiolvassa az info tagvaltozobol a szelessegi adatot

	void readImage();
	void writeImage(const char* name);
};