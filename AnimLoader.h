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

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NON INFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <string>
#include <map>
#include <fstream>

namespace Anim
{
	class AnimLoader
	{
	public:
		typedef int Hash;

		struct Int2
		{
			Int2(int x, int y) : vx{x}, vy{y}
			{
			}

			int vx{};
			int vy{};
		};

		struct Int4
		{
			Int4(int x, int y, int width, int height) : vX{x}, vY{y}, vWidth{width}, vHeight{height}
			{
			}

			int vX{};
			int vY{};
			int vWidth{};
			int vHeight{};
		};

		struct AnimData
		{
			AnimData(Int2 rc, Int4 s): RowsCols(rc), Src(s)
			{
			}

			Int2 RowsCols;
			Int4 Src;
		};

		static std::map<int, AnimData> Load(const std::string& filePath)
		{
			std::map<int, AnimData> animMap;
			std::ifstream inputStream(filePath.c_str());
			std::string line{};

			if (!inputStream.is_open())
			{
				//Logger::LogWarning("[Animation File: Invalid FilePath]");
				inputStream.close();
				return std::map<int, AnimData>();
			}


			std::getline(inputStream, line);
			int index = 0;
			while (!inputStream.eof())
			{
				const int endName = line.find('>');
				if (endName == -1)
				{
					//Logger::LogWarning("[Animation File: Invalid Format]");
					inputStream.close();
					return std::map<int, AnimData>();
				}

				std::string name = line.substr(1, endName - 1);


				std::getline(inputStream, line);
				const Int2 RC = GetVec2FromLine("RC", line);
				std::getline(inputStream, line);
				const Int4 Rect = GetVec4FromLine("SRC", line);
				std::getline(inputStream, line);

				animMap.insert(std::pair<int, AnimData>(index, AnimData(Int2(RC.vx, RC.vy), Rect)));

				if (line.empty())break;

				index += 1;
			}

			inputStream.close();
			return animMap;
		}

	private:
		static Int4 GetVec4FromLine(const std::string& paramName,const std::string& line)
		{
			const size_t paramBegin = line.find(paramName) + paramName.size() + 2;
			const size_t commaPos1 = line.find(',', paramBegin);
			std::string param = line.substr(paramBegin, commaPos1 - paramBegin);
			const int value1 = std::stoi(param);

			const size_t commaPos2 = line.find(',', commaPos1 + 1);
			param = line.substr(commaPos1 + 1, commaPos2 - commaPos1);
			const int value2 = std::stoi(param);

			const size_t commaPos3 = line.find(',', commaPos2 + 1);
			param = line.substr(commaPos2 + 1, commaPos3 - commaPos2);
			const int value3 = std::stoi(param);

			const size_t commaPos4 = line.find('\"', commaPos3) - 1;
			param = line.substr(commaPos3 + 1, commaPos4 - commaPos3);
			const int value4 = std::stoi(param);


			return Int4(value1, value2, value3, value4);
		}

		static Int2 GetVec2FromLine(const std::string& paramName,const std::string& line)
		{
			const size_t paramBegin = line.find(paramName) + paramName.size() + 2;
			const size_t commaPos1 = line.find(',', paramBegin);
			std::string param = line.substr(paramBegin, commaPos1 - paramBegin);
			const int value1 = std::stoi(param);

			const size_t commaPos2 = line.find('\"', commaPos1 + 1) - 1;
			param = line.substr(commaPos1 + 1, commaPos2 - commaPos1);
			const int value2 = std::stoi(param);

			return Int2(value1, value2);
		}
	};
}
