#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string projectName;
    if (argc > 1) {
        projectName = argv[1];
    } else {
        while (projectName.empty()) {
            system("clear");
            std::cout << "Please enter the name for the project" << '\n';
            std::cin >> projectName;
        }
    }
    std::ofstream CMakeLists("CMakeLists.txt");

    CMakeLists << "cmake_minimum_required(VERSION 3.25)\n\n";

    CMakeLists << "project(" << projectName << "LANGUAGES C CXX)\n\n";

    CMakeLists << "set(CMAKE_CXX_STANDARD 20)\n";
    CMakeLists << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n";
    CMakeLists << "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n";

    CMakeLists << "find_package(Vulkan REQUIRED)\n";
    CMakeLists << "find_package(PkgConfig REQUIRED)\n";
    CMakeLists << "pkg_check_modules(GLFW3 REQUIRED glfw3)\n\n";

    CMakeLists << "include_directories(\n"
               << "${Vulkan_INCLUDE_DIRS}\n"
               << "${GLFW3_INCLUDE_DIRS}\n"
               << ")\n\n";

    CMakeLists << "add_executable(${PROJECT_NAME} src/main.cpp)\n\n";

    CMakeLists << "target_link_libraries(${PROJECT_NAME}\n"
               << "${Vulkan_LIBRARIES}\n"
               << "${GLFW3_LIBRARIES})\n";

    CMakeLists << "target_include_directories(${PROJECT_NAME} PUBLIC "
                  "\"${CMAKE_CURRENT_SOURCE_DIR}/include\")";

    CMakeLists.close();
    system("mkdir build");
    system("mkdir src");
    system("mkdir include");

    std::ofstream main("src/main.cpp");
    main << "#include <iostream>\n"
         << "#include <vulkan/vulkan.h>\n\n";
    main << "int main() {\n"
         << "uint32_t version = 0;\n"
         << "vkEnumerateInstanceVersion(&version);\n"
         << "std::cout << \"Vulkan API Version: \" << \n"
            "VK_VERSION_MAJOR(version) << \".\";\n"
         << "return 0;\n"
         << "}";
    main.close();

    std::system("cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON");

    return 0;
}
