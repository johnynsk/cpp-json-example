#ifndef SUPEROBJECT_INCLUDED
#define SUPEROBJECT_INCLUDED

#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "SuperException.h"
#include <vector>
#include <typeinfo>

using namespace std;

class SuperObject //класс супер объекта
{
    void *pointer;
    string type;

public:
    /**
     * Шаблон конструктора
     */
    template<class Type> SuperObject(Type value)
    {
        Type* obj = new Type;
        *obj = value;

        this->pointer = obj;
        this->type = typeid(Type).name();
    }


    /**
     * Конструктор по умолчанию
     */
    SuperObject()
    {
        this->pointer = nullptr;
        this->type = typeid(nullptr).name();
    }


    /**
     * Возвращает тип данных
     */
    string getType()    //полчаем тип объекта
    {
        return type;
    }


    /**
     * Шаблон возврата данных
     */
    template<class Type> Type getValue() const      //получение значения объекта
    {
        Type *pt = (Type*) pointer;
        Type t = *pt;

        return t;
    }


    /**
     * Оператор присваивания (объекта типа SuperObject)
     */
    SuperObject& operator=(SuperObject value) {
        this->pointer = value.pointer;
        this->type = value.getType();
        return *this;
    }


    /**
     * Оператор присваивания любого другого типа
     */
    template <class Type> SuperObject& operator=(Type value) {
        Type* obj = new Type(value);
        this->pointer = obj;
        this->type = typeid(Type).name();
        return *this;
    }

    static SuperObject createFromJsonString(std::string input)
    {
        rapidjson::Document document;
        document.Parse(input.c_str());

        if (document.HasParseError()) {
            throw SuperException("Non-JSON string, RTFM");
        }

        return SuperObject::createFromJsonNode(document);
    }

    static SuperObject createFromJsonNode(rapidjson::Value &jsonNode)       //итерирование по json
    {
        std::map<std::string, SuperObject> resultMap;
        std::vector<SuperObject> resultVector;

        switch(jsonNode.GetType()) {
            case rapidjson::Type::kObjectType:
                for (rapidjson::Value::ConstMemberIterator i = jsonNode.MemberBegin(); i != jsonNode.MemberEnd(); ++i) {
                    resultMap[i->name.GetString()] = SuperObject::createFromJsonNode(jsonNode[i->name.GetString()]);
                }

                return SuperObject(resultMap);

            case rapidjson::Type::kArrayType:
                for (rapidjson::SizeType i = 0; i < jsonNode.Size(); i++) {
                    resultVector.push_back(SuperObject::createFromJsonNode(jsonNode[i]));
                }

                return SuperObject(resultVector);

            case rapidjson::Type::kStringType:
                return SuperObject(std::string(jsonNode.GetString()));

            case rapidjson::Type::kNumberType:
                if (jsonNode.IsInt()) {
                    return SuperObject(jsonNode.GetInt());
                }

                return SuperObject(jsonNode.GetDouble());

            case rapidjson::Type::kNullType:
                return SuperObject();

            case rapidjson::Type::kFalseType:
                return SuperObject(false);

            case rapidjson::Type::kTrueType:
                return SuperObject(true);
        }
    }
};
//
//SuperObject& operator+(SuperObject value1, SuperObject value2)    //перегруженый оператор сложения суперобъекта с переменнойтипа Type
//{
//  if (value1.getType() != value2.getType()) {
//      throw SuperException("Types must be equal");
//  }
//
//  return SuperObject();
//}

template<class Type> SuperObject& operator+(SuperObject val1, Type val2)    //перегруженый оператор сложения суперобъекта с переменнойтипа Type
{
    cout << "avothui";
    if (val1.getType() != typeid(val2)) {
        throw SuperException("Types must be equal (at sum)");
    }

    return SuperObject(val1.getValue<Type>() + val2);
}

template<class Type> SuperObject& operator+(Type value1, SuperObject value2)
{
    return value2 + value1;
}

#endif
