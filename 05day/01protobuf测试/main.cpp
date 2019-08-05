#include "Test.protoc.pb.h"

using namespace std;

int main()
{
	Test::Student stu1;

	stu1.set_no(10);
	stu1.set_name ("syw");

	string buf1;
	stu1.AppendToString(&buf1);

	//08 0A 12 03 73 79 77
	for (char c : buf1)
	{
		printf("%02X ", c);
	}
	cout << endl;


	Test::Student stu2;
	string buf2 = "\x08\x0A\x12\x03\x73\x79\x77";
	stu2.ParseFromString(buf2);
	printf("no = %d\n", stu2.no());
	printf("name = %s\n", stu2.name().data());



	return 0;
}