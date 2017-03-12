#include "string"
#include "fstream"
#include "iostream"
#include "vector"
#include <tuple>
using namespace std;

class TextFile
{
public:
	vector <tuple<string,size_t>> buffer;
	string fname;
void upload(string name)
	{
	    this->fname = name;
		string str;
		ifstream f_stream;
		f_stream.open(name.c_str());
		if (f_stream.is_open())
		{
			while (getline(f_stream, str))
				buffer.push_back(make_tuple(str, hash<string>{}(str)));
		}
		else
			cout << "File " << name << " doesnt exist!" << endl;
		f_stream.close();
	}
};
void difference(TextFile fdiff1, TextFile fdiff2)
{
	unsigned int j = 0;
	for (unsigned int i = 0; i < fdiff1.buffer.size(); ++i)
	{
		for (j=0; j < fdiff2.buffer.size(); ++j) 
			(get<1>(fdiff1.buffer[i]) == get<1>(fdiff2.buffer[j])) ? j+=fdiff2.buffer.size() : NULL ;
		(j == fdiff2.buffer.size()) ? cout << "File name: " << fdiff1.fname << "; line: " << i + 1 << "; difference: " << get<0>(fdiff1.buffer[i]) << endl : cout ;
	}
};
int main(int argc, char *argv[])
{
	TextFile File1, File2;
	File1.upload(argv[1]);
	File2.upload(argv[2]);
	difference(File1, File2);
	difference(File2, File1);
	system("pause");
	return 0;
};
