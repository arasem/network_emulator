

#include "iostream"

typedef void (*rectangle_cb_t)( void *data);

class Rectangle {
    int width, height;

  public:
    rectangle_cb_t cb;

};

static void event_cb( void *data){

    std::cout << "callback \n" ;

}

int main(){
    int value = 5;
    void *ptr = &value;

    Rectangle Rec1;
    Rec1.cb = event_cb;
    Rec1.cb(ptr);

    std::cout << "Hello \n";

return 0;

}

