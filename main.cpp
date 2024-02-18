#include <iostream>
#include <filesystem>
#include <fstream>
#include <string.h>

typedef enum
{
    C_PROJECT,
    CPP_PROJECT,
} project_type_t;

void generate_makefile(std::ofstream &makefile, std::string project, project_type_t project_type)
{

    std::string compiler = project_type == CPP_PROJECT ? "CXX=g++\n" : "CXX=gcc\n";
    std::string srcs = project_type == CPP_PROJECT ? "SRCS=main.cpp\n" : "SRCS=main.c\n";
    std::string standard = project_type == CPP_PROJECT ? "--std=c++17\n" : "--std=c11\n";
    makefile << compiler;
    makefile << "OUT=" << project << "\n";
    makefile << srcs;
    makefile << "defualt:\n";
    makefile << "\t$(CXX) $(SRCS) -o $(OUT)" << " " << standard;
    makefile << "clean:\n";
    makefile << "\trm $(OUT)\n";
    makefile << "run:\n";
    makefile << "\t ./$(OUT)\n";
}

void generate_main(std::ofstream &main_cpp, project_type_t project_type)
{
    std::string base_include = project_type == CPP_PROJECT ? "#include <iostream>\n" : "#include <stdio.h>";

    main_cpp << base_include;
    main_cpp << "\n";
    main_cpp << "\n";
    main_cpp << "\n";
    main_cpp << "int main(int argc, char **argv) \n";
    main_cpp << "{\n";
    main_cpp << "\n";
    main_cpp << "\treturn 0;\n";
    main_cpp << "}\n";
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        std::cout << "USAGE cppinit <project-name>\n";
        return -1;
    }

    std::string project = argv[1];
    project_type_t project_type = CPP_PROJECT;

    if (argc == 3)
    {
        if (strcmp("-c", argv[2]) == 0)
        {
            project_type = C_PROJECT;
        }
    }

    switch (project_type)
    {
    case C_PROJECT:
        std::cout << "generating c project\n";
        break;
    case CPP_PROJECT:
        std::cout << "generating cpp project\n";
    default:
        break;
    }

    try
    {

        if (std::filesystem::is_directory(project))
        {
            std::cout << "Directory already exists!\n";
            return 1;
        }

        std::filesystem::create_directory(project);
        std::cout << "Created directory " << project << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "error creating directory " << e.what() << '\n';
        return 1;
    }

    std::filesystem::current_path(project);

    std::ofstream makefile("Makefile");

    std::ofstream main_cxx;

    if (project_type == C_PROJECT)
    {
        main_cxx.open("main.c");
    }
    else
    {
        main_cxx.open("main.cpp");
    }

    generate_makefile(makefile, project, project_type);
    generate_main(main_cxx, project_type);

    return 0;
}