/*
Varga Csaba - K0****
Porgramozás alapjai 2 - nagy házi feladat
2021/2022/2
fénykép torzítás megszûntetése
Felhasznált külsõ libraryk: OpenCV - https://opencv.org/	Windows.h
GitHub - https://github.com/Agravr6/prog2_HF
*/
#include "BitMap.h"
#include <Windows.h> // system("cls")

std::vector<cv::Point2f> findDestination(int horizonLine, BitMap bmp);
std::vector<cv::Point2f> getSourcePoints(BitMap);

int main() {
	char* fname = new char[255];	// windowsba max 255 karakter hosszu lehet egy fajl neve
	int HL;							// Horizont vonal
	char answer;
	do
	{
		system("cls");
		std::cout << "Enter the filename: ";
		std::cin >> fname;

		// peldanyositjuk az osztalyunkat es beolvassuk a kepet
		BitMap pic(fname);
		try {
			pic.readImage();
		}
		catch (const char* err) {
			system("cls");
			std::cout << err << std::endl;
			std::cout << "Do you want to try again? (Y - to try again | anything else to exit)" << std::endl;
			std::cin >> answer;
			if (answer != 'Y')
				return 0;
			continue;
		}

		std::cout << "Enter the horizon line: ";
		std::cin >> HL;
		try {
			if (HL < 0)
				throw "Invalid input. Horizon Line is negative";
			else if (HL > pic.getHeight())
				throw "Invalid input. Horizon Line is greater than the height of the picture";
		}
		catch (const char* err) {
			system("cls");
			std::cout << err << std::endl;
			std::cout << "Do you want to try again? (Y - to try again | anything else to exit)" << std::endl;
			std::cin >> answer;
			if (answer == 'Y')
				continue;
			return 0;
		}
		std::vector<cv::Point2f> source;
		try {
			source = getSourcePoints(pic);
		}
		catch (const char* err) {
			system("cls");
			std::cout << err << std::endl;
			std::cout << "Do you want to try again? (Y - to try again | anything else to exit)" << std::endl;
			std::cin >> answer;
			if (answer == 'Y')
				continue;
			return 0;
		}
		
		std::vector<cv::Point2f> destination = findDestination(HL, pic);
		
		// bMap masolatanak tarolasa ModifiedBMap-ban
		pic.setModifiedBMap(pic.getBMap());
		// homografia matrix kiszamitasa
		cv::Mat h = cv::findHomography(source, destination);
		// transzformacio elvegzese
		cv::warpPerspective(pic.getBMap(), pic.getModifiedBMap(), h, pic.getModifiedBMap().size());
		char* outputName = new char[255];
		system("cls");
		std::cout << "Enter output filename(without extension): ";
		std::cin >> outputName;
		try {
			pic.writeImage(outputName);
		}
		catch (const char* err) {
			system("cls");
			std::cout << err << std::endl;
			std::cout << "Do you want to try again? (Y/N) ";
			std::cin >> answer;
			if (answer == 'Y')
				main();
			return 0;
		}
		
		std::cout << "Image transformation was successfull" << std::endl;
		std::cout << "Do you want to transform a new image? (Y/N)" << std::endl;
		std::cin >> answer;

	} while (answer == 'Y');	// ameddig Y valasz erkezik, addig "meglesz hivva a main" es lehet uj kepeket beolvasni
	return 0;
}


