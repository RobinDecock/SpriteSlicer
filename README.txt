Made by Robin Decock.

[AnimLoader]:
Has a static function (std::map<int, AnimData> Load(std::string filePath);)
this loads in the pointed at filepath
and returns a map
[Key]: Hash value of the chosen animationName.
[Value]: AnimData:

struct AnimData
{
   Int2 RowsCols;
   Int4 Src;
};

which is a simple struct that contains:
1.the amount of rows and collumns
2.the source rectangle


[Layout of generated .Anim]
{
	<AnimName1>
	RC="1,2"
	SRC="2,1,56,32"
	<AnimName2>
	RC="1,40"
	SRC="100,65,68,16"
	<....>
	....
}

size_t ComputeHash(std::string const& s)
{
	const int hashSize = 501;
	int sum = 0;
	for (int k = 0; k < s.length(); k++)
		sum = sum + int(s[k]);
	return  sum % hashSize;
}