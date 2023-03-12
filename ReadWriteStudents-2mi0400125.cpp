#include <iostream>
#include <fstream>

#pragma warning (disable : 4996)

//Ioan Grozev 2MI0400125

const size_t MAX_SIZE = 1024;
const unsigned SPEC_DIGIT_POS = 4;

enum class Major
{
	Informatics = 4,
	ComputerScience = 8,
	SoftwareEngineering = 6
};

struct Student
{
	Major major;

	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	char email[MAX_SIZE];
	char fn[MAX_SIZE];
};
struct StudentsCollection
{
	Student* data;
	unsigned int students_number;
};

unsigned int getStudentsCount(std::ifstream& file)
{
	char buff[MAX_SIZE];
	unsigned int studentsCount = 0;

	while (!file.eof())
	{
		file.getline(buff, MAX_SIZE);
		studentsCount++;
	}

	file.seekg(0, std::ios::beg);
	return studentsCount - 1;
}

void parseField(char* dest, const char*& src)
{
	while (*src != ',' && *src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}

	src++;
	*dest = '\0';
}

void setMajor(Student& student)
{
	if (student.fn[SPEC_DIGIT_POS] == (int)Major::Informatics)
	{
		student.major = Major::Informatics;
	}
	else if (student.fn[SPEC_DIGIT_POS] == (int)Major::ComputerScience)
	{
		student.major = Major::ComputerScience;
	}
	else if (student.fn[SPEC_DIGIT_POS] == (int)Major::SoftwareEngineering)
	{
		student.major = Major::SoftwareEngineering;
	}
}

void initialiseStudent(Student& student, const char* line)
{
	parseField(student.firstName, line);
	parseField(student.lastName, line);
	parseField(student.email, line);
	parseField(student.fn, line);

	setMajor(student);
}

int fillStudentsCollection(StudentsCollection& collection, const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "File can't be opened!" << std::endl;
		return -1;
	}

	unsigned int studentsCount = getStudentsCount(file);
	collection.students_number = studentsCount;
	collection.data = new Student[studentsCount];

	char buff[MAX_SIZE];
	file.getline(buff, MAX_SIZE);
	for (size_t i = 0; i < studentsCount; i++)
	{
		file.getline(buff, MAX_SIZE);
		initialiseStudent(collection.data[i], buff);
	}

	file.close();
	return studentsCount;
}

void printByFn(const StudentsCollection& collection, const char* fn, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(collection.data[i].fn, fn) == 0)
		{
			std::cout << "Name: " << collection.data[i].firstName << ' ' << collection.data[i].lastName <<
				", Email: " << collection.data[i].email << ", FN: " << collection.data[i].fn << std::endl;
			if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::Informatics)
			{
				std::cout << "Major: Informatics" << std::endl;
			}
			else if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::ComputerScience)
			{
				std::cout << "Major: Computer science" << std::endl;
			}
			else if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::SoftwareEngineering)
			{
				std::cout << "Major: Software engineering" << std::endl;
			}
		}
	}
}

void Edit_Email(const char* new_email , char* old_email )
{
	while (*new_email != '\0')
	{
		*old_email = *new_email;
		old_email++;
		new_email++;
	}
	*old_email = '\0';
}

void replace_email(StudentsCollection& s, const char* FN, const char* new_email)
{
	for (int i = 0; i < s.students_number; i++)
	{
		if (strcmp(s.data[i].fn, FN) == 0)
		{
			Edit_Email(new_email, s.data[i].email);
		}
	}
}

void save_in_file(const StudentsCollection& s, const char* name_of_file)
{
	std::ofstream file(name_of_file);
	if (!file.is_open())
	{
		std::cout<<"Error";
	}
	file << "First name,Last name,Email address,FN";
	for (int i = 0; i < s.students_number; i++)
	{
		file << std::endl;
		file << s.data[i].firstName << ',';
		file << s.data[i].lastName << ',';
		file << s.data[i].email << ',';
		file << s.data[i].fn ;
	}
	
	file.close();
}

int main()
{
	std::cout << "Open file: ";
	char fileName[MAX_SIZE];
	std::cin >> fileName;

	StudentsCollection collection;
	int size = fillStudentsCollection(collection, fileName);
	if (size == -1)
	{
		return -1;
	}

	std::cout << "File successfully opened!" << std::endl << std::endl;

	char command[MAX_SIZE];

	do
	{
		
		std::cin >> command;

		if (strcmp(command, "print") == 0)
		{
			char fn[MAX_SIZE];
			std::cin >> fn;

			printByFn(collection, fn, size);
			std::cout << std::endl;

		}

		if (strcmp(command, "edit") == 0)
		{
			char fn[MAX_SIZE];
			std::cin >> fn;

			char email[MAX_SIZE];
			std::cin >> email;

			replace_email(collection, fn, email);
			std::cout << std::endl;
		}

		if (strcmp(command, "save") == 0)
		{
			char file_name[MAX_SIZE];
			std::cin >> file_name;

			save_in_file(collection,  file_name);
			
		}
		
	} while (strcmp(command, "save") != 0);

	
	
	// HW: Implement the rest of the commands

	delete[] collection.data;
}