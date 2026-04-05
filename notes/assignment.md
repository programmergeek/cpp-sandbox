# Variables

In C++, as in every other systems programming language, a variable is a name given to a location in memory. You can assign a value to that location in memory as long as it can fit within the allocated space and is of the correct type. The amount memory for variables types like `char`, `void`, etc, is dependant on the system you running the program on. For example, if you are on a 32-bit system, then `char`s will awalys be 4 bytes long, 8 on 64-bit systems.

It is for this reason, among other reasons, why you can't run 64-bit programs on 32-bit systems. Data is lost because there is just not enough space i.e pointer truncation.

The fundanmental data types in c++ are:
    - `char`
    - `int`
    - `bool`
    - `void`
    - `float`
    - `double`
    - `long`
    - `signed`
    - `unsigned`
