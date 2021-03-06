#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <stack>
#include <sstream>
#include <errno.h>
#include "util/tc_autoptr.h"

using namespace std;

#define YYSTYPE GrammarBasePtr

void yyerror(char const *msg);

/**
 * 语法元素基类
 */
class GrammarBase : virtual public taf::TC_HandleBase
{
public:
    virtual ~GrammarBase(){};
};

typedef taf::TC_AutoPtr<GrammarBase> GrammarBasePtr;

/**
 * 解析过程中的整形数
 */
class StringTok : public GrammarBase
{
public:

    StringTok() { }
    string v;
};

typedef taf::TC_AutoPtr<StringTok> StringTokPtr;

/**
 * 解析过程中的整形数
 */
class IntegerTok : public GrammarBase
{
public:

    IntegerTok():v(0) { }
    long long v;
};

typedef taf::TC_AutoPtr<IntegerTok> IntegerTokPtr;

/**
 * 解析过程中的浮点数
 */
class FloatTok : public GrammarBase
{
public:

    FloatTok():v(0.0f) { }
    double v;
};

typedef taf::TC_AutoPtr<FloatTok> FloatTokPtr;

/**
 * 解析过程中的bool类型
 */
class BoolTok : public GrammarBase
{
public:

    BoolTok():v(true) { }
    bool v;
};

typedef taf::TC_AutoPtr<BoolTok> BoolTokPtr;

/**
 * 解析过程中的数值类型
 */
class ConstTok : public GrammarBase
{
public:

    ConstTok():t(VALUE) { }

    enum
    {
        VALUE,
        STRING,
        BOOL,
    };

    int    t;
    string v;
};

typedef taf::TC_AutoPtr<ConstTok> ConstTokPtr;

///////////////////////////////////////////////

/**
 * 类型基类
 */
class Type : virtual public GrammarBase
{
public:
    virtual bool isSimple() const { return false;}
};

typedef taf::TC_AutoPtr<Type> TypePtr;

/**
 * 内建类型
 */
class Builtin : public Type
{
public:

    enum Kind
    {
        KindVoid,
        KindBool,
        KindByte,
        KindShort,
        KindInt,
        KindLong,
        KindFloat,
        KindDouble,
        KindString,
        KindBinary,
        KindVector,
        KindMap
    };

    /**
     * 构造函数
     * @param kind
     */
    Builtin(Kind kind);

    /**
     * 类型
     *
     * @return Kind
     */
    Kind kind() const;

    /**
     * 是否是简单类型
     *
     * @return bool
     */
    bool isSimple() const;

    /**
     * 字符串标示
     */
    static const char* builtinTable[];

protected:

    Kind _kind;
};

typedef taf::TC_AutoPtr<Builtin> BuiltinPtr;

/**
 * Vector类型
 */
class Vector : public Type
{
public:
    /**
     * 构造函数
     * @param ptr
     */
    Vector(const TypePtr& ptr);

    /**
     * 获取类型
     *
     * @return TypePtr&
     */
	TypePtr& getTypePtr() {return _ptr;}
protected:
    TypePtr _ptr;
};

typedef taf::TC_AutoPtr<Vector> VectorPtr;

/**
 * Map类型
 */
class Map : public Type
{
public:
    /**
     * 构造函数
     * @param pleft
     * @param pright
     */
    Map(const TypePtr& pleft, const TypePtr& pright);

    /**
     * 获取左类型
     *
     * @return TypePtr&
     */
	TypePtr& getLeftTypePtr() {return _pleft;}

    /**
     * 获取右类型
     *
     * @return TypePtr&
     */
	TypePtr& getRightTypePtr() {return _pright;}

protected:
    TypePtr _pleft;
    TypePtr _pright;
};

typedef taf::TC_AutoPtr<Map> MapPtr;

/**
 * 变量定义
 */
class TypeId : public GrammarBase
{
public:
    /**
     * 构造函数
     * @param ptr
     * @param id
     */
    TypeId(const TypePtr& ptr, const string& id);

