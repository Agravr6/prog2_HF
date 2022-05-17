#pragma once

// interface ososztaly
class Image
{
	virtual void writeImage(const char* path) = 0;
	virtual void readImage() = 0;
};
