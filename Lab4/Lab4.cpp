#include <iostream>
#include <string>

// Subject
class Graphic {
public:
    virtual void draw() const = 0;
    virtual void move(int x, int y) = 0;
    virtual ~Graphic() {}
};

// Real Subject
class RealImage : public Graphic {
private:
    std::string filename;

public:
    RealImage(const std::string& filename) : filename(filename) {}

    void draw() const override {
        std::cout << "Drawing image from file: " << filename << std::endl;
    }

    void move(int x, int y) override {
        std::cout << "Moving image to (" << x << ", " << y << ")" << std::endl;
    }
};

// Proxy
class ImageProxy : public Graphic {
private:
    std::string filename;
    RealImage* image;

public:
    ImageProxy(const std::string& filename) : filename(filename), image(nullptr) {}

    void loadImage() {
        if (!image) {
            image = new RealImage(filename);
        }
    }

    void draw() const override {
        loadImage();
        image->draw();
    }

    void move(int x, int y) override {
        loadImage();
        image->move(x, y);
    }

    ~ImageProxy() {
        delete image;
    }
};

// Client
class Box {
private:
    int width;
    int height;
    Graphic* graphic;

public:
    Box(int w, int h, Graphic* g) : width(w), height(h), graphic(g) {}

    void draw() const {
        graphic->draw();
    }

    void move(int x, int y) {
        graphic->move(x, y);
    }

    ~Box() {
        delete graphic;
    }
};

// Client
class Mouse {
public:
    void click() {
        std::cout << "Mouse clicked" << std::endl;
    }
};

// Client
class TestImage {
public:
    void loadImage() {
        std::cout << "Loading real image..." << std::endl;
    }
};

// Client
class ImageLoader {
public:
    void loadImage() {
        std::cout << "Loading image..." << std::endl;
    }
};

int main() {
    // Create a proxy for the image
    ImageProxy* proxy = new ImageProxy("TestImage");
    // Create a box with the proxy
    Box* box = new Box(100, 100, proxy);

    // Simulate mouse actions
    Mouse mouse;
    mouse.click();  // Single click, just move the box
    box->move(50, 50);
    box->draw();

    mouse.click();  // Double click, load real image
    proxy->loadImage();
    box->draw();

    // Clean up
    delete box;

    return 0;
}
