#ifndef UST_H
#define UST_H

#include <iostream>
#include <typeinfo>

class Ust
{
public:
    Ust();

    template<class ValueType>
    Ust(const ValueType& t);

    template<class CastType>
    CastType cast() const;

private:
    struct BaseHolder
    {
        virtual ~BaseHolder() {}
        virtual const std::type_info& type_info() const = 0;
    };

    template<class ValueType>
    struct Holder : BaseHolder
    {
        Holder(const ValueType& value)
            :_value(value) {}

        const std::type_info& type_info() const
        {
            return typeid(_value);
        }

        ValueType _value;
    };
private:
    BaseHolder* _held;
};


Ust::Ust()
    :_held(nullptr)
{}

template <class ValueType>
Ust::Ust(const ValueType& value)
    :_held(new Holder<ValueType>(value))
{}

template <class CastType>
CastType Ust::cast() const
{
    std::string s = typeid(CastType).name();
    std::string s1 = _held->type_info().name();
    if(typeid(CastType) != _held->type_info())
        throw std::runtime_error("Bad any cast");

    return static_cast<Holder<CastType>* >(_held)->_value;
}

#endif // UST_H
