#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
using namespace std;

#define BufferMax 0x000080
#define INF 0x3f3f3f3f

template<typename T>
class Field {
    T value;
public:
    Field() : value(0) {}
    Field(const T data) : value(data) {}
    T getValue() const { return value; }
};

class Record {
    vector<void*> fields;
public:
    ~Record() {
        fields.clear();
    }
    template<typename T>
    void addField(const T& value) {
        void* ptr = nullptr;
        ptr = new Field<T>(value);
        fields.push_back(ptr);
    }
    template<typename T>
    void updateField(size_t fieldIndex, const T& newValue);
    void showRecord(vector<string>& field_types) {
        for(size_t j = 0; j < fields.size(); j++) {
            if (field_types[j] == "Int") {
                auto fieldPtr = static_cast<Field<int>*>(fields[j]);
                cout << fieldPtr->getValue() << ' ';
            } else if (field_types[j] == "Float") {
                auto fieldPtr = static_cast<Field<float>*>(fields[j]);
                cout << fieldPtr->getValue() << ' ';
            } else if (field_types[j] == "Double") {
                auto fieldPtr = static_cast<Field<double>*>(fields[j]);
                cout << fieldPtr->getValue() << ' ';
            } else if (field_types[j] == "Char") {
                auto fieldPtr = static_cast<Field<char>*>(fields[j]);
                cout << fieldPtr->getValue() << ' ';
            } else if (field_types[j] == "String") {
                auto fieldPtr = static_cast<Field<string>*>(fields[j]);
                cout << fieldPtr->getValue() << ' ';
            }
        }
        cout << endl;
    }
    template<typename T>
    T getField(T null, const size_t& index) const { return *((T*)fields[index]); }
};

class Table {
    string name;
    vector<string> field_types;
    vector<string> field_names;
    vector<Record> records;
public:
    Table() : name("null") {}
    Table(const string& table_name) : name(table_name) {}
    void addField(string& field_name, string& field_type) {
        field_names.push_back(field_name);
        field_types.push_back(field_type);
    }
    void addRecord();
    void select(const string& field_name);
    template<typename T>
    void updateRecord(size_t recordIndex, const string& fieldName, const T& newValue);
    void deleteRecord(size_t recordIndex);
    string getName() const { return name; }
    void showTable();
};

class DataBase {
    string name;
    vector<Table> tables;
public:
    DataBase(const string& db_name) : name(db_name) {}
    void createTable(string& table_name);
    void insertRecord(const string& table_name);
    void selectFrom(const string& field_name, const string& table_name);
    void deleteFrom(const size_t& recordindex, const string& table_name);
    void dropTable(const string& table_name);
    void showTable(const string& table_name);
    void showDataBase();
    string getName() const { return name; }
};

void Table::addRecord() {
    Record rcd;
    char c;
    while ( cin >> c && c != '(') ;
    for (vector<string> :: iterator it = field_types.begin(); it != field_types.end(); it++) {
        if (*it == "Int") {
            int value;
            cin >> value;
            rcd.addField(value);
        } else if (*it == "Float") {
            float value;
            cin >> value;
            rcd.addField(value);
        } else if (*it == "Double") {
            double value;
            cin >> value;
            rcd.addField(value);
        } else if (*it == "Char") {
            char value;
            cin >> value;
            rcd.addField(value);
        } else if (*it == "String") {
            string value;
            cin >> value;
            rcd.addField(value);
        }
    }
    records.push_back(rcd);
}

void Table::select(const string& field_name) {
    size_t key = INF;
    for (size_t i = 0; i < field_types.size(); i++)
        if (field_names[i] == field_name) {
            key = i;
            break;
        }
    if (key == INF) {
        cout << "There is not a field named " << field_name << " ." << endl << endl;
        return ;
    }
    for (size_t i = 0; i < records.size(); i++) {
        if (field_types[key] == "Int")
            cout << records[i].getField(0, key) << endl << endl;
        if (field_types[key] == "Float")
           cout << records[i].getField(0, key) << endl << endl;
        if (field_types[key] == "Double")
            cout << records[i].getField(0, key) << endl << endl;
        if (field_types[key] == "Char")
            cout << records[i].getField('0', key) << endl << endl;
        if (field_types[key] == "String")
            cout << records[i].getField("0", key) << endl << endl;
    }
}

template<typename T>
void Record::updateField(size_t fieldIndex, const T& newValue) {
    if (fieldIndex >= fields.size()) {
        cout << "Field index out of range." << endl;
        return;
    }
    auto fieldPtr = static_cast<Field<T>*>(fields[fieldIndex]);
    fieldPtr->setValue(newValue);
}

