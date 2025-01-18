#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

extern char** environ;

int main()
{
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++)
    {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    for (char** env = environ; *env != nullptr; ++env)
    {
        std::string env_var(*env);
        size_t pos = env_var.find('=');
        if (pos != std::string::npos)
        {
            std::string name = env_var.substr(0, pos);
            std::string value = env_var.substr(pos + 1);
            std::cout << "Variable: " << name << ", Value: " << value << std::endl;
        }
    }

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    std::cout << "Hostname: " << hostname << std::endl;

    struct utsname os_info{};
    if (uname(&os_info) == 0)
    {
        std::cout << "Operating System: " << os_info.sysname << std::endl;
        std::cout << "Node Name: " << os_info.nodename << std::endl;
        std::cout << "Release: " << os_info.release << std::endl;
        std::cout << "Version: " << os_info.version << std::endl;
        std::cout << "Machine: " << os_info.machine << std::endl;
    }
    else
    {
        std::cerr << "Failed to get OS details" << std::endl;
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
