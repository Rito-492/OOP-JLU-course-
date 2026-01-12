#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Component {  
public:  
    virtual ~Component() { }  
  
    virtual void display(const string& prefix) const = 0;  
  
    virtual void add(Component* component) { }  
  
    virtual void remove(Component* component) { }
  
    virtual int getChildCount() const { }  

    virtual Component* getChild(int index) const {  
        return nullptr;
    }  
};  

class Leaf : public Component {  
private:
    string name;

public:  
    Leaf(const string& name) : name(name) {}  
  
    void display(const string& prefix) const override {  
        cout << prefix << name << endl;  
    }
};  

class Composite : public Component {  
private:  
    string name;  
    vector<Component*> children;  
  
public:  
    Composite(const string& name) : name(name) {}  
  
    void display(const string& prefix) const override {  
        cout << prefix << name << endl;  
        for (const auto& child : children) {  
            child->display(prefix + "  ");
        }  
    }  
  
    void add(Component* component) override {  
        children.push_back(component);  
    }  
  
    void remove(Component* component) override {  
        for (auto it = children.begin(); it != children.end(); ++it) {  
            if (*it == component) {  
                children.erase(it);  
                break;  
            }  
        }  
    }  
  
    int getChildCount() const override {  
        return children.size();  
    }
  
    Component* getChild(int index) const override {  
        if (index < 0 || index >= children.size()) {  
            return nullptr;  
        }  
        return children[index];  
    }  
};  

int main() {
    Composite* headquarters = new Composite("总部");  
    Composite* branch1 = new Composite("分公司1");  
    Leaf* hrDept = new Leaf("人力资源部");  
    Leaf* financeDept = new Leaf("财务部");  

    branch1->add(hrDept);  
    branch1->add(financeDept);  
    headquarters->add(branch1);  

    headquarters->display(""); // 显示整个组织结构  

    delete hrDept;
    delete financeDept;
    delete branch1;
    delete headquarters;

    return 0;  
}