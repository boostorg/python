#include <iostream>
#include <map>
#include <string>

enum choice { red, blue };

void print_choice(choice c)
{
    std::map<choice, std::string> choice_map;
    choice_map[red] = "red";
    choice_map[blue] = "blue";
    std::cout << "You chose: " << choice_map[c] << std::endl;
}

struct C
{
    choice c;

    void print_()
    {
        print_choice(c);
    }
};