std::vector<cv::Point2f> getSourcePoints(BitMap bmp) {
	std::vector<cv::Point2f> src;
	int x, y;
	char c;
	std::cout << "format: (x,y)" << std::endl;
	std::cout << "Coords of Top-left corner: ";
	std::cin >> c;
	if (c != '(') {
		throw "Invalid input format";
	}
	std::cin >> x;
	if (x < 0) {
		throw "Invalid input. X coordinate is negative";
	}
	else if (x > bmp.getWidth()) {
		throw "Invalid input. X coordiante is greater than the width of the picture";
	}
	std::cin >> c;
	if (c != ',') {
		throw "Invalid input format";
	}
	std::cin >> y;
	if (y < 0) {
		throw "Invalid input. Y coordinate is negative";
	}
	else if (y > bmp.getHeight()) {
		throw "Invalid input. Y cooridnate is greater than the height of the picture";
	}
	std::cin >> c;
	if (c != ')') {
		throw "Invalid input format";
	}
	//top-left
	src.push_back(cv::Point2f(x, y));			

	std::cout << "Coords of Bottom-left corner: ";
	std::cin >> c;
	if (c != '(') {
		throw "Invalid input format";
	}
	std::cin >> x;
	if (x < 0) {
		throw "Invalid input. X coordinate is negative";
	}
	else if (x > bmp.getWidth()) {
		throw "Invalid input. X coordiante is greater than the width of the picture";
	}
	std::cin >> c;
	if (c != ',') {
		throw "Invalid input format";
	}
	std::cin >> y;
	if (y < 0) {
		throw "Invalid input. Y coordinate is negative";
	}
	else if (y > bmp.getHeight()) {
		throw "Invalid input. Y cooridnate is greater than the height of the picture";
	}
	std::cin >> c;
	if (c != ')') {
		throw "Invalid input format";
	}
	//bottom-left
	src.push_back(cv::Point2f(x, y));		

	std::cout << "Coords of Bottom-right corner: ";
	std::cin >> c;
	if (c != '(') {
		throw "Invalid input format";
	}
	std::cin >> x;
	if (x < 0) {
		throw "Invalid input. X coordinate is negative";
	}
	else if (x > bmp.getWidth()) {
		throw "Invalid input. X coordiante is greater than the width of the picture";
	}
	std::cin >> c;
	if (c != ',') {
		throw "Invalid input format";
	}
	std::cin >> y;
	if (y < 0) {
		throw "Invalid input. Y coordinate is negative";
	}
	else if (y > bmp.getHeight()) {
		throw "Invalid input. Y cooridnate is greater than the height of the picture";
	}
	std::cin >> c;
	if (c != ')') {
		throw "Invalid input format";
	}
	//bottom-right
	src.push_back(cv::Point2f(x, y));		

	std::cout << "Coords of Top-right corner: ";
	std::cin >> c;
	if (c != '(') {
		throw "Invalid input format";
	}
	std::cin >> x;
	if (x < 0) {
		throw "Invalid input. X coordinate is negative";
	}
	else if (x > bmp.getWidth()) {
		throw "Invalid input. X coordiante is greater than the width of the picture";
	}
	std::cin >> c;
	if (c != ',') {
		throw "Invalid input format";
	}
	std::cin >> y;
	if (y < 0) {
		throw "Invalid input. Y coordinate is negative";
	}
	else if (y > bmp.getHeight()) {
		throw "Invalid input. Y cooridnate is greater than the height of the picture";
	}
	std::cin >> c;
	if (c != ')') {
		throw "Invalid input format";
	}
	//top-right
	src.push_back(cv::Point2f(x, y));		
	return src;
}



// a feladat kiirasa szerint meghatarozza, hogy hol lesz a modifikalt kep 4 csucspontja
std::vector<cv::Point2f> findDestination(int horizonLine, BitMap bmp)
{
	std::vector<cv::Point2f> destination;
	// "kinullazzuk" a vectort
	destination.clear();
	// Ha a horizont vonal felett van nagyobb terulet
	if (horizonLine >= bmp.getBMap().rows / 2)
	{
		destination.push_back(cv::Point2f(0, 0));									//top-left
		destination.push_back(cv::Point2f(0, horizonLine));							//bottom-left
		destination.push_back(cv::Point2f(bmp.getBMap().cols, horizonLine));		//bottom-right
		destination.push_back(cv::Point2f(bmp.getBMap().cols, 0));					//top-right
	}

	// Ha a horizont vonal alatt van nagyobb terulet
	else
	{
		destination.push_back(cv::Point2f(0, horizonLine));							//top-left
		destination.push_back(cv::Point2f(0, bmp.getBMap().rows));					//bottom-left
		destination.push_back(cv::Point2f(bmp.getBMap().cols, bmp.getBMap().rows));	//bottom-right
		destination.push_back(cv::Point2f(bmp.getBMap().cols, horizonLine));		//top-right
	}
	return destination;
}
