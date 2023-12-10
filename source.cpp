#include <iostream>
#include <string>
#include <Windows.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;

struct xyPoint
{
	int x;
	int y;
	bool click;
};

int main()
{
	POINT point;
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = VK_LBUTTON;
	xyPoint xy{};
	xyPoint xy_ld{};
	nlohmann::json j{};
	nlohmann::json j_ld{};
	ofstream fout;
	fout.open("file.json");
	ifstream fin;
	fin.open("file.json");
	int counter = 0;

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		GetCursorPos(&point);
		xy.x = point.x;
		xy.y = point.y;
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			xy.click = true;
		}
		else
		{
			xy.click = false;
		}
		j["x"] = xy.x;
		j["y"] = xy.y;
		j["click"] = xy.click;
		fout << j << endl;
		cout << j << endl;
		counter++;
	}
	for (int i = 0; i < counter; i++)
	{
		fin >> j;
		string serString = j.dump();
		j_ld = nlohmann::json::parse(serString);
		xy_ld.x = j_ld["x"].get<int>();
		xy_ld.y = j_ld["y"].get<int>();
		xy_ld.click = j_ld["click"].get<bool>();
		cout << j_ld << endl;
		SetCursorPos(xy_ld.x, xy_ld.y);
		if (xy_ld.click)
		{

			SendInput(1, &input, sizeof(INPUT));

		}
	}
	fout.close();
	fin.close();
	return 0;
}
