#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H

class TApplication {
public:
    static int execute();   // Executes the main thread
private:
    static bool menu(char&); // Shows the menu and waiting for user's choice
};


#endif //OOP_APPLICATION_H
