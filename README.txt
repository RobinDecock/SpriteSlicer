Made by Robin Decock.

[AnimLoader]:
Has a static function (std::map<int, AnimData> Load(std::string filePath);)
this loads in the pointed at filepath
and returns a map
[Key]: Index value of animData(is visible in the spriteslicer next to the name)
the .Anim file will also contain a generated enum that you can cast to an int, to get the right data out of the map.
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

	//GENERATED ENUM:
	enum AnimType
	{
	AnimName1,AnimName2
	}
}