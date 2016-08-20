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
#include "SuperException.h"
#include "SuperViewer.h"
#include <vector>

using namespace rapidjson;

struct Node
{
    std::string key;
    SuperObject value;
    Node *next;
};


int test() {
    //std::string json = "{\"type\":\"test\",\"number\":\"test2\"}";
    //std::string json = "[\"abc\", \"def\"]";
    std::string json = "{\"test\": 123.01, \"tedst\": 152, \"yeah\": {\"magic\": \"fuck yeah\"}, \"array\": [123, {\"cdx\":\"def\"}, [false, true], null]}";
    //SuperObject a = std::string("abcdef string");
    //std::cout << a.getValue<std::string>() << std::endl;
//  a = SuperObject(std::string("cdefghijklmnop")) + a;
//  std::cout << a.getValue<std::string>() << std::endl;

    //std::string json = "{\"a\":\"1\", \"b\": \"2\", \"c\": {\"hui\": \"da\", \"items\": [false, true]}}";
    //SuperObject b = 15;
    //b = 20 + b;
    //a = 33;
    //a = new SuperObject(10);
    //std::cout << b.getValue<int>() << std::endl;
//  a = 10;

    SuperObject fromJson = SuperObject::createFromJsonString(json);
    showMe(fromJson, 0);

    return 0;
}


using namespace std;
void test2()
{
    std::map<string, SuperObject> first;

    first["abcde"]=10;
    first["b"]=30;
    first["c"]=50;
    first["d"]=70;

  //std::map<char,int> second (first.begin(),first.end());
  //std::map<char,int> third (second);
    for( map<string,SuperObject>::iterator i=first.begin(); i!=first.end(); ++i)
    {
        cout << (*i).first << ": " << (*i).second.getValue<int>() << endl;
    }
}

int main()
{
    try {
        test();

        system("pause");
        return 0;

    } catch (SuperException exception) {
        cout << "caught exception" << endl << exception.getMessage() << endl;

        system("pause");
        return 0;
    }
}