    /**
     * 变量名称
     *
     * @return string
     */
    string getId() const { return _id; }

    /**
     * 变量类型
     *
     * @return Type*
     */
    TypePtr& getTypePtr() { return _ptr;}

protected:
    TypePtr _ptr;
    string  _id;
};

typedef taf::TC_AutoPtr<TypeId> TypeIdPtr;


////////////////////////////////////////////////////
//
class Namespace;
typedef taf::TC_AutoPtr<Namespace> NamespacePtr;
/**
 * 容器基类, 所有可以包含其他元素的元素都从该基类继承
 */
class Container : virtual public GrammarBase
{
public:
    /**
     * 构造函数
     * @param id
     */
    Container(const string &id) : _id(id)
    {
    }

    /**
     * 生成名字空间
     * @param id
     *
     * @return NamespacePtr
     */
    NamespacePtr createNamespace(const string &id);

    /**
     * 获取ID
     *
     * @return string
     */
    string getId() const { return _id;}

    /**
     * 获取所有的名字空间
     *
     * @return vector<NamespacePtr>&
     */
    vector<NamespacePtr> &getAllNamespacePtr() { return _ns; }
protected:
    string                  _id;
    vector<NamespacePtr>    _ns;
};

typedef taf::TC_AutoPtr<Container> ContainerPtr;

////////////////////////////////////////////////////
//
class Const : public GrammarBase
{
public:
    /**
     *
     * @param tPtr
     * @param cPtr
     */
    Const(TypeIdPtr &tPtr, ConstTokPtr &cPtr) : _tPtr(tPtr), _cPtr(cPtr)
    {
    }

    /**
     *
     *
     * @return TypePtr&
     */
    TypeIdPtr &getTypeIdPtr()       { return _tPtr; }

    /**
     *
     *
     * @return ConstTokPtr
     */
    ConstTokPtr getConstTokPtr()    { return _cPtr; }

protected:
    TypeIdPtr   _tPtr;
    ConstTokPtr _cPtr;
};

typedef taf::TC_AutoPtr<Const> ConstPtr;

////////////////////////////////////////////////////
//
/**
 * 结构
 */
class Struct : virtual public Container, virtual public Type
{
public:
    /**
     * 构造函数
     * @param id
     */
    Struct(const string& id, const string &sid) : Container(id), _sid(sid)
    {
    }

    /**
     * 添加成员变量
     * @param ptid
     */
    void addTypeId(const TypeIdPtr &ptr);

    /**
     * 获取所有的成员变量
     *
     * @return vector<TypeIdPtr>&
     */
    vector<TypeIdPtr>& getAllMemberPtr() {return _members;}

    /**
     * 获取结构的名称
     *
     * @return string
     */
    string getSid() const { return _sid; }

protected:
    vector<TypeIdPtr>   _members;
    string              _sid;
};

typedef taf::TC_AutoPtr<Struct> StructPtr;

////////////////////////////////////////////////////
//
/**
 * 参数描述
 */
class ParamDecl : public GrammarBase
{
public:
    /**
     * 构造
     * @param typeIdPtr
     * @param v
     */
    ParamDecl(const TypeIdPtr &typeIdPtr) : _typeIdPtr(typeIdPtr)
    {
    }

    /**
     * 变量声明
     *
     * @return TypeIdPtr&
     */
    TypeIdPtr& getTypeIdPtr() { return _typeIdPtr; }

protected:
    TypeIdPtr   _typeIdPtr;
};
typedef taf::TC_AutoPtr<ParamDecl> ParamDeclPtr;

///////////////////////////////////////////////////////
//
/**
 * 操作类
 */
class Operation : public Container
{
public:
    /**
     * 构造函数
     * @param id
     * @param typePtr
     */
    Operation(const string &id, const TypePtr &typePtr) : Container(id), _typePtr(typePtr)
    {
    }

    /**
     * 生成一个参数
     * @param typeIdPtr
     *
     * @return ParamDeclPtr
     */
    ParamDeclPtr createParamDecl(const TypeIdPtr &typeIdPtr);

