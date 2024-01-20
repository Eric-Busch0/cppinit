#include <iostream>
#include <filesystem>
#include <fstream>

void generate_makefile(std::ofstream& makefile, std::string project)
{
    makefile << "CXX=g++\n";
    makefile << "OUT=" << project << "\n";
    makefile << "SRCS=main.cpp\n";
    makefile << "defualt:\n";
    makefile << "\t$(CXX) $(SRCS) -o $(OUT) --std=c++17\n";
    makefile << "clean:\n";
    makefile << "\trm $(OUT)\n";
    makefile << "run:\n";
    makefile << "\t ./$(OUT)\n";
}

void generate_main(std::ofstream& main_cpp)
{
    main_cpp << "#include <iostream>\n";
    main_cpp << "int main(int argc, char **argv) \n";
    main_cpp << "{\n";
    main_cpp << "\n";
    main_cpp << "return 0;\n";
    main_cpp << "}\n";



}

int main(int argc, char **argv) 
{

    if(argc < 2)
    {
        std::cout << "USAGE cppinit <project-name>\n";
        return -1;
    }

    std::string project = argv[1];

    try
    {

        if(std::filesystem::is_directory(project))
        {
            std::cout << "Directory already exists!\n";
            return 1;
        }

        std::filesystem::create_directory(project);
        std::cout << "Created directory " << project << std::endl; 
    }
    catch(const std::exception& e)
    {
        std::cerr << "error creating directory " << e.what() << '\n';
        return 1;
    }

    std::filesystem::current_path(project);

    std::ofstream makefile("Makefile");
    std::ofstream main_cpp("main.cpp");


    generate_makefile(makefile, project);
    generate_main(main_cpp);

    return 0;
}