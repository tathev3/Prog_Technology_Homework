#include <iostream>
#include <string>
#include <vector>

class FileSystemElement {
public:
    virtual void showDetails() const = 0;
    virtual ~FileSystemElement() = default;
};

class File : public FileSystemElement {
private:
    std::string name;

public:
    File(const std::string& name) : name(name) {}

    void showDetails() const override {
        std::cout << "File: " << name << std::endl;
    }
};

class Directory : public FileSystemElement {
private:
    std::string name;
    std::vector<FileSystemElement*> elements;

public:
    Directory(const std::string& name) : name(name) {}

    void add(FileSystemElement* element) {
        elements.push_back(element);
    }

    void showDetails() const override {
        std::cout << "Directory: " << name << std::endl;
        for (const auto& element : elements) {
            element->showDetails();
        }
    }
};

int main() {
    File file1("file1.txt");
    File file2("file2.txt");

    Directory folder1("Folder1");
    folder1.add(&file1);

    Directory root("Root");
    root.add(&folder1);
    root.add(&file2);

    root.showDetails();

    return 0;
}