    /**
     * 获取返回值类型
     *
     * @return TypePtr&
     */
	TypePtr &getTypePtr() { return _typePtr; }

    /**
     * 获取所有参数
     *
     * @return vector<ParamDeclPtr>&
     */
	vector<ParamDeclPtr> &getAllParamDeclPtr() { return _ps; }
protected:
    TypePtr _typePtr;
    vector<ParamDeclPtr>    _ps;
};

typedef taf::TC_AutoPtr<Operation> OperationPtr;
///////////////////////////////////////////////////////
//
/**
 * 接口描述
 */
class Interface : public Container
{
public:
    /**
     * 构造
     * @param id
     */
    Interface(const string &id) : Container(id)
    {

    }

    /**
     * 生成一个操作
     * @param id
     * @param typePtr
     *
     * @return OperationPtr
     */
    OperationPtr createOperation(const string &id, const TypePtr &typePtr);

    /**
     * 获取所有操作
     *
     * @return vector<OperationPtr>&
     */
	vector<OperationPtr> &getAllOperationPtr() { return _ops; }
protected:
    vector<OperationPtr>    _ops;
};

typedef taf::TC_AutoPtr<Interface> InterfacePtr;

/////////////////////////////////////////////////////////
//
/**
 * 名字空间
 */
class Namespace : public Container
{
public:
    /**
     * 构造函数
     * @param id
     */
    Namespace(const string &id) : Container(id)
    {
    }

    /**
     * 生成接口
     * @param id
     *
     * @return InterfacePtr
     */
    InterfacePtr createInterface(const string &id);

    /**
     * 生成结构
     * @param id
     *
     * @return StructPtr
     */
    StructPtr createStruct(const string& id);

    /**
     *
     * @param pPtr
     * @param cPtr
     *
     * @return ConstPtr
     */
    ConstPtr createConst(TypeIdPtr &pPtr, ConstTokPtr &cPtr);

    /**
     * 是否有接口
     *
     * @return bool
     */
    bool hasInterface() const { return !_is.empty(); }

    /**
     * 获取所有的接口
     *
     * @return vector<InterfacePtr>&
     */
	vector<InterfacePtr> &getAllInterfacePtr() { return _is; }

    /**
     * 获取所有的结构
     *
     * @return vector<StructPtr>&
     */
	vector<StructPtr> &getAllStructPtr() { return _ss; }

    /**
     * 常量类型
     *
     * @return vector<ConstPtr>&
     */
    vector<ConstPtr> &getAllConstPtr()     { return _cs; }

protected:
    vector<InterfacePtr>    _is;
    vector<StructPtr>       _ss;
    vector<ConstPtr>        _cs;
};

/////////////////////////////////////////////////////////////////
/**
 * 上下文
 */
class Context : public taf::TC_HandleBase
{
public:
    /**
     * 构造函数
     */
    Context(const string &file) : _currline(1), _filename(file)
    {
    }

    /**
     * 下一行
     */
    void nextLine() { _currline++; }

    /**
     * 目前的行
     *
     * @return size_t
     */
    size_t getCurrLine() { return _currline; }

    /**
     * 当前文件名
     *
     * @return string
     */
    string getFileName() { return _filename; }

    /**
     * 添加include的文件
     * @param incl
     */
    void addInclude(const string &incl);

    /**
     * 添加属于这个文件的名字空间
     * @param c
     */
    void addNamespacePtr(const NamespacePtr &c)
    {
        _namespaces.push_back(c);
    }

    /**
     * 获取includes的文件
     *
     * @return vector<string>
     */
    vector<string> getIncludes() { return _includes; }

    /**
     * 获取名字空间
     *
     * @return vector<NamespacePtr>
     */
    vector<NamespacePtr> getNamespaces() { return _namespaces; }

protected:
    size_t                  _currline;
    string                  _filename;
    vector<string>          _includes;
    vector<NamespacePtr>    _namespaces;
};

typedef taf::TC_AutoPtr<Context> ContextPtr;

#endif

