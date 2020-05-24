/*
	Copyright(c) <2020> <Robin Decock>
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this softwareand associated documentation
	files(the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and /or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions :

	The above copyright noticeand this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <string>
#include <map>
#include <fstream>

static class AnimLoader
{
public:
	struct Int2
	{
		Int2() {}
		Int2(int x, int y) :vx{ x }, vy{ y }
		{}
		int vx;
		int vy;
	};
	struct Int4
	{
		Int4() {}
		Int4(int x, int y, int width, int height) :vX{ x }, vY{ y }, vWidth{ width }, vHeight{ height }
		{}
		int vX;
		int vY;
		int vWidth;
		int vHeight;
	};
	struct AnimData
	{
		Int2 RowsCols;
		Int4 Src;
	};
	static std::map<int, AnimData> Load(std::string filePath)
	{
		int index = 0;
		std::map<std::string, std::map<int, AnimData>>::iterator it = AnimTexMap.find(filePath);
		if (it != AnimTexMap.end())
		{
			return AnimTexMap[filePath];
		}

		std::map<int, AnimData> animMap;
		std::ifstream inputStream(filePath.c_str());
		std::string line = "";

		if (!inputStream.is_open())
		{
			//Logger::LogWarning("[Animation File: Invalid FilePath]");
			inputStream.close();
			return std::map<int, AnimData>();
		}


		std::getline(inputStream, line);
		while (!inputStream.eof())
		{
			size_t endName = line.find(">");
			if (endName == -1)
			{
				//Logger::LogWarning("[Animation File: Invalid Format]");
				inputStream.close();
				return std::map<int, AnimData>();
			}

			std::string name = line.substr(1, endName - 1);
			animMap.insert(std::pair<int, AnimData>(index, AnimData()));
			std::getline(inputStream, line);
			int2 RC = GetVec2FromLine("RC", line);
			std::getline(inputStream, line);
			int4 Rect = GetVec4FromLine("SRC", line);
			std::getline(inputStream, line);

			animMap[index].RowsCols = int2(RC.x, RC.y);
			animMap[index].Src = Rect;
			index += 1;
			if (line == "")break;
		}

		inputStream.close();

		AnimTexMap.insert(std::pair<std::string, std::map<int, AnimData>>(filePath, animMap));
		return animMap;
	}
private:
	static Int4 GetVec4FromLine(std::string paramName, std::string line)
	{
		int paramBegin = line.find(paramName) + paramName.size() + 2;
		int commaPos1 = line.find(",", paramBegin);
		std::string param = line.substr(paramBegin, commaPos1 - paramBegin);
		int value1 = std::stoi(param);

		int commaPos2 = line.find(",", commaPos1 + 1);
		param = line.substr(commaPos1 + 1, commaPos2 - commaPos1);
		int value2 = std::stoi(param);

		int commaPos3 = line.find(",", commaPos2 + 1);
		param = line.substr(commaPos2 + 1, commaPos3 - commaPos2);
		int value3 = std::stoi(param);

		int commaPos4 = line.find("\"", commaPos3) - 1;
		param = line.substr(commaPos3 + 1, commaPos4 - commaPos3);
		int value4 = std::stoi(param);


		return Int4(value1, value2, value3, value4);
	}

	static Int2 GetVec2FromLine(std::string paramName, std::string line)
	{
		int paramBegin = line.find(paramName) + paramName.size() + 2;
		int commaPos1 = line.find(",", paramBegin);
		std::string param = line.substr(paramBegin, commaPos1 - paramBegin);
		int value1 = std::stoi(param);

		int commaPos2 = line.find("\"", commaPos1 + 1) - 1;
		param = line.substr(commaPos1 + 1, commaPos2 - commaPos1);
		int value2 = std::stoi(param);

		return Int2(value1, value2);
	}
};