template<typename T>
void Table::updateRecord(size_t recordIndex, const string& fieldName, const T& newValue) {
    if (recordIndex >= records.size()) {
        cout << "Record index out of range." << endl;
        return;
    }
    size_t fieldIndex = find(field_names.begin(), field_names.end(), fieldName) - field_names.begin();
    if (fieldIndex >= field_names.size()) {
        cout << "Field name not found." << endl;
        return;
    }
    records[recordIndex].updateField<T>(fieldIndex, newValue);
}

void Table::deleteRecord(size_t recordIndex) {
    if (recordIndex >= records.size()) {
        cout << "Record index out of range." << endl;
        return;
    }
    records.erase(records.begin() + recordIndex);
}

void Table::showTable() {
    cout<< endl << name << endl;
    for (vector<string> :: iterator it = field_names.begin(); it != field_names.end(); it++)
       cout << *it << ' ';
    cout << endl;
    for (auto it = records.begin(); it != records.end(); it++)
        it->showRecord(field_types);
    cout << endl;
}

void DataBase::createTable(string& table_name) {
    Table tb(table_name);
    string field_name, field_type;
    while (cin >> field_name && field_name != "(") ;
    while (cin >> field_name && field_name != ");") {
        cin >> field_type;
        tb.addField(field_name, field_type);
    }
    tables.push_back(tb);
}

void DataBase::insertRecord(const string& table_name) {
    for (vector<Table> :: iterator it = tables.begin(); it != tables.end(); it++)
        if (it->getName() == table_name) {
            it->addRecord();
            return ;
        }
    cout << "There is not a table named " << table_name << " ." << endl << endl;
}

void DataBase::selectFrom(const string& field_name, const string& table_name) {
    for (vector<Table> :: iterator it = tables.begin(); it != tables.end(); it++) {
        if (it->getName() == table_name) {
            if (field_name == "*")
                it->showTable();
            else
                it->select(field_name);
            return ;
        }
    }
    cout << "There is not a table named " << table_name << " ." << endl << endl;
}

void DataBase::deleteFrom(const size_t& recordindex, const string& table_name) {
    for (vector<Table> :: iterator it = tables.begin(); it != tables.end(); it++)
        if (it->getName() == table_name) {
            it->deleteRecord(recordindex);
            return ;
        }
    cout << "There is not a table named " << table_name << " ." << endl << endl;
}

void DataBase::dropTable(const string& table_name) {
    for (size_t i = 0; i < tables.size(); i++) {
        if (tables[i].getName() == table_name) {
            tables.erase(tables.begin() + i);
            cout << "SUCCESS!" << endl << endl;
            return ;
        }
    }
    cout << "There is not a table named " << table_name << " ." << endl << endl;
}

void DataBase::showTable(const string& table_name) {
    for (vector<Table> :: iterator it = tables.begin(); it != tables.end(); it++)
        if (it->getName() == table_name) {
            it->showTable();
            return ;
        }
    cout << "There is not a table named " << table_name << " ." << endl << endl;
}

void DataBase::showDataBase() {
    for (vector<Table> :: iterator it = tables.begin(); it != tables.end(); it++)
        it->showTable();
}

int main() {
    
    DataBase db("DB1");
    string buf;
    while (cin >> buf) {
        if (buf == "exit")
            break;
        if (buf == "CREATE") {
            cin >> buf;
            if (buf == "TABLE") {
                string table_name;
                cin >> table_name;
                db.createTable(table_name);
                db.showDataBase();
            }
        }
        if (buf == "INSERT") {
            cin >> buf;
            if (buf == "INTO") {
                string table_name;
                cin >> table_name;
                db.insertRecord(table_name);
                db.showDataBase();
            }
        }
        if (buf == "SELECT") {
            cin >> buf;
            string table_name;
            string field_name = buf;
            cin >> buf;
            if (buf == "FROM") {
                cin >> table_name;
                db.selectFrom(field_name, table_name);
            }
        }
        if (buf == "UPDATE") {
            size_t recordindex;
            cin >> recordindex;
            cin >> buf;
            if (buf == "FROM") {
                string table_name;
                cin >> table_name;

                db.deleteFrom(recordindex, table_name);
                db.showDataBase();
            }
        }
        if (buf == "DELETE") {
            size_t recordindex;
            cin >> recordindex;
            cin >> buf;
            if (buf == "FROM") {
                string table_name;
                cin >> table_name;
                db.deleteFrom(recordindex, table_name);
                db.showDataBase();
            }
        }
        if (buf == "DROP") {
            cin >> buf;
            if (buf == "TABLE") {
                string table_name;
                cin >> table_name;
                db.dropTable(table_name);
            }
        }
    }
    return 0;
}