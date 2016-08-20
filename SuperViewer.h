#ifndef SUPERVIEWER_INCLUDED
#define SUPERVIEWER_INCLUDED
#define STEP 4
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "SuperObject.h"
#include <vector>
using namespace std;

string printOffset(int offset)
{
    SuperObject a = 10;
    string result = "";

    for (offset; offset > 0; offset--) {
        result.append(" ");
    }

    return result;
}

void showMe(SuperObject &object, int offset)        //итерирование по json
{
    //cout << printOffset(offset) << "type = " << object.getType() << endl;
    if (object.getType() == "int") {
        cout << printOffset(offset) << "int(" << object.getValue<int>() << ")" << endl;

        return;
    }

    if (object.getType() == "double") {
        cout << printOffset(offset) << "double(" << object.getValue<double>() << ")" << endl;

        return;
    }

    if (object.getType() == typeid(std::string).name()) {
        cout << printOffset(offset) << "string(" << object.getValue<string>() << ")" << endl;

        return;
    }

    if (object.getType() == typeid(char const *).name()) {
        cout << printOffset(offset) << "string(" << object.getValue<string>().c_str() << ")" << endl;

        return;
    }

    if (object.getType() == "bool") {
        cout << printOffset(offset) << "bool(" << ((bool)object.getValue<bool>() ? "true" : "false" ) << ")" << endl;

        return;
    }

    if (object.getType() == typeid(nullptr).name()) {
        cout << printOffset(offset) << "NULL" << endl;

        return;
    }

    if (object.getType() == typeid(map<string, SuperObject>).name()) {
        std::map<string, SuperObject> currentNode = object.getValue<map<string, SuperObject>>();

        cout << printOffset(offset) << "array(" << object.getValue<map<string, SuperObject>>().size() << ") {" << endl;

        for(map<string, SuperObject>::iterator i = currentNode.begin(); i!=currentNode.end(); ++i)
        {
            cout << printOffset(offset + STEP) << "[" << (*i).first << "]=>" << endl;
            showMe((*i).second, offset + STEP);
        }

        cout << printOffset(offset) << "}" << endl;

        return;
    }

    if (object.getType() == typeid(vector<SuperObject>).name()) {
        cout << printOffset(offset) << "array(" << object.getValue<vector<SuperObject>>().size() << ") {" << endl;

        for (int i=0; i < object.getValue<vector<SuperObject>>().size(); i++) {
            cout << printOffset(offset + STEP) << "[" << i << "]=>" << endl;
            showMe(object.getValue<vector<SuperObject>>()[i], offset + STEP);
        }

        cout << printOffset(offset) << "}" << endl;

        return;
    }

    cout << object.getType();
}

#endif

