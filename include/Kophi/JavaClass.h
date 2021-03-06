#ifndef KOPHI_JAVACLASS_H
#define KOPHI_JAVACLASS_H

#include <Kophi/Utils.h>

#include <Kophi/JavaConstant.h>
#include <Kophi/JavaProperty.h>
#include <Kophi/JavaAttribute.h>

namespace Kophi {
    constexpr uint32_t JAVA_CLASS_MAGIC = 0xCAFEBABE;

    class JavaPool {
        std::vector<JavaConstant> pool;
    public:
        unsigned size() const;
        JavaConstant operator[](unsigned index) const;

        JavaPool(const JavaClass &java, unsigned size, const Byte *data, unsigned &index);
        JavaPool(const JavaPool &pool);
        JavaPool() = default;
    };

    class JavaClass {
    public:
        uint32_t magic = 0;
        uint16_t majorVersion = 0;
        uint16_t minorVersion = 0;
        AccessFlags accessFlags = AccessFlags::None;
        PoolIndex thisClass = 0;
        PoolIndex superClass = 0;
        uint16_t constantCount = 0;
        uint16_t interfaceCount = 0;
        uint16_t fieldCount = 0;
        uint16_t methodCount = 0;
        uint16_t attributeCount = 0;
        JavaPool pool;
        std::vector <uint16_t> interfaces;
        std::vector <JavaField> fields;
        std::vector <JavaMethod> methods;
        std::vector <JavaAttribute> attributes;

        const JavaConstantClass *getThisClass() const;
        const JavaConstantClass *getSuperClass() const;

        const JavaAttribute searchAttributes(const std::string &name) const;
        const std::vector<JavaConstant> searchConstants(JavaConstantTag tag) const;

        const std::string getSourceFileName() const;
        const std::vector<std::string> getDependancies() const;

        JavaClass(const std::vector<Byte> &data);
        JavaClass(const std::string &path);
        JavaClass(const JavaClass &java);
        JavaClass() = default;
    };

    std::string describeClass(const JavaClass &java);
}

#endif //KOPHI_JAVACLASS_H
